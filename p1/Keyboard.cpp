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
	if(e->key() == Qt::Key_Backspace)
	{
		isback_pressed = true;
	}


	if (isctl_pressed && isplus_pressed)
	{
		//enlarge the picture
		float scale = 1.0;
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
		float scale = 1.0;
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
			//this->setMouseTracking(false);
			//ui->centralWidget->setMouseTracking(false);
			//ui->ShowImage->setMouseTracking(false);
			setCursor(Qt::ArrowCursor);

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
			//this->setMouseTracking(false);
			//ui->centralWidget->setMouseTracking(false);
			//ui->ShowImage->setMouseTracking(false);
			setCursor(Qt::ArrowCursor);

			reset_image();
			closet_point();

			paint_path();

			is_seed = false;
			path_id ++;
		}
	}

	if(isback_pressed)
	{
		//delete the stored existed path with respect to the chosen one.
		if (!is_seed)
		{
			if (chosen_path != -1)
			{
				vector<vector<QPoint>>::iterator iter = ex_path.begin() + chosen_path;
				ex_path.erase(iter);
				iter = click_point.begin() + chosen_path;
				click_point.erase(iter);

				path_id = ex_path.size();
				chosen_path = -1;

				if (workstates == image_only_contour)modify_expath(1.0);
				else if(workstates == min_path)modify_expath(3.0);
				reset_image();
				paint_path();
				draw_image();
			}
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
	if(e->key() == Qt::Key_Backspace)
	{
		isback_pressed = false;
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