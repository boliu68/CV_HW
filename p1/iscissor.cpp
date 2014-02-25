#include<float.h>
#include<limits.h>
#include<math.h>
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "iscissor.h"
#include "helper.h"
using namespace cv;
using namespace std;

const int linktable[8][2]={{1,0},{1,-1},{0,-1},{-1,-1}
                            ,{-1,0},{-1,1},{0,1},{1,1}};

double PixelNode::Column(){return column;}

double PixelNode::Row(){return row;}

PixelNode::PixelNode(int c,int r):FibHeapNode()
{
    state=INITIAL;
    prevNode=NULL;
    column=c;row=r;
    totalCost=DBL_MAX;
}

Iscissor::Iscissor(QImage * image, CostFunction cf)
{
    img=image;
    pixelnodes.resize(img->height());
    for(int i=0;i<img->height();i++)
        for(int j=0;j<img->width();j++)
            pixelnodes[i].push_back(new PixelNode(j,i));
    //mask=image->createHeuristicMask();
    QImage m(img->width(),img->height(),img->format());
    m.fill(qRgb(255,255,255));
    mask=m;
    seed=NULL;
    costfunction=cf;
    costFun();
}

void Iscissor::setSeed(int column,int row)
{
    seed=pixelnodes[row][column];
    updatePathTree();
}

QImage Iscissor::drawCostGraph()
{
    int w=img->width(),h=img->height();
    QImage cg(3*w,3*h,img->format());
    for(int j=0;j<h;j++)
        for(int i=0;i<w;i++)
        {
            PixelNode *pn=pixelnodes[j][i];
            cg.setPixel(3*i+1,3*j+1,img->pixel(i,j));
            cg.setPixel(3*i+2,3*j+1,qRgb(pn->LinkCost(0)*1.5,pn->LinkCost(0)*1.5,pn->LinkCost(0)*1.5));
            cg.setPixel(3*i+2,3*j,qRgb(pn->LinkCost(1)*1.5,pn->LinkCost(1)*1.5,pn->LinkCost(1)*1.5));
            cg.setPixel(3*i+1,3*j,qRgb(pn->LinkCost(2)*1.5,pn->LinkCost(2)*1.5,pn->LinkCost(2)*1.5));
            cg.setPixel(3*i,3*j,qRgb(pn->LinkCost(3)*1.5,pn->LinkCost(3)*1.5,pn->LinkCost(3)*1.5));
            cg.setPixel(3*i,3*j+1,qRgb(pn->LinkCost(4)*1.5,pn->LinkCost(4)*1.5,pn->LinkCost(4)*1.5));
            cg.setPixel(3*i,3*j+2,qRgb(pn->LinkCost(5)*1.5,pn->LinkCost(5)*1.5,pn->LinkCost(5)*1.5));
            cg.setPixel(3*i+1,3*j+2,qRgb(pn->LinkCost(6)*1.5,pn->LinkCost(6)*1.5,pn->LinkCost(6)*1.5));
            cg.setPixel(3*i+2,3*j+2,qRgb(pn->LinkCost(7)*1.5,pn->LinkCost(7)*1.5,pn->LinkCost(7)*1.5));
        }
    return cg;
}
QImage Iscissor::drawPathTree()
{
    int w=img->width(),h=img->height();
    QImage cg(3*w,3*h,img->format());
    cg.fill(qRgb(0,0,0));
    for(int j=0;j<h;j++)
        for(int i=0;i<w;i++)
        {
            PixelNode *pn=pixelnodes[j][i];
            cg.setPixel(3*i+1,3*j+1,img->pixel(i,j));
            PixelNode *prepn=pn->prevNode;
            if(prepn!=NULL)
            {
                int c=3*i+1+prepn->Column()-pn->Column();
                int r=3*j+1+prepn->Row()-pn->Row();
                cg.setPixel(c,r,qRgb(255,255,0));
                c=3*prepn->Column()+1+pn->Column()-prepn->Column();
                r=3*prepn->Row()+1+pn->Row()-prepn->Row();
                cg.setPixel(c,r,qRgb(127,127,0));
            }
        }
    return cg;
}
QImage Iscissor::drawPixelNode()
{
    int w=img->width(),h=img->height();
    QImage cg(3*w,3*h,img->format());
    cg.fill(qRgb(0,0,0));
    for(int j=0;j<h;j++)
        for(int i=0;i<w;i++)
            cg.setPixel(3*i+1,3*j+1,img->pixel(i,j));
    return cg;
}
void Iscissor::updatePathTree()
{
    //mask.save("mask.png");
    initializePixelNodes();
    FibHeap heap;
    heap.Insert(seed);
    PixelNode *q;
    while(heap.Minimum()!=NULL)
    {
        q=(PixelNode *)heap.ExtractMin();
        q->state=PixelNode::EXPANDED;
        int r,c;
        for(int i=0;i<8;i++)
        {
            q->Neighbor(i,c,r);
            if(c>=0&&c<img->width()&&r>=0&&r<img->height()&&mask.pixel(c,r)!=0)
            {
                PixelNode *pn=pixelnodes[r][c];
                if(pn->state!=PixelNode::EXPANDED)
                {
                    double cost=q->LinkCost(i);
                    if(pn->state==PixelNode::INITIAL)
                    {
                        pn->prevNode=q;
                        pn->totalCost=cost+q->totalCost;
                        pn->state=PixelNode::ACTIVE;
                        heap.Insert(pn);
                    }
                    else if(pn->state==PixelNode::ACTIVE)
                    {
                        if(cost+q->totalCost<pn->totalCost)
                        {
                            pn->prevNode=q;
                            PixelNode newpn(pn->Column(),pn->Row());
                            newpn.totalCost=cost+q->totalCost;
                            heap.DecreaseKey(pn,newpn);
                        }
                    }
                }
            }
        }
    }
}

