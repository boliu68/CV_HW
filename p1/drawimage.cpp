#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
/*
* Draw the image on the label widget.
*/
void MainWindow::draw_image()
{
	int corner_x = ui->centralWidget->x() + ui->ShowImage->x();
	int corner_y = ui->centralWidget->y() + ui->ShowImage->y();

	if(workstates == image_only||workstates ==image_only_contour)
    {
        ui->ShowImage->resize(pimg->width(), pimg->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
		ui->centralWidget->resize(pimg->width(), pimg->height());
		this->resize(pimg->width() + corner_x, pimg->height() + corner_y);
	}
	else if(workstates == pixel_node)
	{
		QImage pn=ics->drawPixelNode();
		delete pimg;
		pimg = new QImage(pn.scaled(pn.width() * size, pn.height() * size));
        ui->ShowImage->resize(pimg->width(), pimg->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
		ui->centralWidget->resize(pimg->width(), pimg->height());
		this->resize(pimg->width() + corner_x, pimg->height() + corner_y);
	}
    else if(workstates ==cost_graph)
    {
        QImage cg=ics->drawCostGraph();
		delete pimg;
		pimg = new QImage(cg.scaled(cg.width() * size, cg.height() * size));
        ui->ShowImage->resize(pimg->width(), pimg->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
		ui->centralWidget->resize(pimg->width(), pimg->height());
		this->resize(pimg->width() + corner_x, pimg->height() + corner_y);
    }
    else if(workstates==path_tree)
    {
		delete pimg;
		pimg = new QImage(pathtree->scaled(pathtree->width() * size, pathtree->height() * size));
        ui->ShowImage->resize(pimg->width(), pimg->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
		ui->centralWidget->resize(pimg->width(), pimg->height());
		this->resize(pimg->width() + corner_x, pimg->height() + corner_y);
    }
	else if(workstates == min_path)
	{
        ui->ShowImage->resize(pimg->width(), pimg->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
		ui->centralWidget->resize(pimg->width(), pimg->height());
		this->resize(pimg->width() + corner_x, pimg->height() + corner_y);
	}
}

