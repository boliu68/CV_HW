#include "singleviewmodel.h"
#include "helper.h"
#include <fstream>

cv::Point2d Vertex::Coor2d()
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
    bottom=NULL;
}

bool Vertex::sameVertex(const cv::Point2d &p)
{
    cv::Point2d d=p-coor2d;
    if(d.ddot(d)<0.001)
        return true;
    return false;
}

void Vertex::setCoor3d(const cv::Point3d &c3)
{
    coor3d=c3;
}

void Vertex::setBottom(Vertex *v)
{
    bottom=v;
}
bool Vertex::isBottom()
{
    return bottom==NULL;
}

Vertex* Vertex::Bottom()
{
    return bottom;
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
    return cv::norm(d);
}

Face::Face(const vector<Vertex *> &vs)
{
    vertexs=vs;
    if(isVerticalLine(vertexs[0],vertexs[1])||isVerticalLine(vertexs[2],vertexs[3]))
    {
        vertical=true;
        for(int i=1;i<5;i++)
            vertexs.push_back(vs[i%4]);
    }
    else if(isVerticalLine(vertexs[0],vertexs[3])||isVerticalLine(vertexs[1],vertexs[2]))
    {
        vertical=true;
        vertexs=vs;
    }
    else
    {
        vertical=false;
        vertexs=vs;
    }
    ground=true;
    for(int i=0;i<4;i++)
        for(int j=i+1;j<4;j++)
        {
            cv::Point3d p1=vertexs[i]->Coor3d();
            cv::Point3d p2=vertexs[j]->Coor3d();
            if(abs(p1.z-p2.z)>0.1)
                ground=false;
        }
    if(ground)
    {
        height=0;
        for(int i=0;i<4;i++)
            height+=vertexs[i]->Coor3d().z;
        height/=4.0;
    }  
    computeArea();
}

bool Face::Vertical()
{
    return vertical;
}

bool Face::isVerticalLine(Vertex *v1, Vertex *v2)
{
    if(v1->Bottom()==NULL&&v2->Bottom()==v1)
        return true;
    if(v1->Bottom()==v2&&v2->Bottom()==NULL)
        return true;
    if(v1->Bottom()!=NULL&&v1->Bottom()==v2->Bottom())
        return true;
    return false;
}

Vertex* Face::getVertex(int _ID)
{
    if(_ID>=4) return vertexs[_ID%4];
    else if(_ID<0) return vertexs[_ID+4];
    return vertexs[_ID];
}

string Face::TexFileName()
{
    return textureFileName;
}

