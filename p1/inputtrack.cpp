#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <stdexcept>

using namespace std;

void MainWindow::mousePressEvent(QMouseEvent *e)
{
	if (workstates == image_only_contour)
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

					pter = new QPainter(pimg);

					if(is_seed)
					{
						//seed already exist, draw the path;
						//otherwise, only draw the clickpoint.
						vector<QPoint> path;
						ics->getPath(x, y, path);

						//store the path to ex_path
						ex_path[path_id].insert(ex_path[path_id].end(), path.begin(), path.end());
					}
								
					//Draw the point
					pter->setPen(QPen(Qt::red, 3));
					pter->drawPoint(x, y);
					pter->end();
					draw_image();

					if (ex_path.size() == 0)
					{
						vector<QPoint> a_point;
						a_point.push_back(QPoint(x,y));
						ex_path.push_back(a_point);
					}

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
	if (workstates == image_only_contour)
	{
		if (is_seed)
		{
			//track the mouse
			int x, y;
			if (click_position(e->x(), e->y(), x, y))
			{
				delete pimg;
				pimg = new QImage(img->copy());

				pter = new QPainter(pimg);
				vector<QPoint> path;

				ics->getPath(x, y, path);

				pter->setPen(Qt::green);
				pter->drawPoints(&ex_path[path_id][0], ex_path[path_id].size());

				pter->drawPoints(&path[0], path.size());
				pter->end();

				draw_image();
				
			}

		}
	}
}

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


	if (isctl_pressed && isplus_pressed)
	{
		//enlarge the picture
		size = size * 2.0;

		draw_image();
	}

	if (isctl_pressed && isminus_pressed)
	{
		//ensmaller the picture.
		
		size = size / 2.0;

		draw_image();
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

}


bool MainWindow::click_position(int x, int y, int& x_, int& y_)
{
	x_ = floor((x - ui->centralWidget->x()) / size);
	y_ = floor((y - ui->centralWidget->y()) / size);
	return (x_ >=0 && y_ >=0 && x_ < img->width() && y_ < img->height());
}