void Iscissor::costFunModify()
{
    int height=img->height();
    int width=img->width();
    double maxD=-1.0;
    for(int j=0;j<height;j++)
        for(int i=0;i<width;i++)
        {
            PixelNode *pn=pixelnodes[j][i];
            for(int k=0;k<8;k++)
            {
                pn->setLinkCost(k,getD(i,j,k));
                if(pn->LinkCost(k)>maxD)
                    maxD=pn->LinkCost(k);
            }
        }
    for(int j=0;j<height;j++)
        for(int i=0;i<width;i++)
        {
             PixelNode *pn=pixelnodes[j][i];
            for(int k=0;k<8;k++)
            {
                double D=pn->LinkCost(k);
                double length=k%2==0?1.0:sqrt(2.0);
                pn->setLinkCost(k,(maxD-D)*length);
            }
        }
}

double Iscissor::getD(int i, int j, int link)
{
    double D=0;
    double d[3];
    if(link==0)
    {
        if(j==0||j==img->height()-1||i==img->width()-1)
            return -1.0;
        int c0[3],c1[3],c2[3],c3[3];
        transQColorFormat(img->pixel(i,j-1),c0);
        transQColorFormat(img->pixel(i+1,j-1),c1);
        transQColorFormat(img->pixel(i,j+1),c2);
        transQColorFormat(img->pixel(i+1,j+1),c3);
        for(int i=0;i<3;i++)
            d[i]=fabs((c0[i]+c1[i])/2.0-(c2[i]+c3[i])/2.0)/2.0;
    }
    else if(link==1)
    {
        if(j==0||i==img->width()-1)
            return -1.0;
        int c0[3],c1[3];
        transQColorFormat(img->pixel(i+1,j),c0);
        transQColorFormat(img->pixel(i,j-1),c1);
        for(int i=0;i<3;i++)
            d[i]=fabs(1.0 * (c0[i]-c1[i]))/sqrt(2.0);
    }
    else if(link==2)
    {
        if(i==0||j==0||i==img->width()-1)
            return -1.0;
        int c0[3],c1[3],c2[3],c3[3];
        transQColorFormat(img->pixel(i-1,j),c0);
        transQColorFormat(img->pixel(i-1,j-1),c1);
        transQColorFormat(img->pixel(i+1,j),c2);
        transQColorFormat(img->pixel(i+1,j-1),c3);
        for(int i=0;i<3;i++)
            d[i]=fabs((c0[i]+c1[i])/2.0-(c2[i]+c3[i])/2.0)/2.0;
    }
    else if(link==3)
    {
        if(i==0||j==0)
            return -1.0;
        int c0[3],c1[3];
        transQColorFormat(img->pixel(i-1,j-1),c0);
        transQColorFormat(img->pixel(i-1,j),c1);
        for(int i=0;i<3;i++)
            d[i]=fabs(1.0 * (c0[i]-c1[i]))/sqrt(2.0);
    }
    else if(link==4)
    {
        int c0[3],c1[3],c2[3],c3[3];
        if(i==0||j==0||j==img->height()-1)
            return -1.0;
        transQColorFormat(img->pixel(i,j-1),c0);
        transQColorFormat(img->pixel(i-1,j-1),c1);
        transQColorFormat(img->pixel(i-1,j+1),c2);
        transQColorFormat(img->pixel(i,j+1),c3);
        for(int i=0;i<3;i++)
            d[i]=fabs((c0[i]+c1[i])/2.0-(c2[i]+c3[i])/2.0)/2.0;
    }
    else if(link==5)
    {
        if(i==0||j==img->height()-1)
            return -1.0;
        int c0[3],c1[3];
        transQColorFormat(img->pixel(i-1,j),c0);
        transQColorFormat(img->pixel(i,j+1),c1);
        for(int i=0;i<3;i++)
            d[i]=fabs(1.0 * (c0[i]-c1[i]))/sqrt(2.0);
    }
    else if(link==6)
    {
        int c0[3],c1[3],c2[3],c3[3];
        if(i==0||i==img->width()-1||j==img->height()-1)
            return -1.0;
        transQColorFormat(img->pixel(i-1,j),c0);
        transQColorFormat(img->pixel(i-1,j+1),c1);
        transQColorFormat(img->pixel(i+1,j+1),c2);
        transQColorFormat(img->pixel(i+1,j),c3);
        for(int i=0;i<3;i++)
            d[i]=fabs((c0[i]+c1[i])/2.0-(c2[i]+c3[i])/2.0)/2.0;
    }
    else
    {
        int c0[3],c1[3];
        if(i==img->width()-1||j==img->height()-1)
            return -1.0;
        transQColorFormat(img->pixel(i+1,j),c0);
        transQColorFormat(img->pixel(i,j+1),c1);
        for(int i=0;i<3;i++)
            d[i]=fabs(1.0* (c0[i]-c1[i]))/sqrt(2.0);
    }
    for(int i=0;i<3;i++)
        D+=d[i]*d[i];
    D=sqrt(D/3.0);
    return D;
}

