#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::mousePressEvent(QMouseEvent * e)
{
	if(img_loaded)
	{
		if(e->button() == Qt::LeftButton)
		{
			int x, y;
			if(click_position(e->x(), e->y(), x, y))
			{
				if(is_vanished == no_done)
				{
					//get the line parallel to x, y, z
					vanish_lines[0].push_back(QPoint(x,y));
				}
				else if(is_vanished == x_done)
				{
					vanish_lines[1].push_back(QPoint(x,y));
				}
				else if(is_vanished == y_done)
				{
					vanish_lines[2].push_back(QPoint(x,y));
				}

				else if(!is_origin)
				{
					//assign the origin point
					origin_pt = QPoint(x,y);
					Vertex* origin_vertex = mod->setOrigin(cv::Point2d(x,y));

					if(origin_vertex != NULL)
					{
						is_origin = true;

						QString tmp;
						QString info = "Please choose a point and insert the distance in 3 dimension.\n";
						info += "Origin Point information:\n";
						info += tmp.sprintf("2D Coordinate:%f,%f\n", origin_vertex->Coor2d().x, origin_vertex->Coor2d().y);
						info += tmp.sprintf("3D Coordinate:%f,%f,%f", origin_vertex->Coor3d().x, origin_vertex->Coor3d().y,origin_vertex->Coor3d().z);

						ui->infobox->setText(info);
						ui->Vanish_Point->setText("Confirm");
						is_vanished = x_scale;

						this->setMouseTracking(true);
						ui->centralWidget->setMouseTracking(true);
						ui->ShowImage->setMouseTracking(true);
					}
					else
					{
							QMessageBox::information(this,
								tr("The input origin point is not valid."),
								tr("The input origin point is not valid."));
					}
				}
				else if(is_vanished == x_scale)
				{
					scale_pt = mod->findPointOnDirection(cv::Point2d(x, y), mod->Xv);
					ui->int_scale->setEnabled(true);
					ui->Vanish_Point->setEnabled(true);
				}
				else if(is_vanished == y_scale)
				{
					scale_pt = mod->findPointOnDirection(cv::Point2d(x, y), mod->Yv); 
					ui->int_scale->setEnabled(true);
					ui->Vanish_Point->setEnabled(true);
				}
				else if(is_vanished == z_scale)
				{
					scale_pt = mod->findPointOnDirection(cv::Point2d(x, y), mod->Zv); 
					ui->int_scale->setEnabled(true);
					ui->Vanish_Point->setEnabled(true);
				}

				//flush the image
				draw_image();
			}
		}
	}
}