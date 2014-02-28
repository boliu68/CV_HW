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

					if(is_snap)
					{
						QPoint tmp = ics->snapSeed(x, y);
						x = tmp.x();
						y = tmp.y();
					}

					if(is_seed)
					{
						//seed already exist, draw the path;
						//otherwise, only draw the clickpoint.
						vector<QPoint> path;
						ics->getPath(x, y, path);

						//store the path to ex_path
						ex_path[path_id].insert(ex_path[path_id].end(), path.begin(), path.end());
						click_point[path_id].push_back(QPoint(x,y));

						//delete pathtree;
						//pathtree = new QImage(ics->drawPathTree());
					}

					//if (ex_path.size() == 0)
					else
					{
						vector<QPoint> a_point;
						a_point.push_back(QPoint(x,y));
						ex_path.push_back(a_point);
						click_point.push_back(a_point);
						//pathtree = new QImage(ics->drawPathTree());
					}
					
					delete pathtree;
					pathtree = new QImage(ics->drawPathTree());

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

			//else
			//{//to choose the contour
			//not press control as well as not is seed
				
			//}
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
				pter->setPen(QPen(Qt::green, 2 * size));

				//paint the existed path
				/*for (int i = 0; i < ex_path.size(); ++i)
				{
					if (i == path_id){pter->setPen(QPen(Qt::green, 2 * size));}
					else{pter->setPen(QPen(Qt::red, 2 * size));}
					pter->drawPoints(&scale_expath[i][0], scale_expath[i].size());
				}*/

				pter->drawPoints(&path[0], path.size());
				delete pter;

				/*if (mask_point.size() > 0)
				{
					pter = new QPainter(pimg);
					pter->setBrush(QBrush(QColor(128, 128, 255, 5), Qt::SolidPattern));
					//pter->setPen(50);
					//pter->drawPoints(&mask_point[0], mask_point.size());
					vector<QPoint>::iterator iter = mask_point.begin();
					int times = 0;
					while(iter != mask_point.end())
					{
						if(times % 5 == 0)
							pter->drawEllipse(QPoint(iter->x(), iter->y()), 20, 20);

						times ++;
						iter ++;
					}
					pter->end();
				}*/
				paint_path();
				//draw_image();
			}

		}
		else
		{
			int x, y;
			if (click_position(e->x(), e->y(), x, y));
			choose_path(x, y);
			paint_path();
			draw_image();

			if(e->buttons() & Qt::LeftButton)
			{
				int x, y;
				click_position(e->x(), e->y(), x, y);
				add_mask(x, y);
			}
		}
	}
}

