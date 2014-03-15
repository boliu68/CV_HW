#ifndef SINGLEVIEWMODEL_H
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
public:
    cv::Point2d Coor2d();
    cv::Point3d Coor3d();
    Vertex(const cv::Point2d &c2);
    bool sameVertex(const cv::Point2d &p);
    LOC Location();
    void setCoor3d(const cv::Point3d &c3);
    void setLocation(LOC l);
    void setNeighbor(Vertex * v);
    Vertex* Neighbor();
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
private:
    QImage * img;
    cv::Point2d vx,vy,vz;
    cv::Vec3d lxy;//lxy=vx*vy;
    vector<Vertex*> vertexs;
    vector<Face*> faces;
    vector<Face*> groundplanes;
    Vertex* origin,reference;
    double refHeight;
    cv::Mat Homography;
    cv::Point3d Normalize(const cv::Point2d &p);
    cv::Point2d Denormalize(const cv::Point3d &p);
    cv::Point2d getOneVanish(const vector<pair<cv::Point2d,cv::Point2d> > &lines);
public:
    SingleViewModel(QImage *image);
    cv::Point2d getVanishs(const vector<pair<cv::Point2d,cv::Point2d> > &xlines,
                           const vector<pair<cv::Point2d,cv::Point2d> > &ylines,
                           const vector<pair<cv::Point2d,cv::Point2d> > &zlines);
    //input a set of lines whose end points are pair<cv::Point2d,cv::Point2d>
    QImage getTextureMap(const vecotr<cv::Point2d> &quadrangle);
    //input 4 corner points of quadrangle
};

#endif // SINGLEVIEWMODEL_H
