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
        ui->ShowImage->resize(pimg->width(), pimg->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
		ui->centralWidget->resize(pimg->width() + 50, pimg->height() + 50);
		this->resize(pimg->width() + 50, pimg->height() + 50);
	}
	else if(workstates == pixel_node)
	{
		QImage pn=ics->drawPixelNode();
		delete pimg;
		pimg = new QImage(pn.scaled(pn.width() * size, pn.height() * size));
        ui->ShowImage->resize(pimg->width(), pimg->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
		ui->centralWidget->resize(pimg->width() + 50, pimg->height() + 50);
		this->resize(pimg->width() + 50, pimg->height() + 50);
	}
    else if(workstates ==cost_graph)
    {
        QImage cg=ics->drawCostGraph();
		delete pimg;
		pimg = new QImage(cg.scaled(cg.width() * size, cg.height() * size));
        ui->ShowImage->resize(pimg->width(), pimg->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
		ui->centralWidget->resize(pimg->width() + 50, pimg->height() + 50);
		this->resize(pimg->width() + 50, pimg->height() + 50);
    }
    else if(workstates==path_tree)
    {
		delete pimg;
		pimg = new QImage(pathtree->scaled(pathtree->width() * size, pathtree->height() * size));
        ui->ShowImage->resize(pimg->width(), pimg->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
		ui->centralWidget->resize(pimg->width() + 50, pimg->height() + 50);
		this->resize(pimg->width() + 50, pimg->height() + 50);
    }
	else if(workstates == min_path)
	{
        ui->ShowImage->resize(pimg->width(), pimg->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
		ui->centralWidget->resize(pimg->width() + 50, pimg->height() + 50);
		this->resize(pimg->width() + 50, pimg->height() + 50);
	}
}

