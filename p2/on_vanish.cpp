#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_vanish()
{
	//to point the vanish points
	if(is_vanished == no_done)
	{
		this->ui->Vanish_Point->setText("Y axis");
		this->ui->infobox->setText("Please assign the Y axis now.");
		is_vanished = x_done;
	}
	else if(is_vanished == x_done)
	{
		this->ui->Vanish_Point->setText("Z axis");
		this->ui->infobox->setText("Please assign the Z axis now.");
		is_vanished = y_done;
	}
	else if(is_vanished == y_done)
	{
		//this->ui->Vanish_Point->setText("Z axis");
		this->ui->Vanish_Point->setEnabled(false);
		this->ui->infobox->setText("Please assign the origin point.");
		is_vanished = z_done;
	}
	//Input the scale for 3 axis.
	else if(is_vanished >= x_scale)
	{
		QString input = ui->int_scale->toPlainText();
		bool test = false;
		input.toDouble(&test);
		if(test)
		{
			axis_scale[is_vanished - x_scale] = input.toDouble();	
			ui->int_scale->clear();

			switch(is_vanished)
			{
			case x_scale:
				{
					ui->infobox->setText("Please insert the scale for Y axis.");
					is_vanished = y_scale;
					break;
				}
			case y_scale:
				{
					ui->infobox->setText("Please insert the scale for Z axis.");
					is_vanished = z_scale;
					break;
				}
			case z_scale:
				{
					ui->infobox->setText("Done.");
					break;
				}
			}
		}
	}

	draw_image();
}