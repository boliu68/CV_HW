#include "singleviewmodel.h"

cv::poin2d Vertex::Coor2d()
{
    return coor2d;
}
cv::Point3d Vertex::Coor3d()
{
    return coor3d;
}
Vertex::Vertex(const cv::Point2d &c2)
{
    coor2d=c2;
    neighbor=NULL;
}

bool Vertex::sameVertex(const cv::Point2d &p)
{
    cv::Point2d d=p-coor2d;
    if(d.ddot(d)<0.001)
        return true;
    return false;
}

Vertex::LOC Vertex::Location()
{
    return location;
}

void Vertex::setCoor3d(const cv::Point3d &c3)
{
    coor3d=c3;
}
void Vertex::setLocation(LOC l)
{
    location=l;
}
void Vertex::setNeighbor(Vertex *v)
{
    neighbor=v;
}
Vertex* Vertex::Neighbor()
{
    return neighbor;
}

Face::Face(const vector<Vertex *> &vs)
{
    vertexs=vs;
    ground=true;
    for(int i=0;i<4;i++)
        for(int j=i+1;j<4;j++)
        {
            cv::Point3d p1=vertexs[i]->Coor3d();
            cv::Point3d p2=vertexs[j]->Coor3d();
            if(abs(p1.z-p2.z)>0.001)
                ground=false;
        }
    if(ground)
    {
        height=0;
        for(int i=0;i<4;i++)
            height+=vertexs[i]->Coor3d().z;
        height/=4.0;
    }
    cv::Vec2d d1=vertexs[1]->Coor2d()-vertexs[0]->Coor2d();
    cv::Vec3d d2=vertexs[3]->Coor2d()-vertexs[0]->Coor2d();
    cv::Vec3d d3=d1.cross(d2);
    area=cv::norm(d3);
}

Vertex* Face::getVertex(int ID)
{
    return vertexs[ID];
}

bool Face::paraToGround()
{
    return ground;
}

double Face::Height()
{
    return height;
}

double Face::Area()
{
    return area;
}

double Face::triangleArea(const cv::Point2d &p1, const cv::Point2d &p2, const cv::Point2d &p3)
{
    cv::Vec3d d1=p2-p1;
    cv::Vec3d d2=p3-p1;
    cv::Vec3d d3=d1.cross(d2);
    return norm(d3);
}

bool Face::inFace(const cv::Point2d &p)
{
    double sum=0.0;
    for(int i=0;i<4;i++)
        sum+=triangleArea(p,vertexs[i]->coor2d(),vertexs[(i+1)%4]->coor2d);
    if(abs(sum-area)<0.0000001)
        return true;
}

SingleViewModel::SingleViewModel(QImage *image)
{
    img=image;
}

cv::Point3d SingleViewModel::Normalize(const cv::Point2d &p)
{
    cv::Point3d np;
    np.x=p.x-img->width()/2.0;
    np.y=p.y-img->height()/2.0;
    np.z=(img->width()+img->height())/4.0;
    return np;
}

cv::Point2d SingleViewModel::Denormalize(const cv::Point3d &np)
{
    cv::Point2d p;
    p.x=np.x/np.z*(img->width()+img->height())/4.0+img->width()/2.0;
    p.y=np.y/np.z*(img->width()+img->height())/4.0+img->height()/2.0;
}

cv::Point2d SingleViewModel::getOneVanish(const vector<pair<cv::Point2d, cv::Point2d> > &lines)
{
    cv::Mat A=cv::Mat::zeros(3,3,CV_64F);
    vector<cv::Vec3d> ls;
    ls.resize(lines.size());
    for(int i=0;i<lines.size();i++)
    {
        cv::Point3d p1=Normalize(lines[i].first);
        cv::Point3d p2=Normalize(lines[i].second);
        ls[i]=p1.cross(p2);
    }
    for(int i=0;i<ls.size();i++)
        for(int j=0;j<3;j++)
            for(int k=0;k<3;k++)
                A.at<double>(j,k)+=ls[i][j]*ls[i][k];
    vector<double> eigenvalues;
    cv::Mat eigenvectors;
    cv::eigen(A,eigenvalues,eigenvectors);
    int index=0;
    double m=eigenvalues[0];
    for(int i=1;i<eigenvalues.size();i++)
        if(eigenvalues[i]<m)
        {
            m=eigenvalues[i];
            index=i;
        }
    cv::Point3d v;
    v.x=eigenvectors.at<double>(index,0);
    v.y=eigenvectors.at<double>(index,1);
    v.z=eigenvectors.at<double>(index,2);
    return Denormalize(v);
}

void SingleViewModel::getVanishs(const vector<pair<cv::Point2d, cv::Point2d> > &xlines,
                                 const vector<pair<cv::Point2d, cv::Point2d> > &ylines,
                                 const vector<pair<cv::Point2d, cv::Point2d> > &zlines)
{
    vx=getOneVanish(xlines);
    vy=getOneVanish(ylines);
    vz=getOneVanish(zlines);
}
