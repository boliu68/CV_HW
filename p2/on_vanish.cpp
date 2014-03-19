#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_vanish()
{
	//to point the vanish points
	QString info_str = "X Vanish point:\n";

	if(is_vanished == no_done)
	{
		QString vp_str = "Y axis";
		change_vanish(vp_str, info_str, is_vanished);
		
	}
	else if(is_vanished == x_done)
	{
		QString vp_str = "Z axis";
		change_vanish(vp_str, info_str, is_vanished);
	}
	else if(is_vanished == y_done)
	{
		//this->ui->Vanish_Point->setText("Z axis");
		this->ui->Vanish_Point->setEnabled(false);
		QString vp_str = "Origin";
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
			ref_length[is_vanished - x_scale] = input.toDouble();
			ref_pt[is_vanished - x_scale] = scale_pt;
			scale_pt.x = -1;
			scale_pt.y = -1;
			ui->int_scale->clear();

			ui->int_scale->setEnabled(false);
			ui->Vanish_Point->setEnabled(false);

			switch(is_vanished)
			{
			case x_scale:
				{
					ui->infobox->setText("Please insert the scale for Y reference point.");
					is_vanished = y_scale;
					break;
				}
			case y_scale:
				{
					ui->infobox->setText("Please insert the distance for Z reference point.");
					is_vanished = z_scale;
					break;
				}
			case z_scale:
				{
					ui->infobox->setText("Done.");
					mod->setReferencePoints(ref_pt[0],ref_pt[1],ref_pt[2],
                            ref_length[0], ref_length[1], ref_length[2],
                            ref_vpt[0], ref_vpt[1], ref_vpt[2]);

					//Output the refvpt information
					QString info = "Selected point information\n";
					QString tmp;
					char coord[3] = {'X', 'Y', 'Z'};
					for (int i = 0; i < 3; i++)
					{
						info += tmp.sprintf("%c:%f,%f,%f\n", coord[i], ref_vpt[i]->Coor3d().x,  ref_vpt[i]->Coor3d().y,  ref_vpt[i]->Coor3d().z);
						store_vertex.push_back(ref_vpt[i]);
					}
					ui->infobox->setText(info);
					is_vanished = all_done;

					ui->D3->setEnabled(true);
					ui->texture->setEnabled(true);
					ui->vrml->setEnabled(true);

					break;
				}
			}
		}
	}

	draw_image();
}


void MainWindow::change_vanish(QString vp_str, QString info_str, int xyz)
{
	std::vector<QPoint>::iterator iter;
    std::vector<std::pair<cv::Point2d,cv::Point2d> > lines;
	for(iter  = vanish_lines[xyz].begin(); iter < vanish_lines[xyz].end() && (iter + 1) < vanish_lines[xyz].end(); iter += 2)
	{
		std::pair<cv::Point2d,cv::Point2d> one_line;
		one_line.first = cv::Point2d(iter->x(), iter->y());
		one_line.second = cv::Point2d((iter+1)->x(), (iter+1)->y());
		lines.push_back(one_line);
	}
	QString tmp;
	switch(xyz)
	{
	case no_done:
		vanish_pt[0] = mod->computeVanish(lines,mod->Xv);
		info_str += tmp.sprintf("X:(%f,%f,%f)\n", vanish_pt[0].x, vanish_pt[0].y, vanish_pt[0].z);
		if(std::abs(vanish_pt[0].z) < 0.1)
			vanish_pt[0].z = 1;
		is_vanished = x_done;
		break;
	case x_done:
		vanish_pt[1] = mod->computeVanish(lines,mod->Yv);
		info_str += tmp.sprintf("X:(%f,%f,%f)\n", vanish_pt[0].x, vanish_pt[0].y, vanish_pt[0].z);
		info_str += tmp.sprintf("Y:(%f,%f,%f)\n", vanish_pt[1].x, vanish_pt[1].y, vanish_pt[1].z);
		if(std::abs(vanish_pt[1].z) < 0.1)
			vanish_pt[1].z = 1;
		is_vanished = y_done;
		break;
	case y_done:
		vanish_pt[2] = mod->computeVanish(lines,mod->Zv);
		is_vanished = z_done;
		info_str += tmp.sprintf("X:(%f,%f,%f)\n", vanish_pt[0].x, vanish_pt[0].y, vanish_pt[0].z);
		info_str += tmp.sprintf("Y:(%f,%f,%f)\n", vanish_pt[1].x, vanish_pt[1].y, vanish_pt[1].z);
		info_str += tmp.sprintf("Z:(%f,%f,%f)\n", vanish_pt[2].x, vanish_pt[2].y, vanish_pt[2].z);
		break;
	}

	this->ui->Vanish_Point->setText(vp_str);
	this->ui->infobox->setText(info_str);
}
