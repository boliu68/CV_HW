#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
/*
* Draw the image on the label widget.
*/
void MainWindow::draw_image()
{
	if(workstates == image_only||workstates ==image_only_contour)
    {

		/*QImage * img_tmp;
		img_tmp = pimg;
		pimg = new QImage(pimg->scaled(img->width() * size, img->height() * size, Qt::KeepAspectRatio));
		delete img_tmp;*/
        ui->ShowImage->resize(pimg->width(), pimg->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
		ui->centralWidget->resize(pimg->width(), pimg->height());
		this->resize(pimg->width(), pimg->height());
	}
    else if(workstates ==cost_graph)
    {
        QImage cg=ics->drawCostGraph();
        ui->ShowImage->resize(cg.width(), cg.height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(cg));
		ui->centralWidget->resize(cg.width(), cg.height());
		this->resize(cg.width(), cg.height());
    }
    else if(workstates==path_tree)
    {
        ui->ShowImage->resize(pathtree->width(), pathtree->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*pathtree));
		ui->centralWidget->resize(pathtree->width(), pathtree->height());
		this->resize(pathtree->width(), pathtree->height());
    }
	else if(workstates == min_path)
	{
		/*QImage * img_tmp = pimg;
		pimg = new QImage(pimg->scaled(pimg->width() * size, pimg->height() * size, Qt::KeepAspectRatio));
		delete img_tmp;*/
        ui->ShowImage->resize(pimg->width(), pimg->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
		ui->centralWidget->resize(pimg->width(), pimg->height());
		this->resize(pimg->width(), pimg->height());
	}
}

