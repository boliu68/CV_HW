#ifndef PIXEL_H
#define PIXEL_H
#include"define.h"
class Pixel
{
private:
    Vec2i coord;
    double depth;
    Vec3d normal;
public:
    Pixel(int x,int y);//x: column,y: row
    Vec2i Coord();
    double Depth();
    void setDepth(double d);
    Vec3d Normal();
    void setNormal(const Vec3d &n);
    int label;
    int tmplabel;
};

#endif // PIXEL_H
