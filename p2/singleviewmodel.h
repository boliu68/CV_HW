#ifndef SINGLEVIEWMODEL_H
#define SINGLEVIEWMODEL_H
#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include<QPoint>
#include<QImage>
using namespace std;
class SingleViewModel;
class Face;
class Vertex
{
friend class SingleViewModel;
friend class Face;
private:
    cv::Point2d coor2d;
    cv::Point3d coor3d;
    Vertex* bottom;
    int id;
    void setCoor3d(const cv::Point3d &c3);
    void setBottom(Vertex * v);
    Vertex* Bottom();
    void setID(int i);
    Vertex(const cv::Point2d &c2);
    bool isBottom();
    bool sameVertex(const cv::Point2d &p);
    double getDistance(const cv::Point2d &p);
public:
    cv::Point2d Coor2d();//coordinate in Image system
    cv::Point3d Coor3d();//coordinate in 3D
    int ID();//return ID of this vertex
    ~Vertex();
};

class Face
{
friend class SingleViewModel;
private:
    vector<Vertex*> vertexs;
    double area;
    bool ground;
    bool vertical;
    bool paraToGround();
    bool Vertical();
    double Height();
    double height;
    double Area();
    bool inFace(const cv::Point2d &p);
    double triangleArea(const cv::Point2d &p1,const cv::Point2d &p2,const cv::Point2d &p3);
    QImage* texture;
    bool isVerticalLine(Vertex* v1,Vertex* v2);
    double getAngle(int ID);
    int vertexWithMinAngle();
    double disPoint2Line(const cv::Point3d &p, const cv::Vec3d &d, const cv::Point3d &begin);
    Vertex* farestPoint2Line(const cv::Vec3d &d, const cv::Point3d &begin);
    Vertex* farestPoint2Plane(const cv::Vec3d &d, const cv::Point3d &begin);
    double disPoint2Plane(const cv::Point3d &p, const cv::Vec3d &d, const cv::Point3d &begin);
    Face(const vector<Vertex*> &vs);
public:
    Vertex* getVertex(int ID);//return the IDst vertex, clock order
    QImage Texture();//return texture image
    ~Face();
};

class SingleViewModel
{   
public:
    enum VANISH{Xv,Yv,Zv};
private:
    QImage * img;
    cv::Point3d vx,vy,vz;
    cv::Vec3d lxy;//lxy=vx*vy;
    vector<Vertex*> vertexs;
    vector<Vertex*> virtualVers;
    vector<Face*> faces;
    Vertex* origin,*referP;
    cv::Vec3d refLine;
    double refHeight;
    cv::Mat Homography;
    cv::Mat intrinsic;//K
    cv::Mat Rot;//R
    cv::Mat tran;//t, P=K[R|t]
    cv::Point3d camCenter;
    cv::Vec3d getLine(const cv::Point2d &p1,const cv::Point2d &p2);
    cv::Vec3d getLine(const cv::Point2d &p1,const cv::Point3d &p2);
    cv::Vec3d getLine(const cv::Point3d &p1,const cv::Point2d &p2);
    cv::Vec3d getLine(const cv::Point3d &p1,const cv::Point3d &p2);
    cv::Point3d Normalize(const cv::Point2d &p);
    cv::Point3d Denormalize(const cv::Point3d &p);
    cv::Point3d getOneVanish(const vector<pair<cv::Point2d,cv::Point2d> > &lines);
    void initialVertex(Vertex *ver,const cv::Point2d &c2,const cv::Point3d &c3,Vertex *bottom=NULL);
    double getHeightOnRefLine(const cv::Point2d &p);
    cv::Point2d getPointOnRefLine(const cv::Point2d &bottom,const cv::Point2d &top);
    cv::Point2d getPointOnRefPlane(const cv::Point2d &p, Face *groundplane);
    cv::Point3d getPointOnImage(const cv::Point3d &p);
    bool inSameLine(const cv::Point2d &p1,const cv::Point2d &p2,const cv::Point2d &p3);
    cv::Point3d get3DPointOnRefPlane(const cv::Point2d &p);
    //cv::Vec3d selectVanishLine(const cv::Point2d &p1,const cv::Point2d &p2);
    //bool inRegion(const cv::Point2d &p1,const cv::Point2d &p2,const cv::Point3d &v1,const cv::Point3d &v2);
    //check p1p2 is in p1v1,p2v2
    //bool inPlanePara2Ground(const vector<Vertex*> &vers);
    Face* generateFaceFrom3Points(const vector<Vertex*> &vers);
    //require clock order
    void getFaceTexture(Face *face);
    void computeTexture(Face *face,const vector<Vertex*> &vers);
    cv::Point2d getCorrespond(const QPoint &src,const cv::Mat &H);
    QRgb interpolate(const cv::Point2d &p);
    cv::Point3d getProjOnLine(const cv::Point3d &p,const cv::Point3d begin,const cv::Vec3d &d);
    //line:begin with begin in d direction
    cv::Point3d getProjOnPlane(const cv::Point3d &p,const cv::Point3d begin,const cv::Vec3d &n);
    //plane: normal:n, begin on it
    cv::Point2d compute2DCoordinate(const cv::Point3d & p);
    void getCameraInformation();

public:
    SingleViewModel(QImage *image);
    cv::Point3d computeVanish(const vector<pair<cv::Point2d,cv::Point2d> > &lines,VANISH v);
    //input a set of lines whose end points are pair<cv::Point2d,cv::Point2d>, and v is the enum of vanish
    //you should tell this function which vanish point need to be computed by v
    Vertex* setOrigin(const cv::Point2d &p);
    //Set origin point in image,return origin vertex information. If fail, return NULL;
    void setReferencePoints(const cv::Point2d &x,const cv::Point2d &y,const cv::Point2d &z,
                            double xlength,double ylength,double zlength,
                            Vertex* xver,Vertex* yver,Vertex* zver);
    //Set 3 reference points, and tell the length between origin point to them,
    //vertex information are returned in xver,yver,zver
    cv::Point2d findPointOnDirection(const cv::Point2d &p,VANISH v);
    //find the projection of p in line from origin to vanish point v on image space
    cv::Point2d findPointOnDirection(const cv::Point2d &p, const cv::Point2d &bottom);
    //find the projection of p in line from bottom to vanish point v in z direction
    Vertex* findNearestVertex(const cv::Point2d &p);
    //find vertex which has been computed and is nearest to p in image space
    Vertex* compute3DCoordinate(Vertex* bottom,cv::Point2d &top);
    //compute vertex top's 3d coordinate by bottom which has been computed
    Face* findFace(const cv::Point2d &p);
    //find the face which has been generated and contains p, if no face, return null
    void compute3DCoordinate(const cv::Point2d &bottom,const cv::Point2d &top,
                             Vertex* vbottom,Vertex* vtop);
    //compute vertex bottom and top' 3d coordinate, return vertex information in vbottom,vtop
    Face* generateFace(const vector<Vertex*> &vers);
    //input vertexs in clock order, generate a new face. If fail ,return NULL
    ~SingleViewModel();
};

#endif // SINGLEVIEWMODEL_H
