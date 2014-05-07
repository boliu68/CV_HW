#include <stdio.h>
#include "normal_class.h"
#include <io.h>
#include <direct.h> 
#include <algorithm>
#include "svdcmp.h"

double distance(vector<Vec3d>::iterator x, vector<Vec3d>::iterator y);
bool compare_vector(const pair<int, uchar> a, const pair<int, uchar> b);

normal_class::normal_class()
{
}

bool normal_class::read_file(const string &folder)
{
	this->foldername = folder;

	//read light direction
	string light_filename = this->foldername + "\\lightvec.txt";
	
	FILE * fp;
	fp = fopen(light_filename.c_str(), "r");
	if(fp == NULL)
		return false;
	
	double x,y,z;
	while(fscanf(fp, "%lf %lf %lf", &x, &y,&z) != EOF)
	{
		Vec3d xyz(x, y, z);
		this->light_direction.push_back(xyz);
	}

	//scan all the bmp files and save it;
	char current_path[_MAX_PATH];
	getcwd(current_path,_MAX_PATH);  
	if (_fullpath(current_path, foldername.c_str(), _MAX_PATH) == NULL)  
        return false;  

	string bmp_path(current_path);
	bmp_path +=  "\\*.bmp";
	_finddata_t file;
    long lf;
	if((lf = _findfirst(bmp_path.c_str(), &file))==-1l)
		return false;
    else
    {
        do
        {
            //save the bmp image to vector<IplImage*>
			string filepath(current_path);
			filepath += "\\";
			filepath += file.name;
			Mat img;
			img = imread(filepath.c_str(), CV_LOAD_IMAGE_GRAYSCALE);

			imgs.push_back(img);
        } 
		while( _findnext( lf, &file ) == 0 );
    }
    _findclose(lf);

	this->norm_height = this->imgs[0].size[1];
	this->norm_width = this->imgs[0].size[0];

	return true;
}

bool normal_class::uniform_division(int k, int NSAMPLE)
{
    //int NSAMPLE = 500;
	knn = k;
	generateSphereSamples(NSAMPLE, sampled_light_direction);
	
	//this->imgs;
	
	find_nearest();

	interpolate();
	
	//this->interplote_imgs;
	return true;
}

void normal_class::find_nearest()
{

	int i, j, h;
	vector<Vec3d>::iterator sample_bg = sampled_light_direction.begin();

	while(sample_bg != sampled_light_direction.end())
	{

		vector<int> vec_idx;
		vector<Vec3d>::iterator capture_bg = this->light_direction.begin();
		j = 0;

		int close_idx = 0;
		double close_dist = 1000;

		while(capture_bg != light_direction.end())
		{
			
			double dist = distance(sample_bg, capture_bg);

			if (dist < 0.3)
				vec_idx.push_back(j);
			j++;
			capture_bg ++;
		}

		sample_bg ++;

		this->nearest_light_direction.push_back(vec_idx);
	}
}


void normal_class::interpolate()
{

	int i = 0, j = 0;
	vector<Vec3d> sampled_light_tmp = this->sampled_light_direction;
	this->sampled_light_direction.clear();
	vector<Vec3d>::iterator sample_bg = sampled_light_tmp.begin();

	while(sample_bg != sampled_light_tmp.end())
	{
		vector<int> nearest_captured = nearest_light_direction[i];
		
		double L_sum = 0;
		Mat interpolate_mat = Mat::zeros(imgs[0].size[0], imgs[0].size[1], CV_64FC1);//imgs[0].type());

		for(j = 0; j< nearest_captured.size(); j ++)
		{
			double L0Li = sample_bg->val[0] * this->light_direction[nearest_captured[j]].val[0]
			+sample_bg->val[1] * this->light_direction[nearest_captured[j]].val[1]
			+sample_bg->val[2] * this->light_direction[nearest_captured[j]].val[2];
			L_sum += L0Li;

			//add(interpolate_mat, imgs[nearest_captured[j]] * L0Li, interpolate_mat);//imgs[nearest_captured[j]].mul(L0Li);
		}
		for (j = 0; j< nearest_captured.size(); j++)
		{
			double L0Li = sample_bg->val[0] * this->light_direction[nearest_captured[j]].val[0]
			+sample_bg->val[1] * this->light_direction[nearest_captured[j]].val[1]
			+sample_bg->val[2] * this->light_direction[nearest_captured[j]].val[2];
			
			Mat tmp = Mat(imgs[nearest_captured[j]].size(), CV_64FC1);
			imgs[nearest_captured[j]].convertTo(tmp, CV_64FC1);

			add(interpolate_mat, tmp * L0Li / L_sum, interpolate_mat);//imgs[nearest_captured[j]].mul(L0Li);
		}

		if(nearest_captured.size() !=0 )
		{
			this->sampled_light_direction.push_back(*sample_bg);	
			//divide(interpolate_mat, L_sum, interpolate_mat);
			interplote_imgs.push_back(interpolate_mat);
		}
		sample_bg ++;
		i++;
	}
}

bool normal_class::find_denominator(float L, float H)
{
	rank_all();

	update_kr(L, H);

	//show the denominator image
	Mat show_tmp = Mat(interplote_imgs[denominator_idx].size(), CV_8U);
	interplote_imgs[denominator_idx].convertTo(show_tmp, CV_8U);
	imshow("DisplayImage", show_tmp);
	waitKey(20);
	
	return true;
}

