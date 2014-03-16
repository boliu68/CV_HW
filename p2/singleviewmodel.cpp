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
void Vertex::setID(int i)
{
    id=i;
}
int Vertex::ID()
{
    return id;
}
double Vertex::getDistance(const cv::Point2d &p)
{
    cv::Point2d d=coor2d-p;
    return norm(d);
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

cv::Vec3b SingleViewModel::getLine(const cv::Point2d &p1, const cv::Point2d &p2)
{
    cv::Point3d hp1(p1.x,p1.y,1.0);
    cv::Point3d hp2(p2.x,p2.y,1.0);
    return hp1.cross(hp2);
}

cv::Point2d SingleViewModel::computeVanish(const vector<pair<cv::Point2d,cv::Point2d> > &lines,VANISH v)
{
    cv::POint2d vanish=getOneVanish(lines);
    if(v==Xv)
        vx=vanish;
    else if(v=Yv)
        vy=vanish;
    else vz=vanish;
    return vanish;
}

void SingleViewModel::initialVertex(Vertex *ver, const cv::Point2 &c2, const cv::Point &c3, Vertex::LOC loc)
{
    ver=new Vertex(c2);
    ver->setCoor3d(c3);
    ver->setLocation(Loc);
    vertexs.push_back(ver);
    ver->setID(vertexs.size()-1);
}

void SingleViewModel::setOrigin(const cv::Point2d &p)
{
    initialVertex(origin,p,cv::Point3d(0.0,0.0,0.0),Vertex::LOC::BOTTOM);
}

cv::Point2d SingleViewModel::findPointOnDirection(const cv::Point2d &p, VANISH v)
{
    cv::POint2d vanish;
    if(v==Xv)
        vanish=vx;
    else if(v=Yv)
        vanish=vy;
    else vanish=vz;
    cv::Vec3d line=getLine(origin->Coor2d(),v);
    cv::Vec3d vl(line[1],-line[0],line[0]*p.y-line[1]*p.x);
    cv::Vec3d np=line.cross(vl);
    cv::Point2d np2(np[0]/np[2],np[1]/np[2]);
    return np2;
}

void SingleViewModel::setReferencePoints(const cv::Point2d &x, const cv::Point2d &y, const cv::Point2d &z,
                                         double xlength, double ylength, double zlength,
                                         Vertex *xver, Vertex *yver, Vertex *zver)
{
    initialVertex(xver,x,cv::Point3d(xlength,0.0,0.0),Vertex::LOC::BOTTOM);
    initialVertex(yver,y,cv::Point3d(0.0,ylength,0.0),Vertex::LOC::BOTTOM);
    initialVertex(zver,z,cv::Point3d(0.0,0.0,zlength),Vertex::LOC::BOTTOM);
    reference=zver;
    reLine=getLine(origin->Coor2d(),reference->Coor2d());
    lxy=getLine(vx,vy);
    vector<cv::Point3d> src,dst;
    src.push_back(origin->Coor2d());
    src.push_back(x);
    cv::Vec3d xline=getLine(y,vx);
    cv::Vec3d yline=getLine(x,vy);
    cv::Vec3d p=xline.cross(yline);
    src.push_back(cv::Point2d(p[0]/p[2],p[1]/p[2]));
    dst.push_back(cv::POint2d(0.0,0.0));
    dst.push_back(cv::POint2d(xlength,0.0));
    dst.push_back(cv::POint2d(xlength,ylength));
    dst.push_back(cv::POint2d(0.0,ylength));
    Homography=cv::getPerspectiveTransform(src,dst);
    refHeight=zlength;
}

Vertex* SingleViewModel::findNearestVertex(const cv::Point2d &p)
{
    double m=vertexs[0]->getDistance(p);
    int index=0;
    for(int i=1;i<vertexs.size();i++)
    {
        double d=vertexs[1]->getDistance(p);
        if(d<m)
        {
            m=d;
            index=i;
        }
    }
    return vertexs[index];
}

Face* SingleViewModel::findFace(const cv::Point2d &p)
{
    int index=-1;
    double m=DBL_MAX;
    for(int i=0;i<faces.size();i++)
    {
        Face* f=faces[i];
        if(f->inFace(p)&&f->Area()<m)
        {
            m=f->Area();
            index=i;
        }
    }
    if(index==-1)
        return NULL;
    return faces[index];
}