void PixelNode::operator =(FibHeapNode& RHS)
{
    PixelNode& pRHS=(PixelNode&)RHS;
    FHN_Assign(RHS);
    totalCost=pRHS.totalCost;
}

int PixelNode::operator ==(FibHeapNode& RHS)
{
    PixelNode& pRHS=(PixelNode&)RHS;
    if (FHN_Cmp(RHS)) return 0;
    // Key compare goes here in derived classes
    if(RHS.NegInfinityFlag&&NegInfinityFlag) return 1;
    return totalCost==pRHS.totalCost;
}

int PixelNode::operator <(FibHeapNode& RHS)
{
     int X;
     PixelNode& pRHS=(PixelNode&)RHS;
     if ((X=FHN_Cmp(RHS)) != 0)
      return X < 0 ? 1 : 0;
     // Key compare goes here in derived classes
     if(RHS.NegInfinityFlag&&NegInfinityFlag)
         return 0;
     return totalCost<pRHS.totalCost;
}

void PixelNode::Print()
{
    if (NegInfinityFlag)
        cout << "-inf.";
    else cout << totalCost;
}

void PixelNode::Neighbor(int link, int &c, int &r)
{
    c=column+linktable[link][0];
    r=row+linktable[link][1];
}

void Iscissor::initializePixelNodes()
{
    int h=img->height(),w=img->width();
    for(int j=0;j<h;j++)
        for(int i=0;i<w;i++)
        {
            pixelnodes[j][i]->totalCost=DBL_MAX;
            pixelnodes[j][i]->state=PixelNode::INITIAL;
        }
    seed->totalCost=0;
    seed->prevNode=NULL;
}

void PixelNode::setLinkCost(int link, double value)
{
    linkCost[link]=value;
}

double PixelNode::LinkCost(int link)
{
    return linkCost[link];
}

double PixelNode::LinkCost(PixelNode *pn)
{
    if(pn->Column()==column+1&&pn->Row()==row)
        return linkCost[0];
    if(pn->Column()==column+1&&pn->Row()==row-1)
        return linkCost[1];
    if(pn->Column()==column&&pn->Row()==row-1)
        return linkCost[2];
    if(pn->Column()==column-1&&pn->Row()==row-1)
        return linkCost[3];
    if(pn->Column()==column-1&&pn->Row()==row)
        return linkCost[4];
    if(pn->Column()==column-1&&pn->Row()==row+1)
        return linkCost[5];
    if(pn->Column()==column&&pn->Row()==row+1)
        return linkCost[6];
    if(pn->Column()==column+1&&pn->Row()==row+1)
        return linkCost[7];
    return -1.0;
}

