#ifndef NORMAL_CLASS_H
#define NORMAL_CLASS_H

#include"define.h"
#include"pixel.h"
#include "sampling.h"

//used for storing information of initial normal estimation
class normal_class
{
	vector<Mat> imgs;
	vector<Mat> interplote_imgs;
	vector<Vec3d> sampled_light_direction;
	vector<Vec3d> light_direction;
	vector<vector<int>> nearest_light_direction;// the nearest L_i for each L_0
	//vector<int> nearest_light_direction;
	vector<int *> ranking;// for selecting denomiator image
	vector<int> Kil;
	vector<double> Ril;

	string foldername;
	int knn;//k nearest
	//double karea;
	void find_nearest(); //find the nearest light direction for each sampled vertex
	void interpolate();
	void rank_all();
	void update_kr(float L, float H);
	int denominator_idx;

public:
	normal_class();
	int norm_width;
	int norm_height;
	bool read_file(string folder); // read the image and light
	bool uniform_division(int k); //sampling the light direction sphere and assign the nearest vertex
	bool find_denominator(float L, float H);
	bool get_normal();
	vector<vector<Pixel>> pixels;
};

#endif
