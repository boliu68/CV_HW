#include "pixel.h"

Pixel::Pixel(int x, int y)
{
    coord[0]=x;
    coord[1]=y;
}

Vec2i Pixel::Coord()
{
    return coord;
}

double Pixel::Depth()
{
    return depth;
}

Vec3d Pixel::Normal()
{
    return normal;
}

void Pixel::setDepth(double d)
{
    depth=d;
}

void Pixel::setNormal(const Vec3d &n)
{
    normal=n;
}