int Face::ID()
{
    return id;
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

void Face::computeArea()
{
    cv::Vec2d d1=vertexs[1]->Coor2d()-vertexs[0]->Coor2d();
    cv::Vec2d d2=vertexs[3]->Coor2d()-vertexs[0]->Coor2d();
    cv::Vec2d d3=vertexs[1]->Coor2d()-vertexs[2]->Coor2d();
    cv::Vec2d d4=vertexs[3]->Coor2d()-vertexs[2]->Coor2d();
    cv::Vec3d D1(d1[0],d1[1],0);
    cv::Vec3d D2(d2[0],d2[1],0);
    cv::Vec3d D3(d3[0],d3[1],0);
    cv::Vec3d D4(d4[0],d4[1],0);
    area=(cv::norm(D1.cross(D2))+cv::norm(D3.cross(D4)))/2;
}

double Face::RealArea()
{
    cv::Vec2d d1=realvertexs[1]->Coor2d()-realvertexs[0]->Coor2d();
    cv::Vec2d d2=realvertexs[3]->Coor2d()-realvertexs[0]->Coor2d();
    cv::Vec2d d3=realvertexs[1]->Coor2d()-realvertexs[2]->Coor2d();
    cv::Vec2d d4=realvertexs[3]->Coor2d()-realvertexs[2]->Coor2d();
    cv::Vec3d D1(d1[0],d1[1],0);
    cv::Vec3d D2(d2[0],d2[1],0);
    cv::Vec3d D3(d3[0],d3[1],0);
    cv::Vec3d D4(d4[0],d4[1],0);
    return (cv::norm(D1.cross(D2))+cv::norm(D3.cross(D4)))/2;
}

void Face::setRealVertexs(const vector<Vertex *> &vs)
{
    realvertexs=vs;
}

double Face::triangleArea(const cv::Point2d &p1, const cv::Point2d &p2, const cv::Point2d &p3)
{
    cv::Vec2d d1=p2-p1;
    cv::Vec2d d2=p3-p1;
    cv::Vec3d D1(d1[0],d1[1],0);
    cv::Vec3d D2(d2[0],d2[1],0);
    cv::Vec3d d3=D1.cross(D2);
    return cv::norm(d3)/2.0;
}

bool Face::inFace(const cv::Point2d &p)
{
    double sum=0.0;
    for(int i=0;i<4;i++)
        sum+=triangleArea(p,vertexs[i]->Coor2d(),vertexs[(i+1)%4]->Coor2d());
    if(abs(sum-area)<0.00001)
        return true;
    return false;
}

SingleViewModel::SingleViewModel(QImage *image)
{
    img=image;
    origin=NULL;
    referP=NULL;
}

cv::Point3d SingleViewModel::Normalize(const cv::Point2d &p)
{
    cv::Point3d np;
    np.x=p.x-img->width()/2.0;
    np.y=p.y-img->height()/2.0;
    np.z=(img->width()+img->height())/4.0;
    return np;
}

cv::Point3d SingleViewModel::Denormalize(const cv::Point3d &np)
{
    cv::Point3d p;
    p.x=np.x*(img->width()+img->height())/4.0+img->width()/2.0*np.z;
    p.y=np.y*(img->width()+img->height())/4.0+img->height()/2.0*np.z;
    p.z=np.z;
    return p;
}

cv::Point3d SingleViewModel::getOneVanish(const vector<pair<cv::Point2d, cv::Point2d> > &lines)
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

cv::Vec3d SingleViewModel::getLine(const cv::Point2d &p1, const cv::Point2d &p2)
{
    cv::Point3d hp1(p1.x,p1.y,1.0);
    cv::Point3d hp2(p2.x,p2.y,1.0);
    return hp1.cross(hp2);
}

cv::Vec3d SingleViewModel::getLine(const cv::Point3d &p1, const cv::Point2d &p2)
{
    cv::Point3d hp2(p2.x,p2.y,1.0);
    return p1.cross(hp2);
}

cv::Vec3d SingleViewModel::getLine(const cv::Point2d &p1, const cv::Point3d &p2)
{
    cv::Point3d hp1(p1.x,p1.y,1.0);
    return p2.cross(hp1);
}

cv::Vec3d SingleViewModel::getLine(const cv::Point3d &p1, const cv::Point3d &p2)
{
    return p2.cross(p1);
}

cv::Point3d SingleViewModel::computeVanish(const vector<pair<cv::Point2d,cv::Point2d> > &lines,VANISH v)
{
    if(lines.size()<2)
        return cv::Point3d(0,0,0);
    cv::Point3d vanish=getOneVanish(lines);
    if(v==Xv)
        vx=vanish;
    else if(v==Yv)
        vy=vanish;
    else vz=vanish;
    return vanish;
}

Vertex* SingleViewModel::initialVertex(const Point2d &c2, const Point3d &c3, Vertex *bottom)
{
    Vertex* ver=new Vertex(c2);
    ver->setCoor3d(c3);
    ver->setBottom(bottom);
    vertexs.push_back(ver);
    ver->setID(vertexs.size()-1);
    return ver;
}

Vertex *SingleViewModel::setOrigin(const cv::Point2d &p)
{
    lxy=getLine(vx,vy);
    double d=abs(p.x*lxy[0]+p.y*lxy[1]+lxy[2])/sqrt(lxy[0]*lxy[0]+lxy[1]*lxy[1]);
    if(d<0.001) return NULL;
    origin=initialVertex(p,cv::Point3d(0.0,0.0,0.0));
    return origin;
}

cv::Point2d SingleViewModel::findPointOnDirection(const cv::Point2d &p, VANISH v)
{
    cv::Point3d vanish;
    if(v==Xv)
        vanish=vx;
    else if(v==Yv)
        vanish=vy;
    else vanish=vz;
    cv::Vec3d line=getLine(origin->Coor2d(),vanish);
    cv::Vec3d vl(line[1],-line[0],line[0]*p.y-line[1]*p.x);
    cv::Vec3d np=line.cross(vl);
    cv::Point2d np2(np[0]/np[2],np[1]/np[2]);
    return np2;
}

cv::Point2d SingleViewModel::findPointOnDirection(const cv::Point2d &p, const cv::Point2d &bottom)
{
    cv::Vec3d line=getLine(bottom,vz);
    cv::Vec3d vl(line[1],-line[0],line[0]*p.y-line[1]*p.x);
    cv::Vec3d np=line.cross(vl);
    cv::Point2d np2(np[0]/np[2],np[1]/np[2]);
    return np2;
}

void SingleViewModel::setReferencePoints(const cv::Point2d &x, const cv::Point2d &y, const cv::Point2d &z,
                                         double xlength, double ylength, double zlength,
                                         Vertex *&xver, Vertex *&yver, Vertex *&zver)
{
    xver=initialVertex(x,cv::Point3d(xlength,0.0,0.0));
    yver=initialVertex(y,cv::Point3d(0.0,ylength,0.0));
    zver=initialVertex(z,cv::Point3d(0.0,0.0,zlength),origin);
    referP=zver;
    referPx=xver;
    referPy=yver;
    refLine=getLine(origin->Coor2d(),referP->Coor2d());
    /*cv::Point2f src[4],dst[4];
    src[0]=origin->Coor2d();
    src[1]=x;
    cv::Vec3d xline=getLine(y,vx);
    cv::Vec3d yline=getLine(x,vy);
    cv::Vec3d p=xline.cross(yline);
    src[2].x=p[0]/p[2];src[2].y=p[1]/p[2];
    src[3]=y;
    dst[0].x=0;dst[0].y=0;
    dst[1].x=xlength;dst[1].y=0.0;
    dst[2].x=xlength;dst[2].y=ylength;
    dst[3].x=0;dst[3].y=ylength;
    Homography=cv::getPerspectiveTransform(src,dst);*/
    vector<cv::Point2d> src,dst;
    src.push_back(origin->Coor2d());
    src.push_back(x);
    cv::Vec3d xline=getLine(y,vx);
    cv::Vec3d yline=getLine(x,vy);
    cv::Vec3d p=xline.cross(yline);
    src.push_back(cv::Point2d(p[0]/p[2],p[1]/p[2]));
    src.push_back(y);
    dst.push_back(cv::Point2d(0,0));
    dst.push_back(cv::Point2d(xlength,0));
    dst.push_back(cv::Point2d(xlength,ylength));
    dst.push_back(cv::Point2d(0,ylength));
    Homography=computeHomography(src,dst);
    refHeight=zlength;
    refLine=getLine(origin->Coor2d(),z);
    getCameraInformation();
}

Vertex* SingleViewModel::findNearestVertex(const cv::Point2d &p)
{
    double m=vertexs[0]->getDistance(p);
    int index=0;
    for(int i=1;i<vertexs.size();i++)
    {
        double d=vertexs[i]->getDistance(p);
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
        if(!f->paraToGround())
            continue;
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


double SingleViewModel::getHeightOnRefLine(const cv::Point2d &p)
{
    double tb,vr,rb,vt;
    tb=cv::norm(p-origin->Coor2d());
    rb=cv::norm(referP->Coor2d()-origin->Coor2d());
    if(abs(vz.z)<0.0001)
        return tb/rb*refHeight;
    cv::Point2d Vz(vz.x/vz.z,vz.y/vz.z);
    vr=cv::norm(Vz-referP->Coor2d());
    vt=cv::norm(Vz-p);
    if((p-origin->Coor2d()).dot(referP->Coor2d()-origin->Coor2d())<0)
        return -tb*vr/rb/vt*refHeight;
    return tb*vr/rb/vt*refHeight;
}

cv::Point2d SingleViewModel::getPointOnRefLine(const cv::Point2d &bottom, const cv::Point2d &top)
{
    cv::Vec3d l=getLine(origin->Coor2d(),bottom);
    cv::Vec3d v=lxy.cross(l);
    cv::Vec3d l2=getLine(v,top);
    cv::Vec3d hp=l2.cross(refLine);
    cv::Point2d p;
    p.x=hp[0]/hp[2];p.y=hp[1]/hp[2];
    return p;
}

cv::Point2d SingleViewModel::getPointOnRefPlane(const cv::Point2d &p,Face* groundplane)
{
    int index;
    for(index=0;index<4;index++)
        if(!inSameLine(p,groundplane->getVertex(index)->Coor2d()
                     ,groundplane->getVertex(index+1)->Coor2d()))
            break;
    Vertex* ver1,*ver2;
    ver1=groundplane->getVertex(index);
    ver2=groundplane->getVertex(index+1);
    if(ver1->isBottom())
        return p;
    cv::Vec3d l1=getLine(p,ver1->Coor2d());
    cv::Vec3d v1=l1.cross(lxy);
    cv::Vec3d l1b=getLine(v1,ver1->Bottom()->Coor2d());
    cv::Vec3d l2=getLine(p,ver2->Coor2d());
    cv::Vec3d v2=l2.cross(lxy);
    cv::Vec3d l2b=getLine(v2,ver2->Bottom()->Coor2d());
    cv::Vec3d hpr=l1b.cross(l2b);
    cv::Point2d pb;
    pb.x=hpr[0]/hpr[2];pb.y=hpr[1]/hpr[2];
    return pb;
}

bool SingleViewModel::inSameLine(const cv::Point2d &p1, const cv::Point2d &p2, const cv::Point2d &p3)
{
    cv::Point2d d1=p1-p2;
    cv::Point2d d2=p2-p3;
    if(abs(d1.x*d2.y-d1.y*d2.x)<0.0001)
        return true;
    return false;
}

Vertex* SingleViewModel::compute3DCoordinate(Vertex *bottom, const cv::Point2d &top)
{
    cv::Point2d topInref=top;
    Vertex* realBot=bottom;
    if(!bottom->isBottom())
        realBot=bottom->Bottom();
    if(realBot!=origin)
        topInref=getPointOnRefLine(realBot->Coor2d(),top);
    double h=getHeightOnRefLine(topInref);
    cv::Point3d coor3d=bottom->Coor3d();
    coor3d.z=h;
    Vertex* newVer=initialVertex(top,coor3d,realBot);
    return newVer;
}

Vertex* SingleViewModel::compute3DCoordinateofBottom(const Point2d &bottom)
{
    Face* gp=findFace(bottom);
    cv::Point2d realBot=bottom;
    if(gp!=NULL)
        realBot=getPointOnRefPlane(bottom,gp);
    cv::Point3d realBot3d=get3DPointOnRefPlane(realBot);
    cv::Point3d bottom3d=realBot3d;
    Vertex* realBotVer;
    if(gp!=NULL)
    {
        realBotVer=new Vertex(realBot);
        realBotVer->setCoor3d(realBot3d);
        virtualVers.push_back(realBotVer);
        realBotVer->setID(-(virtualVers.size()-1)-1);
        bottom3d.z=gp->Height();
    }
    Vertex* vbottom=initialVertex(bottom,bottom3d);
    if(gp!=NULL)
        vbottom->setBottom(realBotVer);
    return vbottom;
}

void SingleViewModel::compute3DCoordinate(const cv::Point2d &bottom, const cv::Point2d &top,
                                          Vertex *&vbottom, Vertex *&vtop)
{
    vbottom=compute3DCoordinateofBottom(bottom);
    vtop=compute3DCoordinate(vbottom,top);
}

cv::Point3d SingleViewModel::get3DPointOnRefPlane(const cv::Point2d &p)
{
    cv::Mat hp(3,1,CV_64F);
    hp.at<double>(0)=p.x;hp.at<double>(1)=p.y;hp.at<double>(2)=1;
    cv::Mat hpRef=Homography*hp;
    cv::Point3d result;
    result.x=hpRef.at<double>(0)/hpRef.at<double>(2);
    result.y=hpRef.at<double>(1)/hpRef.at<double>(2);
    result.z=0.0;
    return result;
}

cv::Point2d SingleViewModel::getPointOnImage(const cv::Point2d &p)
{
    cv::Mat hpRef(3,1,CV_64F);
    hpRef.at<double>(0)=p.x;hpRef.at<double>(1)=p.y;hpRef.at<double>(2)=1;
    cv::Mat hp=Homography.inv()*hpRef;
    cv::Point2d result;
    result.x=hp.at<double>(0)/hp.at<double>(2);
    result.y=hp.at<double>(1)/hp.at<double>(2);
    return result;
}

QImage Face::Texture()
{
    return *texture;
}

Face* SingleViewModel::generateFace(const vector<Vertex *> &vers)
{
    if(vers.size()<3||vers.size()>4)
        return NULL;
    Face *face;
    if(vers.size()==3)
    {
        bool check=false;
        if(vers[0]->Bottom()==NULL&&vers[1]->Bottom()==NULL&&vers[2]->Bottom()==NULL)
            check=true;
        if(vers[0]->Bottom()!=NULL&&vers[1]->Bottom()!=NULL&&vers[2]->Bottom()!=NULL)
        {
            check=true;
            for(int i=0;i<3;i++)
                for(int j=i+1;j<3;j++)
                    if(vers[i]->Bottom()==vers[j]->Bottom())
                        check=false;
        }
        if(!check) return NULL;
        face=generateFaceFrom3Points(vers);
    }
    if(vers.size()==4)
        face=new Face(vers);
    getFaceTexture(face);
    faces.push_back(face);
    face->id=faces.size()-1;
    face->Texture().save("debug.jpg");
    return face;
}

Face* SingleViewModel::generateFaceFrom3Points(const vector<Vertex *> &vers)
{
    cv::Point3d d1=vers[0]->Coor3d()-vers[1]->Coor3d();
    cv::Point3d d2=vers[2]->Coor3d()-vers[1]->Coor3d();
    cv::Point3d p3d=vers[1]->Coor3d()+d1+d2;
    cv::Point2d p2d=compute2DCoordinate(p3d);
    Vertex* pVer=initialVertex(p2d,p3d);
    if(abs(p3d.z)>0.0001)
    {
        cv::Point3d pb3d=p3d;
        pb3d.z=0;
        cv::Point2d pb2d=compute2DCoordinate(pb3d);
        Vertex* newBotVer=new Vertex(pb2d);
        newBotVer->setCoor3d(pb3d);
        virtualVers.push_back(newBotVer);
        newBotVer->setID(-(virtualVers.size()-1)-1);
        pVer->setBottom(newBotVer);
    }
    /*cv::Point3d pb3d=p3d;
    pb3d.z=0;
    Vertex* pVer;
    if(vers[1]->Bottom()!=NULL)
    {
        cv::Vec3d bd1,bd2;
        bd1=vers[1]->Bottom()->Coor3d()-pb3d;
        bd2=vers[2]->Bottom()->Coor3d()-pb3d;
        cv::Vec3d v1,v2;
        v1=getPointOnImage(bd1);
        v2=getPointOnImage(bd2);
        cv::Vec3d l1,l2;
        l1=getLine(v1,vers[1]->Coor2d());
        l2=getLine(v2,vers[2]->Coor2d());
        cv::Vec3d hp2d=l1.cross(l2);
        cv::Point2d p2d(hp2d[0]/hp2d[2],hp2d[1]/hp2d[2]);
        l1=getLine(v1,vers[1]->Bottom()->Coor2d());
        l2=getLine(v2,vers[2]->Bottom()->Coor2d());
        cv::Vec3d hpb2d=l1.cross(l2);
        cv::Point2d pb2d(hpb2d[0]/hpb2d[2],hpb2d[1]/hpb2d[2]);
        Vertex* newBotVer=new Vertex(pb2d);
        newBotVer->setCoor3d(pb3d);
        virtualVers.push_back(newBotVer);
        newBotVer->setID(-(virtualVers.size()-1)-1);
        pVer=initialVertex(p2d,p3d,newBotVer);
    }
    else
    {
        cv::Point3d hp2d=getPointOnImage(pb3d);
        cv::Point2d p2d(hp2d.x/hp2d.z,hp2d.y/hp2d.z);
        pVer=initialVertex(p2d,pb3d);
    }*/
    vector<Vertex*> facevers=vers;
    facevers.push_back(pVer);
    Face *face=new Face(facevers);
    return face;
}

void SingleViewModel::getFaceTexture(Face *face)
{
    vector<Vertex*> vers;
    if(face->Vertical())
    {
        double d1=cv::norm(face->getVertex(0)->Coor3d()-face->getVertex(3)->Coor3d());
        double d2=cv::norm(face->getVertex(1)->Coor3d()-face->getVertex(2)->Coor3d());
        if(d1<d2)
        {
            cv::Point3d p03d(face->getVertex(0)->Coor3d().x,face->getVertex(0)->Coor3d().y,face->getVertex(1)->Coor3d().z);
            cv::Point3d p33d(face->getVertex(3)->Coor3d().x,face->getVertex(3)->Coor3d().y,face->getVertex(2)->Coor3d().z);
            /*cv::Point3d d=p03d-face->getVertex(1)->Coor3d();
            cv::Point3d v=getPointOnImage(d);
            cv::Vec3d l1,l2;
            l1=getLine(v,face->getVertex(1)->Coor2d());
            l2=getLine(v,face->getVertex(2)->Coor2d());
            l3=getLine(face->getVertex(0)->Coor2d(),face->getVertex(3)->Coor2d());
            cv::Vec3d hp02d,hp32d;
            hp02d=l1.cross(l3);hp32d=l2.cross(l3);
            cv::Point2d p02d(hp02d[0]/hp02d[2],hp02d[1]/hp02d[2]);
            cv::Point2d p32d(hp32d[0]/hp32d[2],hp32d[1]/hp32d[2]);*/
            cv::Point2d p02d=compute2DCoordinate(p03d);
            cv::Point2d p32d=compute2DCoordinate(p33d);
            Vertex *ver0=new Vertex(p02d);ver0->setCoor3d(p03d);
            Vertex *ver3=new Vertex(p32d);ver3->setCoor3d(p33d);
            vers.push_back(ver0);vers.push_back(face->getVertex(1));
            vers.push_back(face->getVertex(2));vers.push_back(ver3);
            face->setRealVertexs(vers);
            virtualVers.push_back(ver0);ver0->setID(-(virtualVers.size()+1));
            virtualVers.push_back(ver3);ver3->setID(-(virtualVers.size()+1));
        }
        else
        {
            cv::Point3d p13d(face->getVertex(1)->Coor3d().x,face->getVertex(1)->Coor3d().y,face->getVertex(0)->Coor3d().z);
            cv::Point3d p23d(face->getVertex(2)->Coor3d().x,face->getVertex(2)->Coor3d().y,face->getVertex(3)->Coor3d().z);
            /*cv::Point3d d=p13d-face->getVertex(0)->Coor3d();
            cv::Point3d v=getPointOnImage(d);
            cv::Vec3d l1,l2;
            l1=getLine(v,face->getVertex(0)->Coor2d());
            l2=getLine(v,face->getVertex(3)->Coor2d());
            l3=getLine(face->getVertex(1)->Coor2d(),face->getVertex(2)->Coor2d());
            cv::Vec3d hp12d,hp22d;
            hp12d=l1.cross(l3);hp22d=l2.cross(l3);
            cv::Point2d p12d(hp12d[0]/hp12d[2],hp12d[1]/hp12d[2]);
            cv::Point2d p22d(hp22d[0]/hp22d[2],hp22d[1]/hp22d[2]);*/
            cv::Point2d p12d=compute2DCoordinate(p13d);
            cv::Point2d p22d=compute2DCoordinate(p23d);
            Vertex *ver1=new Vertex(p12d);ver1->setCoor3d(p13d);
            Vertex *ver2=new Vertex(p22d);ver2->setCoor3d(p23d);
            vers.push_back(face->getVertex(0));vers.push_back(ver1);
            vers.push_back(ver2);vers.push_back(face->getVertex(3));
            virtualVers.push_back(ver1);ver1->setID(-(virtualVers.size()+1));
            virtualVers.push_back(ver2);ver2->setID(-(virtualVers.size()+1));
        }
    }
    else
    {
        int ver0id=face->vertexWithMinAngle();
        double d1,d2;
        d1=cv::norm(face->getVertex(ver0id+1)->Coor3d()-face->getVertex(ver0id)->Coor3d());
        d2=cv::norm(face->getVertex(ver0id-1)->Coor3d()-face->getVertex(ver0id)->Coor3d());
        Vertex *ver1=face->getVertex(ver0id);
        cv::Vec3d d;
        if(d1<d2)
            d=face->getVertex(ver0id-1)->Coor3d()-ver1->Coor3d();
        else
            d=face->getVertex(ver0id+1)->Coor3d()-ver1->Coor3d();
        d=d/cv::norm(d);
        Vertex *verfar2l=face->farestPoint2Line(d,ver1->Coor3d());
        Vertex *verfar2p=face->farestPoint2Plane(d,ver1->Coor3d());
        cv::Point3d p03d=getProjOnLine(ver1->Coor3d(),verfar2l->Coor3d(),d);
        cv::Point3d p23d=getProjOnPlane(ver1->Coor3d(),verfar2p->Coor3d(),d);
        cv::Point3d p33d=ver1->Coor3d()+(p03d-ver1->Coor3d())+(p23d-ver1->Coor3d());
        cv::Point2d p02d=compute2DCoordinate(p03d);
        cv::Point2d p22d=compute2DCoordinate(p23d);
        cv::Point2d p32d=compute2DCoordinate(p33d);
        Vertex *ver0=new Vertex(p02d);
        Vertex *ver2=new Vertex(p22d);
        Vertex *ver3=new Vertex(p32d);
        ver0->setCoor3d(p03d);ver2->setCoor3d(p23d);ver3->setCoor3d(p33d);
        vers.push_back(ver0);vers.push_back(ver1);
        vers.push_back(ver2);vers.push_back(ver3);
        virtualVers.push_back(ver0);ver0->setID(-(virtualVers.size()+1));
        virtualVers.push_back(ver2);ver2->setID(-(virtualVers.size()+1));
        virtualVers.push_back(ver3);ver3->setID(-(virtualVers.size()+1));
    }
    face->setRealVertexs(vers);
    computeTexture(face);
}

QRgb SingleViewModel::interpolate(const cv::Point2d &p)
{
    if(p.x<0||p.x>img->width()-1||p.y<0||p.y>img->height()-1)
        return qRgb(0,0,0);
    QPoint a(floor(p.x),floor(p.y));
    QPoint b(ceil(p.x),floor(p.y));
    QPoint c(ceil(p.x),ceil(p.y));
    QPoint d(floor(p.x),ceil(p.y));
    QRgb ac,bc,cc,dc;
    ac=img->pixel(a);bc=img->pixel(b);
    cc=img->pixel(c);dc=img->pixel(d);
    cv::Vec3d acv,bcv,ccv,dcv;
    transQColorFormat(ac,acv);transQColorFormat(bc,bcv);
    transQColorFormat(cc,ccv);transQColorFormat(dc,dcv);
    cv::Vec3d cv=acv*(p.x-a.x())*(p.y-b.y())+bcv*(b.x()-p.x)*(p.y-b.y())
            +ccv*(c.x()-p.x)*(c.y()-p.y)+dcv*(p.x-d.x())*(d.y()-p.y);
    return qRgb(cv[0],cv[1],cv[2]);
}

cv::Point2d SingleViewModel::getCorrespond(const QPoint &src, const Mat &H)
{
    Mat srcp(3,1,CV_64F);
    srcp.at<double>(0)=src.x();srcp.at<double>(1)=src.y();srcp.at<double>(2)=1;
    Mat dstp=H*srcp;
    return cv::Point2d(dstp.at<double>(0)/dstp.at<double>(2),dstp.at<double>(1)/dstp.at<double>(2));
}

void SingleViewModel::computeTexture(Face *face)
{
    //cv::Point2f src[4],dst[4];
    vector<cv::Point2d> src,dst;
    for(int i=0;i<4;i++)
        dst.push_back(face->realvertexs[i]->Coor2d());
    double w3d,h3d;
    w3d=cv::norm(face->realvertexs[1]->Coor3d()-face->realvertexs[0]->Coor3d());
    h3d=cv::norm(face->realvertexs[3]->Coor3d()-face->realvertexs[0]->Coor3d());
    double area2d=face->RealArea();
    double area3d=w3d*h3d;
    double scale=sqrt(area2d/area3d);
    int w=w3d*scale,h=h3d*scale;
    src.push_back(cv::Point2d(0,0));
    src.push_back(cv::Point2d(w,0));
    src.push_back(cv::Point2d(w,h));
    src.push_back(cv::Point2d(0,h));
    /*src[0].x=0;src[0].y=0;
    src[1].x=w;src[1].y=0;
    src[2].x=w;src[2].y=h;
    src[3].x=0;src[3].y=h;
    cv::Mat H=cv::getPerspectiveTransform(src,dst);*/
    cv::Mat H=computeHomography(src,dst);
    face->texture=new QImage(w,h,img->format());
    for(int x=0;x<w;x++)
        for(int y=0;y<h;y++)
        {
            QPoint p(x,y);
            cv::Point2d dstp=getCorrespond(p,H);
            face->texture->setPixel(p,interpolate(dstp));
        }
}

double Face::getAngle(int _ID)
{
    cv::Vec3d d1=vertexs[(_ID+1)%4]-vertexs[_ID];
    cv::Vec3d d2=vertexs[(_ID+3)%4]-vertexs[_ID];
    double cosa=d1.dot(d2)/cv::norm(d1)/cv::norm(d2);
    return acos(cosa);
}

int Face::vertexWithMinAngle()
{
    int index=0;
    double m=getAngle(0);
    for(int i=1;i<4;i++)
    {
        double angle=getAngle(i);
        if(angle<m)
        {
            m=angle;
            index=i;
        }
    }
    return index;
}

double Face::disPoint2Line(const Point3d &p, const Vec3d &d, const Point3d &begin)
{
    cv::Vec3d pb=p-begin;
    cv::Point3d l=(pb.dot(d))*d;
    cv::Vec3d proj=begin+l;
    return norm(pb-proj);
}

Vertex* Face::farestPoint2Line(const Vec3d &d, const Point3d &begin)
{
    int index=0;
    double m=disPoint2Line(vertexs[0]->Coor3d(),d,begin);
    for(int i=1;i<4;i++)
    {
        double dis=disPoint2Line(vertexs[i]->Coor3d(),d,begin);
        if(dis>m)
        {
            index=i;
            m=dis;
        }
    }
    return vertexs[index];
}

double Face::disPoint2Plane(const Point3d &p, const Vec3d &d, const Point3d &begin)
{
    cv::Vec3d pb=p-begin;
    return pb.dot(d);
}

Vertex* Face::farestPoint2Plane(const Vec3d &d, const Point3d &begin)
{
    int index=0;
    double m=disPoint2Plane(vertexs[0]->Coor3d(),d,begin);
    for(int i=1;i<4;i++)
    {
        double dis=disPoint2Plane(vertexs[i]->Coor3d(),d,begin);
        if(dis>m)
        {
            index=i;
            m=dis;
        }
    }
    return vertexs[index];
}

cv::Point3d SingleViewModel::getProjOnLine(const Point3d &p, const Point3d begin, const Vec3d &d)
{
    double t=d.dot(p-begin);
    return begin+t*Point3d(d);
}

cv::Point3d SingleViewModel::getProjOnPlane(const Point3d &p, const Point3d begin, const Vec3d &n)
{
    double t=n.dot(begin-p);
    return p+t*Point3d(n);
}

cv::Point2d SingleViewModel::compute2DCoordinate(const Point3d &p)
{
    if(p.z==0)
    {
        cv::Point2d p2d=getPointOnImage(cv::Point2d(p.x,p.y));
        return p2d;
    }
    cv::Point3d pb3d=p;
    pb3d.z=0;
    cv::Point2d pb2d=getPointOnImage(cv::Point2d(pb3d.x,pb3d.y));
    cv::Vec3d lb=getLine(pb2d,origin->Coor2d());
    cv::Vec3d v=lb.cross(lxy);
    double rb,t;
    rb=norm(referP->Coor2d()-origin->Coor2d());
    cv::Point2d pl2d;
    if(abs(vz.z)<0.0001)
    {
        rb=norm(referP->Coor2d()-origin->Coor2d());
        t=p.z*rb/refHeight;
    }
    else
    {
        double vzr,vzb;
        cv::Point2d Vz(vz.x/vz.z,vz.y/vz.z);
        vzr=norm(Vz-referP->Coor2d());
        vzb=norm(Vz-origin->Coor2d());
        t=p.z*rb*vzb/(refHeight*vzr+p.z*rb);
    }
    pl2d=origin->Coor2d()+t/rb*(referP->Coor2d()-origin->Coor2d());
    cv::Vec3d l=getLine(v,pl2d);
    cv::Vec3d lver=getLine(vz,pb2d);
    cv::Vec3d hp2d=l.cross(lver);
    return cv::Point2d(hp2d[0]/hp2d[2],hp2d[1]/hp2d[2]);
}

/*cv::Vec3d SingleViewModel::selectVanishLine(const cv::Point2d &p1, const cv::Point2d &p2)
{
    cv::Point3d v1,v2;
    if(inRegion(p1,p2,vx,vy))
        return lxy;

}

bool SingleViewModel::inRegion(const cv::Point2d &p1, const cv::Point2d &p2,
                               const cv::Point3d &v1, const cv::Point3d &v2)
{
    cv::Vec2d d1,d2;
    if(abs(v1.z)<0.0001)
    {
        d1[0]=v1.x;
        d1[1]=v1.y;
    }
    else
    {
        d1[0]=v1.x/v1.z-p1.x;
        d1[1]=v1.y/v1.z-p1.y;
    }
    if(abs(v2.z)<0.0001)
    {
        d2[0]=v2.x;
        d2[1]=v2.y;
    }
    else
    {
        d2[0]=v2.x/v2.z-p1.x;
        d2[1]=v2.y/v2.z-p1.y;
    }
    d1=d1/cv::norm(d1);
    d2=d2/cv::norm(d2);
    cv::Vec2d d=p2-p1;
    cv::Mat A(2,2,CV_64F),B(2,1,CV_64F),X(2,1,CV_64F);
    A.at<double>(0,0)=d1[0];A.at<double>(0,1)=d2[0];
    A.at<double>(1,0)=d1[1];A.at<double>(1,1)=d2[1];
    B.at<double>(0)=d[0];B.at<double>(1)=d[1];
    cv::solve(A,B,X,cv::DECOMP_SVD);
    if(X.at<double>(0)<0.0||X.at<double>(1)<0.0)
        return false;
    return true;
}*/

Vertex::~Vertex()
{
    bottom=NULL;
}

Face::~Face()
{
    for(int i=0;i<4;i++)
        vertexs[i]=NULL;
    vertexs.clear();
    delete texture;
    texture=NULL;
}

SingleViewModel::~SingleViewModel()
{
    for(int i=0;i<vertexs.size();i++)
    {
        delete vertexs[i];
        vertexs[i]=NULL;
    }
    vertexs.clear();
    for(int i=0;i<virtualVers.size();i++)
    {
        delete virtualVers[i];
        virtualVers[i]=NULL;
    }
    virtualVers.clear();
    for(int i=0;i<faces.size();i++)
    {
        delete faces[i];
        faces[i]=NULL;
    }
    faces.clear();
    origin=NULL;
    referP=NULL;
}

void SingleViewModel::getCameraInformation()
{
    cv::Mat Hinv=Homography.inv();
    cv::Vec3d p(referP->Coor2d().x,referP->Coor2d().y,1);
    cv::Vec3d p4(Hinv.at<double>(0,2),Hinv.at<double>(1,2),Hinv.at<double>(2,2));
    double a=cv::norm(p4.cross(p))/cv::norm(vz.cross(p))/refHeight;
    if(cv::norm(a*refHeight*p.cross(vz)+p.cross(p4))>0.0001)
        a=-a;
    cv::Mat P(3,4,CV_64F);
    cv::Vec3d P3=a*vz;
    for(int i=0;i<3;i++)
    {
        P.at<double>(i,0)=Hinv.at<double>(i,0);
        P.at<double>(i,1)=Hinv.at<double>(i,1);
        P.at<double>(i,2)=P3[i];
        P.at<double>(i,3)=Hinv.at<double>(i,2);
    }
    cv::decomposeProjectionMatrix(P,intrinsic,Rot,tran);
    cv::Mat C;
    cv::SVD::solveZ(P,C);
    camCenter.x=C.at<double>(0)/C.at<double>(3);
    camCenter.y=C.at<double>(1)/C.at<double>(3);
    camCenter.z=C.at<double>(2)/C.at<double>(3);
}

void SingleViewModel::generateVRMLCode(const string &prefix)
{
    for(int i=0;i<faces.size();i++)
    {
        Face *face=faces[i];
        char fID[20];
        sprintf(fID,"_%.3d.png",face->ID());
        string fname(fID);
        fname=prefix+fname;
        face->Texture().save(fname.c_str());
        face->textureFileName=fname;
    }
    string fname=prefix+".wrl";
    ofstream ofile(fname.c_str());
    ofile<<"#VRML V2.0 utf8"<<endl;
    ofile<<"Transform {"<<endl;
    ofile<<"  translation "<<camCenter.x<<" "<<camCenter.y<<" "<<camCenter.z<<endl;
    ofile<<"  children ["<<endl;
    ofile<<"    Shape {"<<endl;
    ofile<<"      geometry Sphere {"<<endl;
    ofile<<"        radius 0.15"<<endl;
    ofile<<"      }"<<endl;
    ofile<<"    }"<<endl;
    ofile<<"  ]"<<endl;
    ofile<<"}"<<endl;
    for(int i=0;i<faces.size();i++)
    {
        Face *face=faces[i];
        ofile<<"Shape{"<<endl;
        ofile<<"    appearance  Appearance{"<<endl;
        ofile<<"        texture  ImageTexture{"<<endl;
        ofile<<"           url \""<<face->TexFileName()<<"\""<<endl;
        ofile<<"        }"<<endl;
        ofile<<"    }"<<endl;
        ofile<<"    geometry IndexedFaceSet {"<<endl;
        ofile<<"       coord Coordinate {"<<endl;
        ofile<<"         point[";
        for(int j=3;j>0;j--)
        {
            cv::Point3d p=face->realvertexs[j]->Coor3d();
            ofile<<p.x<<" "<<p.y<<" "<<p.z<<", ";
        }
        cv::Point3d p=face->realvertexs[0]->Coor3d();
        ofile<<p.x<<" "<<p.y<<" "<<p.z<<"]"<<endl;
        ofile<<"       }"<<endl;
        ofile<<"       coordIndex [0,1,2,3,-1]"<<endl;
        ofile<<"       ccw TRUE"<<endl;
        ofile<<"       solid FALSE"<<endl;
        ofile<<"       texCoord TextureCoordinate {"<<endl;
        ofile<<"       point [0  0, 1  0, 1  1, 0  1]"<<endl;
        ofile<<"       }"<<endl;
        ofile<<"       texCoordIndex[0 1 2 3 -1]"<<endl;
        ofile<<"    }"<<endl;
        ofile<<"}"<<endl;
    }
}


bool SingleViewModel::saveCalibration(const string &prefix)
{
    string fname=prefix+"_calibration.txt";
    ofstream ofile(fname.c_str());
    if(!ofile.is_open())
        return false;
    ofile<<vx.x<<" "<<vx.y<<" "<<vx.z<<endl;
    ofile<<vy.x<<" "<<vy.y<<" "<<vy.z<<endl;
    ofile<<vz.x<<" "<<vz.y<<" "<<vz.z<<endl;
    ofile<<origin->Coor2d().x<<" "<<origin->Coor2d().y<<endl;
    ofile<<referPx->Coor2d().x<<" "<<referPx->Coor2d().y<<" "<<referPx->Coor3d().x<<endl;
    ofile<<referPy->Coor2d().x<<" "<<referPy->Coor2d().y<<" "<<referPy->Coor3d().y<<endl;
    ofile<<referP->Coor2d().x<<" "<<referP->Coor2d().y<<" "<<referP->Coor3d().z<<endl;
    return true;
}

bool SingleViewModel::loadCalibration(const string &path,Vertex *&_origin,
                                      Vertex *&xver, Vertex *&yver,Vertex *&zver
                                      ,cv::Point3d &vanishx,cv::Point3d &vanishy,cv::Point3d &vanishz)
{
    ifstream ifile(path.c_str());
    if(!ifile.is_open())
        return false;
    ifile>>vx.x>>vx.y>>vx.z;
    ifile>>vy.x>>vy.y>>vy.z;
    ifile>>vz.x>>vz.y>>vz.z;
    lxy=getLine(vx,vy);
    cv::Point2d o,px,py,p;
    double xl,yl,zl;
    ifile>>o.x>>o.y;
    ifile>>px.x>>px.y>>xl;
    ifile>>py.x>>py.y>>yl;
    ifile>>p.x>>p.y>>zl;
    setOrigin(o);
    setReferencePoints(px,py,p,xl,yl,zl,xver,yver,zver);
    vanishx=vx;vanishy=vy;vanishz=vz;
    _origin=origin;
    return true;
}

void SingleViewModel::compute3DCoordinateInPlane(Vertex *refer, const Point2d &top, Vertex *&vbottom, Vertex *&vtop)
{
    if(refer->isBottom())
    {
        vtop=compute3DCoordinateofBottom(top);
        vbottom=NULL;
        return;
    }
    cv::Vec3d ltvz=getLine(top,vz);
    cv::Vec3d lrt=getLine(refer->Coor2d(),top);
    cv::Vec3d v=lrt.cross(lxy);
    cv::Vec3d lvb=getLine(v,refer->Bottom()->Coor2d());
    cv::Vec3d hpb=lvb.cross(ltvz);
    cv::Point2d pb2d(hpb[0]/hpb[2],hpb[1]/hpb[2]);
    cv::Point3d pb3d=get3DPointOnRefPlane(pb2d);
    cv::Point3d p3d(pb3d.x,pb3d.y,refer->Coor3d().z);
    vbottom=initialVertex(pb2d,pb3d);
    vtop=initialVertex(top,p3d,vbottom);
}

cv::Mat SingleViewModel::computeHomography(const vector<cv::Point2d> &src,const vector<cv::Point2d> &dst)
{
    cv::Mat Tsrc=getNormalizeTransformation(src);
    cv::Mat Tdst=getNormalizeTransformation(dst);
    vector<cv::Mat> nsrc,ndst;
    for(int i=0;i<src.size();i++)
    {
        cv::Mat hs(3,1,CV_64F);
        hs.at<double>(0)=src[i].x;
        hs.at<double>(1)=src[i].y;
        hs.at<double>(2)=1;
        nsrc.push_back(Tsrc*hs);
    }
    for(int i=0;i<dst.size();i++)
    {
        cv::Mat hs(3,1,CV_64F);
        hs.at<double>(0)=dst[i].x;
        hs.at<double>(1)=dst[i].y;
        hs.at<double>(2)=1;
        ndst.push_back(Tdst*hs);
    }
    cv::Mat A=cv::Mat::zeros(8,9,CV_64F),h(9,1,CV_64F);
    for(int i=0;i<src.size();i++)
    {
        A.at<double>(i*2,0)=nsrc[i].at<double>(0);
        A.at<double>(i*2,1)=nsrc[i].at<double>(1);
        A.at<double>(i*2,2)=1;
        A.at<double>(i*2,6)=-ndst[i].at<double>(0)*nsrc[i].at<double>(0);
        A.at<double>(i*2,7)=-ndst[i].at<double>(0)*nsrc[i].at<double>(1);
        A.at<double>(i*2,8)=-ndst[i].at<double>(0);

        A.at<double>(i*2+1,3)=nsrc[i].at<double>(0);
        A.at<double>(i*2+1,4)=nsrc[i].at<double>(1);
        A.at<double>(i*2+1,5)=1;
        A.at<double>(i*2+1,6)=-ndst[i].at<double>(1)*nsrc[i].at<double>(0);
        A.at<double>(i*2+1,7)=-ndst[i].at<double>(1)*nsrc[i].at<double>(1);
        A.at<double>(i*2+1,8)=-ndst[i].at<double>(1);
    }
    cv::SVD::solveZ(A,h);
    cv::Mat H(3,3,CV_64F);
    for(int i=0;i<9;i++)
        H.at<double>(i/3,i%3)=h.at<double>(i);
    return Tdst.inv()*H*Tsrc;
}

cv::Mat SingleViewModel::getNormalizeTransformation(const vector<Point2d> &src)
{
    cv::Point2d center(0,0);
    for(int i=0;i<src.size();i++)
        center=center+src[i];
    double sx=0,sy=0;
    for(int i=0;i<src.size();i++)
    {
        sx+=(src[i].x-center.x)*(src[i].x-center.x);
        sy+=(src[i].y-center.y)*(src[i].y-center.y);
    }
    sx=sqrt(sx/src.size());
    sy=sqrt(sy/src.size());
    cv::Mat H=cv::Mat::eye(3,3,CV_64F);
    H.at<double>(0,0)=1.0/sx;
    H.at<double>(1,1)=1.0/sy;
    H.at<double>(0,2)=-center.x/sx;
    H.at<double>(1,2)=-center.y/sy;
    return H;
}
