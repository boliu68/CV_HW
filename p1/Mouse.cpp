#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <stdexcept>
#include <time.h>

using namespace std;

void MainWindow::mousePressEvent(QMouseEvent *e)
{
	if (workstates == image_only_contour || workstates == min_path)
	{//work in image_only_contour mode
		//will show the contour
		if(e->button() == Qt::LeftButton)
		{//the shortcut

			if (isctl_pressed || is_seed)
			{
				setCursor(Qt::CrossCursor);

				//change the coordinate
				int x, y;
				if (click_position(e->x(), e->y(), x, y))
				{

					//pter = new QPainter(pimg);

					if(is_seed)
					{
						//seed already exist, draw the path;
						//otherwise, only draw the clickpoint.
						vector<QPoint> path;
						ics->getPath(x, y, path);

						//store the path to ex_path
						ex_path[path_id].insert(ex_path[path_id].end(), path.begin(), path.end());
						click_point[path_id].push_back(QPoint(x,y));

						delete pathtree;
						pathtree = new QImage(ics->drawPathTree());
					}

					//if (ex_path.size() == 0)
					else
					{
						vector<QPoint> a_point;
						a_point.push_back(QPoint(x,y));
						ex_path.push_back(a_point);
						click_point.push_back(a_point);
						pathtree = new QImage(ics->drawPathTree());
					}
					
					if(workstates == min_path){modify_expath(3.0);}
					else if(workstates == image_only_contour){modify_expath(1.0);}

					//begin to tracking the mouse
					this->setMouseTracking(true);
					ui->centralWidget->setMouseTracking(true);
					ui->ShowImage->setMouseTracking(true);

					//update the seed
					ics->setSeed(x, y);
					is_seed = true;

				}
			}
		}
	}
}


void MainWindow::mouseMoveEvent(QMouseEvent * e)
{
	if (workstates == image_only_contour || workstates == min_path)
	{
		if (is_seed)
		{
			//track the mouse
			int x, y;
			if (click_position(e->x(), e->y(), x, y))
			{

				float scale = 1.0;

				if (workstates == image_only_contour){scale = 1.0;}
				else if(workstates = min_path){scale = 3.0;}

				vector<QPoint> path;
				ics->getPath(x, y, path);
				
				reset_image();

				//modify the point position with respect to scale
				vector<QPoint>::iterator iter = path.begin();
				while(iter != path.end())
				{
					*iter = QPoint(iter->x() * scale * size, iter->y() * scale * size); 
					iter ++;
				}

				pter = new QPainter(pimg);

				//paint the existed path
				for (int i = 0; i < ex_path.size(); ++i)
				{
					if (i == path_id){pter->setPen(QPen(Qt::green, 2 * size));}
					else{pter->setPen(QPen(Qt::red, 2 * size));}
					pter->drawPoints(&scale_expath[i][0], scale_expath[i].size());
				}

				pter->drawPoints(&path[0], path.size());
				pter->end();
				draw_image();
			}

		}
	}
}


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
		
	x_ = floor((x - ui->centralWidget->x()) / scale);
	y_ = floor((y - ui->centralWidget->y()) / scale);
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

