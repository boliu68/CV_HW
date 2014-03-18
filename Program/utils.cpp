#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>


bool MainWindow::click_position(int x, int y, int& x_, int& y_)
{
	float scale;
	if (workstates == image_only || workstates == image_only_contour)
		{scale = size;}
	if (workstates == pixel_node 
		|| workstates == cost_graph 
		|| workstates == path_tree 
		|| workstates == min_path)
		{scale = 3.0 * size;}
		
	x_ = floor((x - ui->ShowImage->x() - ui->centralWidget->x()) / scale);
	y_ = floor((y - ui->ShowImage->y() - ui->centralWidget->y()) / scale);
	return (x_ >=0 && y_ >=0 && x_ < img->width() && y_ < img->height());
}


void MainWindow::reset_image()
{
	float scale = 1.0;
	if (workstates == image_only_contour)
	{
		//pimg = new QImage(img->copy());
		QImage * img_tmp;
		img_tmp = pimg;
		pimg = new QImage(img->scaled(img->width() * size, img->height() * size, Qt::KeepAspectRatio));
		delete img_tmp;
		scale = 1.0;
	}

	else if(workstates == min_path)
	{
		delete pimg;
		pimg = new QImage(pathtree->scaled(pathtree->width() * size, pathtree->height() * size, Qt::KeepAspectRatio));
		scale = 3.0;
	}
}





void MainWindow::closet_point()
{
	/*vector<QPoint>::iterator final_point = click_point[path_id].end() - 1;
	vector<QPoint>::iterator closet;
	float closet_dist = 1e10;

	vector<QPoint>::iterator iter = click_point[path_id].begin();

	while(iter !=  (click_point[path_id].end() - 2))
	{
		if(((final_point->x() - iter->x()) * (final_point->x() - iter->x()) 
			+ (final_point->y() - iter->y()) * (final_point->y() - iter->y())) < closet_dist)
		{
			closet_dist = (final_point->x() - iter->x()) * (final_point->x() - iter->x()) 
			+ (final_point->y() - iter->y()) * (final_point->y() - iter->y());
			closet = iter;
		}
		iter ++;
	}*/

	vector<QPoint>::iterator closet = click_point[path_id].begin();

	vector<QPoint> path;
	ics->getPath(closet->x(), closet->y(), path);

	ex_path[path_id].insert(ex_path[path_id].end(), path.begin(), path.end());
}


void MainWindow::paint_path(bool contain_mask)
{
	float scale = 1.0;
	if (workstates == image_only_contour){scale = 1.0;}
	else if(workstates == min_path){scale = 3.0;}
	modify_expath(scale);

	//fix the existed path
	pter = new QPainter(pimg);
	
	for (int i = 0; i < scale_expath.size(); ++i)
	{
		if (is_seed)
		{
			if (i == path_id){pter->setPen(QPen(Qt::green, 2 * size));}
			else {pter->setPen(QPen(Qt::red, 2 * size));}
		}
		else
		{
			if (i == chosen_path){pter->setPen(QPen(Qt::yellow, 2 * size));}
			else {pter->setPen(QPen(Qt::red, 2 * size));}
		}

		pter->drawPoints(&scale_expath[i][0], scale_expath[i].size());
	}

	if(contain_mask)
	{
		if (mask_point.size() > 0)
		{
			pter->setPen(Qt::NoPen);
			pter->setBrush(QBrush(Qt::white, Qt::Dense5Pattern));

			vector<QPoint>::iterator iter = mask_point.begin();
			int times = 0;
			while(iter != mask_point.end())
			{
				if(times % int(ceil(5.0 / (scale * size))) == 0)
					pter->drawEllipse(QPoint(iter->x() * scale * size, iter->y() * scale *size), 20, 20);

				times ++;
				iter ++;
			}
		}
	}

	pter->end();
	draw_image();

	//delete pathtree;
	//pathtree = new QImage(ics->drawPathTree());
}


void MainWindow::choose_path(int x, int y)
{
	float threshold = 10;
	for (int i = 0; i < ex_path.size(); ++i)
	{
		vector<QPoint>::iterator iter = ex_path[i].begin();

		while(iter != ex_path[i].end())
		{
			float dist = sqrt(pow(x - iter->x(), 2.0) + pow(y - iter->y(), 2.0));
			if (dist < threshold)
			{
				chosen_path = i;
				return;
			}
			++iter;
		}
	}
}

void MainWindow::add_mask(int x, int y)
{

	mask_point.push_back(QPoint(x, y));
	
	QPainter * mask_pt = new QPainter(mask);

	paint_path();
	draw_image();

	mask_pt->setBrush(QBrush(1, Qt::SolidPattern));

	if (mask_point.size() > 0)
	{
		mask_pt->setPen(Qt::NoPen);
		mask_pt->setBrush(QBrush(1, Qt::SolidPattern));

		vector<QPoint>::iterator iter = mask_point.begin();
		int times = 0;
		while(iter != mask_point.end())
		{
			pter->drawEllipse(QPoint(iter->x() * size, iter->y() *size), 20, 20);
            mask_pt->drawEllipse(QPoint(iter->x() * size, iter->y() *size), 20, 20);
			iter ++;
		}
	}
	mask_pt->end();
    //mask->save("mask.png")
	ics->setMask(*mask);
}


void MainWindow::on_brush()
{
	QImage *tmp = new QImage(*mask);
	delete mask;
	mask = new QImage(*store_mask);
	delete store_mask;
	store_mask = new QImage(*tmp);
	delete tmp;

	ics->setMask(*mask);
	reset_image();
	paint_path();
	draw_image();
}

void MainWindow::change_function()
{
	if(is_modified)
		ics->setCostFunction(ics->ORIGIN);
	else
		ics->setCostFunction(ics->MODIFIED);

	ics->setImage(img);
	is_modified = !is_modified;
	reset_all();

	reset_image();
	paint_path();
	draw_image();
}

void MainWindow::reset_all()
{
	//reset state
	isctl_pressed = false;
	isplus_pressed = false;
	isminus_pressed = false;
	isentr_pressed = false;
	isback_pressed = false;
	path_id = 0;
	chosen_path = -1;
	size = 1;
	is_seed = false;

	ex_path.clear();
    scale_expath.clear();
    click_point.clear();
	mask_point.clear();
}