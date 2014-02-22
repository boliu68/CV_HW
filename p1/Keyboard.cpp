#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <stdexcept>
#include <time.h>

using namespace std;

void MainWindow::keyPressEvent(QKeyEvent * e)
{
	//judge whether control is pressed
	if (e->key() == Qt::Key_Control)
	{
		isctl_pressed = true;
	}
	if (e->key() == Qt::Key_Equal || e->key() == Qt::Key_Plus)
	{
		isplus_pressed = true;
	}
	if (e->key() == Qt::Key_hyphen || e->key() == Qt::Key_Minus)
	{
		isminus_pressed = true;
	}
	if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
	{
		isentr_pressed= true;
	}



	if (isctl_pressed && isplus_pressed)
	{
		//enlarge the picture
		float scale;
		if (workstates == image_only_contour){scale = 1.0;}
		else{scale == 3.0;}
		size = size * 2.0;

		modify_expath(scale);
		reset_image();
		paint_path();
		draw_image();
	}

	if (isctl_pressed && isminus_pressed)
	{
		//ensmaller the picture.
		float scale = 0.0;
		if (workstates == image_only_contour){scale = 1.0;}
		else{scale == 3.0;}
		size = size / 2.0;

		modify_expath(scale);
		reset_image();
		paint_path();
		draw_image();
	}

	if(isentr_pressed && !isctl_pressed)
	{
		if (is_seed)
		{
			//finish current contour
			this->setMouseTracking(false);
			ui->centralWidget->setMouseTracking(false);
			ui->ShowImage->setMouseTracking(false);

			reset_image();

			paint_path();

			is_seed = false;
			path_id ++;
		}
	}

	if(isentr_pressed && isctl_pressed)
	{
		if(is_seed)
		{
			//finish current contour
			this->setMouseTracking(false);
			ui->centralWidget->setMouseTracking(false);
			ui->ShowImage->setMouseTracking(false);

			reset_image();
			closet_point();

			paint_path();

			is_seed = false;
			path_id ++;
		}
	}
}

void MainWindow::keyReleaseEvent(QKeyEvent * e)
{
	if (e->key() == Qt::Key_Control)
	{
		isctl_pressed = false;
	}
	if (e->key() == Qt::Key_Plus || e->key() == Qt::Key_Equal)
	{
		isplus_pressed = false;
	}
	if (e->key() == Qt::Key_hyphen || e->key() == Qt::Key_Minus)
	{
		isminus_pressed = false;
	}
	if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
	{
		isentr_pressed= false;
	}

}

void MainWindow::modify_expath(float scale)
{
	scale_expath = ex_path;
	for (int i = 0; i < scale_expath.size(); ++i)
	{
		vector<QPoint>::iterator iter = scale_expath[i].begin();
		while(iter != scale_expath[i].end())
		{
			*iter = QPoint(iter->x() * scale * size, iter->y() * scale * size);
			iter ++;
		}
	}
}


void MainWindow::closet_point()
{
	vector<QPoint>::iterator final_point = click_point[path_id].end() - 1;
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
	}

	vector<QPoint> path;
	ics->getPath(closet->x(), closet->y(), path);

	ex_path[path_id].insert(ex_path[path_id].end(), path.begin(), path.end());
}


void MainWindow::paint_path()
{
	float scale = 1.0;
	if (workstates == image_only_contour){scale = 1.0;}
	else if(workstates == min_path){scale = 3.0;}
	modify_expath(scale);

	//fix the existed path
	pter = new QPainter(pimg);
	
	for (int i = 0; i < scale_expath.size(); ++i)
	{
		if (i == path_id){pter->setPen(QPen(Qt::green, 2 * size));}
		else {pter->setPen(QPen(Qt::red, 2 * size));}

		pter->drawPoints(&scale_expath[i][0], scale_expath[i].size());
	}
	pter->end();
	draw_image();

	delete pathtree;
	pathtree = new QImage(ics->drawPathTree());
}