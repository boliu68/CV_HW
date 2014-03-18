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
					is_origin = true;

					ui->infobox->setText("Please insert the scale for X axis.");
					ui->Vanish_Point->setText("Confirm");
					ui->int_scale->setEnabled(true);
					ui->Vanish_Point->setEnabled(true);
					is_vanished = x_scale;
				}
				draw_image();
			}
		}
	}
}