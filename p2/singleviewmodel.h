/*#ifndef SINGLEVIEWMODEL_H
#define SINGLEVIEWMODEL_H
#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include<QPoint>
#include<QImage>
using namespace std;

class Vertex
{
public:
    enum LOC{TOP,BOTTOM};
private:
    cv::Point2d coor2d;
    cv::Point3d coor3d;
    LOC location;
    Vertex* neighbor;
    int id;
public:
    cv::Point2d Coor2d();
    cv::Point3d Coor3d();
    Vertex(const cv::Point2d &c2);
    bool sameVertex(const cv::Point2d &p);
    double getDistance(const cv::Point2d &p);
    LOC Location();
    void setCoor3d(const cv::Point3d &c3);
    void setLocation(LOC l);
    void setNeighbor(Vertex * v);
    Vertex* Neighbor();
    void setID(int i);
    int ID();
};

class Face
{
private:
    vector<Vertex*> vertexs;
    double area;
    bool ground;
    double height;
    double triangleArea(const cv::Point2d &p1,const cv::Point2d &p2,const cv::Point2d &p3);
public:
    Face(const vector<Vertex*> &vs);
    double Area();
    bool inFace(const cv::Point2d &p);
    Vertex* getVertex(int ID);
    bool paraToGround();
    double Height();
};

class SingleViewModel
{   
public:
    enum VANISH{Xv,Yv,Zv};
private:
    QImage * img;
    cv::Point2d vx,vy,vz;
    cv::Vec3d lxy;//lxy=vx*vy;
    vector<Vertex*> vertexs;
    vector<Face*> faces;
    vector<Face*> groundplanes;
    Vertex* origin,reference;
    cv::Vec3d reLine;
    double refHeight;
    cv::Mat Homography;
    cv::Vec3d getLine(const cv::Point2d &p1,const cv::Point2d &p2);
    cv::Point3d Normalize(const cv::Point2d &p);
    cv::Point2d Denormalize(const cv::Point3d &p);
    cv::Point2d getOneVanish(const vector<pair<cv::Point2d,cv::Point2d> > &lines);
    void initialVertex(Vertex *ver,const cv::Point2d &c2,const cv::Point &c3,Vertex::LOC loc);
    Face* findFace(const cv::Point2d &p);
public:
    SingleViewModel(QImage *image);
    cv::Point2d computeVanish(const vector<pair<cv::Point2d,cv::Point2d> > &lines,VANISH v);
    //input a set of lines whose end points are pair<cv::Point2d,cv::Point2d>
    QImage getTextureMap(const vector<cv::Point2d> &quadrangle);
    //input 4 corner points of quadrangle
    void setOrigin(const cv::Point2d &p);
    void setReferencePoints(const cv::Point2d &x,const cv::Point2d &y,const cv::Point2d &z,
                            double xlength,double ylength,double zlength,
                            Vertex* xver,Vertex* yver,Vertex* zver);
    cv::Point2d findPointOnDirection(const cv::Point2d &p,VANISH v);
    Vertex* findNearestVertex(const cv::Point2d &p);
    Vertex* compute3DCoordinate(Vertex* bottom);
    void compute3DCoordinate(const cv::Point2d &bottom,const cv::Point2d &top,
                             Vertex* vbottom,Vertex* vtop);
};

#endif // SINGLEVIEWMODEL_H
*/