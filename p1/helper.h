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

#endif // HELPER_H
