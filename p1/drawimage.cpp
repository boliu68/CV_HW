#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
* Draw the image on the label widget.
*/
void MainWindow::draw_image()
{
	this->resize(pimg->width(), pimg->height());
	ui->ShowImage->resize(pimg->width(), pimg->height());
	ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
	//ui->centralWidget->resize(img->width(), img->height());
}