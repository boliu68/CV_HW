#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::save_config()
{
	QString filename = QFileDialog::getSaveFileName(
		this,
		"Save Config",
		QDir::currentPath());

	if(mod->saveCalibration(filename.toUtf8().constData()))
	{
		QMessageBox::information(this,
			tr("Save Succeed."),
			tr("Save Succeed"));
	}
	else
	{
		QMessageBox::information(this,
			tr("Save Failed."),
			tr("Save Failed"));
	}
}

void MainWindow::load_config()
{
	QString filename = QFileDialog::getOpenFileName(
	this,
	"Load Config",
	QDir::currentPath());

	Vertex *origin, *xver, *yver, *zver;

	if(mod->loadCalibration(filename.toUtf8().constData(), origin, xver, yver, zver, vanish_pt[0],vanish_pt[1], vanish_pt[2]))
	{
		store_vertex.clear();
		store_vertex.push_back(origin);
		store_vertex.push_back(xver);
		store_vertex.push_back(yver);
		store_vertex.push_back(zver);

		QString info = "Selected point information\n";
		QString tmp;
		char coord[3] = {'X', 'Y', 'Z'};
		for (int i = 0; i < 3; i++)
		{
			info += tmp.sprintf("%c:%f,%f,%f\n", coord[i], store_vertex[i+1]->Coor3d().x,  store_vertex[i+1]->Coor3d().y,  store_vertex[i+1]->Coor3d().z);
		}

		ui->infobox->setText(info);

		for (int i =0;i<3;i++)
		{
			if(std::abs(vanish_pt[i].z) < 0.0001)
				vanish_pt[i].z = 1;
		}
		ui->cal_bot->setEnabled(true);
		ui->cal_face->setEnabled(true);
		ui->cal_top->setEnabled(true);
		ui->vrml->setEnabled(true);
		ui->savecfg->setEnabled(true);
		ui->Vanish_Point->setEnabled(false);
		ui->int_scale->setEnabled(false);
		is_vanished = all_done;
		is_origin = true;
		draw_image();
	}
	else
	{
		QMessageBox::information(this,
			tr("Load Failed."),
			tr("Load Failed"));
	}
}


void MainWindow::on_vrml()
{
	QString filename = QFileDialog::getSaveFileName(
		this,
		"Save VRML",
		QDir::currentPath());

	mod->generateVRMLCode(filename.toUtf8().constData());

	QMessageBox::information(this,
			tr("Save Succeed."),
			tr("Save Succeed"));
}