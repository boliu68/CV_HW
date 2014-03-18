#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_vanish()
{
	//to point the vanish points
	if(is_vanished == no_done)
	{
		QString vp_str = "Y axis";
		QString info_str = "Please assign the Y axis now.";
		change_vanish(vp_str, info_str, is_vanished);
	}
	else if(is_vanished == x_done)
	{
		QString vp_str = "Z axis";
		QString info_str = "Please assign the Y axis now.";
		change_vanish(vp_str, info_str, is_vanished);
	}
	else if(is_vanished == y_done)
	{
		//this->ui->Vanish_Point->setText("Z axis");
		this->ui->Vanish_Point->setEnabled(false);
		QString vp_str = "Origin";
		QString info_str = "Please assign the origin point.";
		change_vanish(vp_str, info_str, is_vanished);
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


void MainWindow::change_vanish(QString vp_str, QString info_str, int xyz)
{
	this->ui->Vanish_Point->setText(vp_str);
	this->ui->infobox->setText(info_str);

	std::vector<QPoint>::iterator iter;
	std::vector<std::pair<cv::Point2d,cv::Point2d>> lines;
	for(iter  = vanish_lines[xyz].begin(); iter < vanish_lines[xyz].end() && (iter + 1) < vanish_lines[xyz].end(); iter += 2)
	{
		std::pair<cv::Point2d,cv::Point2d> one_line;
		one_line.first = cv::Point2d(iter->x(), iter->y());
		one_line.second = cv::Point2d((iter+1)->x(), (iter+1)->y());
		lines.push_back(one_line);
	}

	switch(xyz)
	{
	case no_done:
		vanish_pt[0] = mod->computeVanish(lines,mod->Xv);
		is_vanished = x_done;
		break;
	case x_done:
		vanish_pt[1] = mod->computeVanish(lines,mod->Yv);
		is_vanished = y_done;
		break;
	case y_done:
		vanish_pt[2] = mod->computeVanish(lines,mod->Zv);
		is_vanished = z_done;
		break;
	}
}