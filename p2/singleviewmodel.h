#ifndef SINGLEVIEWMODEL_H
#define SINGLEVIEWMODEL_H
#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include<QPoint>
using namespace std;

class SingleViewModel
{
private:
    QImage * img;
public:
    SingleViewModel();
    cv::Point2d getVanish(const vector<pair<cv::Point2d,cv::Point2d> > &lines);
    //input a set of lines whose end points are pair<cv::Point2d,cv::Point2d>
    QImage getTextureMap(const vecotr<cv::Point2d> &quadrangle);
    //input 4 corner points of quadrangle
};

#endif // SINGLEVIEWMODEL_H