void normal_class::update_kr(float L, float H)
{
	//calculat K and R for each image
	//update L, H respectively.

	int num_images = this->ranking.size();
	int Lrank = floor(double(num_images * L));
	int Hrank = floor(double(num_images * H));

	int max_k = 0;
	int max_idx = 0;

	for(int i = 0; i < num_images; i++)
	{
		int width = interplote_imgs[0].size[0];
		int height = interplote_imgs[0].size[1];

		int k = 0;
		double r = 0;

		for(int x = 0; x< width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				if (ranking[i][y * width + x] > Lrank)
				{
					++k;
					r += ranking[i][y * width + x];
				}
			}
		}

		if((r / k) > Hrank)
		{
			Kil.push_back(-1);
			Ril.push_back(-1);
		}
		else{
			Kil.push_back(k);
			Ril.push_back(r / k);

			if(k > max_k)
			{
				max_k = k;
				max_idx = i;
			}

		}
	}

	denominator_idx = max_idx;
}

void normal_class::rank_all()
{
	//initialize the rank mat
	int total_time = 0;
	for(int i = 0; i< interplote_imgs.size(); i++)
	{
		//Mat rank = Mat::zeros(interplote_imgs[0].size[0], interplote_imgs[0].size[1], CV_16U);
		
		int *rank = new int[interplote_imgs[0].size[0] * interplote_imgs[0].size[1]];

		this->ranking.push_back(rank);
		Kil.push_back(0);
		Ril.push_back(0.0f);
		total_time ++;

		//delete rank;
	}

	int width = interplote_imgs[0].size[0];
	int height = interplote_imgs[0].size[1];

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			//for one pixel, achieve the rank
            vector<pair<int, double> > intensity_xy;
			//interplote_imgs[0].at<int>(x, y);
			for(int i = 0; i < total_time; i++)
			{
				double* pts = interplote_imgs[i].ptr<double>(x);
				double mm = pts[y];
				intensity_xy.push_back(pair<int, double>(i, mm));
			}

			//sort the intensity and obtain the rank;
			stable_sort(intensity_xy.begin(), intensity_xy.end(), compare_vector);
			for(int i = 0; i < total_time; i++)
			{
				ranking[intensity_xy[i].first][y * width + x] = i;
			}
			
		}
	}
}

bool normal_class::get_normal()
{
	Mat detnominator_image = this->interplote_imgs[this->denominator_idx];
	Vec3d denominator_light = this->sampled_light_direction[this->denominator_idx];
	
	int k = this->interplote_imgs.size();
	int width = detnominator_image.size[0];
	int height = detnominator_image.size[1];

	for(int y = 0; y< height; y++)
	{
		vector<Pixel> pixel_row;

		for (int x = 0; x < width; x++)
		{
			
			double **abc = new double*[k - 1];
			for(int i = 0; i < k - 1; i++)
				abc[i] = new double[3];

			int img_id = 0;

			double* p2 = detnominator_image.ptr<double>(x);
			double I2 = p2[y];

			for(int i = 0; i < k; i++)
			{
				if(i == this->denominator_idx)
					continue;

				double* p1 = this->interplote_imgs[i].ptr<double>(x);
				double I1 = p1[y];

				Vec3d l1 = this->sampled_light_direction[i];

				abc[img_id][0] = I1 * denominator_light.val[0] - I2 * l1.val[0];
				abc[img_id][1] = I1 * denominator_light.val[1] - I2 * l1.val[1];
				abc[img_id][2] = I1 * denominator_light.val[2] - I2 * l1.val[2];
				img_id ++;
			}
			
			double * w = new double[3];
			double ** v = new double*[3];
			for(int i = 0; i< 3;i++)
				v[i] = new double[3];

			svdcmp(abc, k - 1, 3, w, v);

			Pixel px(x, y);
			Vec3d norm;

			//cout <<v[1][2]<<" ";

			if(v[2][2] >= 0)
				norm = Vec3d(v[0][2], v[1][2], v[2][2]);
			else
				norm = Vec3d(-v[0][2], -v[1][2], -v[2][2]);

			px.setNormal(norm);
			px.setDepth(8);

			pixel_row.push_back(px);

			//delete abc;
			//delete v;
			for(int i = 0; i < k - 1; i++)
				delete abc[i];
			for(int i = 0; i < 3; i++)
				delete v[i];
			delete abc;
			delete v;
			delete w;
		}

		pixels.push_back(pixel_row);
	}
	
	return true;
}

double distance(vector<Vec3d>::iterator x, vector<Vec3d>::iterator  y)
{
	//double dist = x->val[0] * y->val[0] + x->val[1] * y->val[1] + x->val[2] * y->val[2];
		
	 double dist = sqrt((x->val[0] - y->val[0]) * (x->val[0] - y->val[0])
	 + (x->val[1] - y->val[1]) * (x->val[1] - y->val[1])
	 + (x->val[2] - y->val[2]) * (x->val[2] - y->val[2]));

	 return dist;
}

bool compare_vector(const pair<int, uchar> a, const pair<int, uchar> b)
{
	return a.second < b.second;
}