void Iscissor::getPath(int column, int row, vector<QPoint> &path)
{
    PixelNode *pn=pixelnodes[row][column];
    while(pn!=NULL)
    {
        path.push_back(QPoint(pn->Column(),pn->Row()));
        pn=pn->prevNode;
    }
    reverse(path.begin(),path.end());
}

void Iscissor::setCostFunction(CostFunction cf)
{
    costfunction=cf;
    costFun();
}

void Iscissor::costFun()
{
    if(costfunction==MODIFIED)
        costFunModify();
    else if(costfunction==ORIGIN)
        costFunOrigin();
}

void Iscissor::costFunOrigin()
{
    Mat cvimg;
    QImageToCVMat(*img,cvimg);
    Mat gray(cvimg.rows,cvimg.cols,CV_8U);
    cvtColor(cvimg,gray,CV_RGB2GRAY);
    Mat lap(cvimg.rows,cvimg.cols,CV_64F);
    Laplacian(cvimg,lap,CV_64F);
    Mat sobx(cvimg.rows,cvimg.cols,CV_64F);
    Mat soby(cvimg.rows,cvimg.cols,CV_64F);
    Sobel(cvimg,sobx,CV_64F,1,0);
    Sobel(cvimg,soby,CV_64F,0,1);
    Mat grad(cvimg.rows,cvimg.cols,CV_64F);
    Mat fz(cvimg.rows,cvimg.cols,CV_64F);
    Mat fg(cvimg.rows,cvimg.cols,CV_64F);
    Mat D(cvimg.rows,cvimg.cols,CV_64FC2);
    double maxG=0;
    for(int i=0;i<cvimg.rows;i++)
        for(int j=0;j<cvimg.cols;j++)
        {
            double dx=sobx.at<double>(i,j);
            double dy=soby.at<double>(i,j);
            double g=sqrt(dx*dx+dy*dy);
            grad.at<double>(i,j)=g;
            if(maxG<g)
                maxG=g;
            D.at<Vec2d>(i,j)=Vec2d(dy/g,-dx/g);
        }
    for(int i=0;i<cvimg.rows;i++)
        for(int j=0;j<cvimg.cols;j++)
        {
            fz.at<double>(i,j)=abs(lap.at<double>(i,j))<0.01?0:1;
            fg.at<double>(i,j)=1-grad.at<double>(i,j)/maxG;

        }
    double wz=0.43,wd=0.43,wg=0.14;
    for(int i=0;i<cvimg.rows;i++)
        for(int j=0;j<cvimg.cols;j++)
        {
            PixelNode *pn=pixelnodes[i][j];
            for(int k=0;k<8;k++)
            {
                int c,r;
                pn->Neighbor(k,c,r);
                if(c>=0&&c<cvimg.cols&&r>=0&&r<cvimg.rows)
                {
                    Vec2d l(i-r,j-c);
                    double dp=l.dot(D.at<double>(i,j));
                    if(dp<0)
                    {
                        l=-l;
                        dp=-dp;
                    }
                    double dq=l.dot(D.at<double>(r,c));
                    double fd=(acos(dp)+acos(dq))/CV_PI;
                    pn->setLinkCost(k,wz*fz.at<double>(r,c)+wg*fg.at<double>(r,c)+wd*fd);
                }
            }
        }
}

void Iscissor::setMask(const QImage &m)
{
    mask=m;
}

QPoint Iscissor::snapSeed(int column, int row)
{
    Mat cvimg;
    QImageToCVMat(*img,cvimg);
    Mat gray(cvimg.rows,cvimg.cols,CV_8U);
    cvtColor(cvimg,gray,CV_RGB2GRAY);
    Mat edge;
    Canny(gray,edge,31,127,3,true);
    double m=DBL_MAX;
    int c=column,r=row;
    for(int i=0;i<edge.rows;i++)
        for(int j=0;j<edge.cols;j++)
            if(edge.at<uchar>(i,j)!=0)
            {
                double d=(i-row)*(i-row)+(j-column)*(j-column);
                if(d<m)
                {
                    m=d;
                    c=j;
                    r=i;
                }
            }
    //setSeed(c,r);
    return QPoint(c,r);
}
