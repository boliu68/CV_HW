#ifndef HELPER_H
#define HELPER_H
#include<iostream>
#include<QImage>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
void transQColorFormat(QRgb qrgb, int color[3])
{
    color[0]=qRed(qrgb);
    color[1]=qGreen(qrgb);
    color[2]=qBlue(qrgb);
}
void transQColorFormat(QRgb qrgb, cv::Vec3d color)
{
    color[0]=qRed(qrgb);
    color[1]=qGreen(qrgb);
    color[2]=qBlue(qrgb);
}
void QImageToCVMat(const QImage &qimg,Mat &cvimg)
{
    cvimg.create(qimg.height(),qimg.width(),CV_8UC3);
    int h=qimg.height(),w=qimg.width();
    for(int i=0;i<h;i++)
        for(int j=0;j<w;j++)
        {
            int color[3];
            transQColorFormat(qimg.pixel(j,i),color);
            cvimg.at<Vec3b>(i,j)=Vec3b(color[0],color[1],color[2]);
        }
}
void visualCVMat(const Mat& img, const string & prefix)
{
    double mmax=DBL_MIN;
    double mmin=DBL_MAX;
    for(int i=0;i<img.rows;i++)
        for(int j=0;j<img.cols;j++)
        {
            double v=img.at<double>(i,j);
            if(v>mmax) mmax=v;
            if(v<mmin) mmin=v;
        }
    Mat show=(img-mmin)/(mmax-mmin);
    imshow(prefix+".jpg",show);
}

void visualCVMatC2(const Mat& img, const string & prefix)
{
    double mmax1=DBL_MIN,mmax2=DBL_MIN;
    double mmin1=DBL_MAX,mmin2=DBL_MAX;
    for(int i=0;i<img.rows;i++)
        for(int j=0;j<img.cols;j++)
        {
            Vec2d v=img.at<Vec2d>(i,j);
            if(v[0]>mmax1) mmax1=v[0];
            if(v[0]<mmin1) mmin1=v[0];
            if(v[1]>mmax2) mmax2=v[1];
            if(v[1]<mmin2) mmin2=v[1];
        }
    Mat show1(img.rows,img.cols,CV_64F);
    Mat show2(img.rows,img.cols,CV_64F);
    for(int i=0;i<img.rows;i++)
        for(int j=0;j<img.cols;j++)
        {
            Vec2d v=img.at<Vec2d>(i,j);
            show1.at<double>(i,j)=(v[0]-mmin1)/(mmax1-mmin1);
            show2.at<double>(i,j)=(v[1]-mmin2)/(mmax2-mmin2);
        }
    imshow(prefix+"1.jpg",show1);
    imshow(prefix+"2.jpg",show2);
}


#endif // HELPER_H
