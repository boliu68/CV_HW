#ifndef PIXEL_H
#define PIXEL_H
#include"define.h"
class Pixel
{
private:
	Vec3d normal;
	Vec2i coord;
	double depth;
public:
	Pixel(){}
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
