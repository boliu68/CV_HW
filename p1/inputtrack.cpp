#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>

using namespace std;

void MainWindow::mousePressEvent(QMouseEvent *e)
{
	if (!is_seed)
	{
		if(e->button() == Qt::LeftButton && isctl_pressed)
		{
			
			setCursor(Qt::CrossCursor);

			//change the coordinate
			int x, y;
			click_position(e->x(), e->y(), x, y);

			//set the seed
			ics->setSeed(x, y);
			is_seed = true;

			//Draw the seed
			pter->setPen(QPen(Qt::red, 6));
			pter->drawPoint(x, y);
			draw_image();
		}
	}
	else
	{
		int x, y;
		click_position(e->x(), e->y(), x, y);

		vector<QPoint> path;
		ics->getPath(x, y, path);

		vector<QPoint>::iterator iter = path.begin();

		pter->setPen(QPen(Qt::green, 3));
		pter->drawPoints(&path[0], path.size());

		pter->setPen(QPen(Qt::blue, 5));
		pter->drawPoint(x, y);

		draw_image();
	}
}

void MainWindow::keyPressEvent(QKeyEvent * e)
{
	//judge whether control is pressed
	if (e->key() == Qt::Key_Control)
	{
		isctl_pressed = true;
	}
}

void MainWindow::keyReleaseEvent(QKeyEvent * e)
{
	if (e->key() == Qt::Key_Control)
	{
		isctl_pressed = false;
	}
}


void MainWindow::click_position(int x, int y, int& x_, int& y_)
{
	x_ = x - ui->centralWidget->x();
	y_ = y - ui->centralWidget->y();
}