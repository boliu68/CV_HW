#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>

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
				click_position(e->x(), e->y(), x, y);
				pter = new QPainter(pimg);

				if(is_seed)
				{
					//seed already exist, draw the path;
					//otherwise, only draw the clickpoint.
					vector<QPoint> path;
					ics->getPath(x, y, path);

					pter->setPen(QPen(Qt::green, 1));
					pter->drawPoints(&path[0], path.size());

					pter->setPen(QPen(Qt::blue, 3));
					pter->drawPoint(x, y);
				}
								
				//Draw the point
				pter->setPen(QPen(Qt::red, 3));
				pter->drawPoint(x, y);
				pter->end();
				draw_image();

				is_seed = true;
				//update the seed
				ics->setSeed(x, y);
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
		QImage * img_tmp = NULL;
		img_tmp = new QImage(img->scaled(pimg->width() * 1.5, pimg->height() * 1.5, Qt::KeepAspectRatio));
		delete pimg;
		pimg = img_tmp;
		draw_image();
	}

	if (isctl_pressed && isminus_pressed)
	{
		//ensmaller the picture.
		QImage * img_tmp = NULL;
		img_tmp = new QImage(img->scaled(pimg->width() / 1.5, pimg->height() / 1.5, Qt::KeepAspectRatio));
		delete pimg;
		pimg = img_tmp;
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


void MainWindow::click_position(int x, int y, int& x_, int& y_)
{
	x_ = x - ui->centralWidget->x();
	y_ = y - ui->centralWidget->y();
}