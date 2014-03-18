#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::mouseMoveEvent(QMouseEvent * e)
{
	if(img_loaded)
	{
		int x, y;
		if(click_position(e->x(), e->y(), x, y))
		{
			if(is_3d)
			{
				if(!is_bottom)
				{
					d3_select_pt = mod->findPointOnDirection(cv::Point2d(x, y), bottom);
				}
			}
			else
			{
				switch(is_vanished)
				{
				case x_scale:
					{
						proj_pt = mod->findPointOnDirection(cv::Point2d(x, y), mod->Xv);
						break;
					}
				case y_scale:
					{
						int x, y;
						click_position(e->x(), e->y(), x, y);
						proj_pt = mod->findPointOnDirection(cv::Point2d(x, y), mod->Yv);
						break;
					}
				case z_scale:
					{
						int x, y;
						click_position(e->x(), e->y(), x, y);
						proj_pt = mod->findPointOnDirection(cv::Point2d(x, y), mod->Zv);
						break;
					}
				default: break;
				}
			}
			draw_image();
		}
	}
}