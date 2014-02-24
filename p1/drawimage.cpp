#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
/*
* Draw the image on the label widget.
*/
void MainWindow::draw_image()
{
<<<<<<< HEAD
	//this->resize(img->width(), img->height());
    //ui->ShowImage->resize(img->width(), img->height());
	//ui->centralWidget->resize(img->width(), img->height());
    if(workstates ==image_only||workstates ==image_only_contour)
    {
        ui->ShowImage->resize(img->width(), img->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*img));
    }
    else if(workstates ==cost_graph)
    {
        QImage cg=ics->drawCostGraph();
        ui->ShowImage->resize(cg.width(), cg.height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(cg));
    }
    else if(workstates==path_tree)
    {
        QImage cg=ics->drawPathTree();
        ui->ShowImage->resize(cg.width(), cg.height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(cg));
    }
}
=======
	this->resize(pimg->width(), pimg->height());
	ui->ShowImage->resize(pimg->width(), pimg->height());
	ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
	//ui->centralWidget->resize(img->width(), img->height());
}
>>>>>>> 8281ddbe12dc7237ab07fc602fd8cbdca6b6f23b
