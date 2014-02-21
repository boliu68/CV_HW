#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
* Draw the image on the label widget.
*/
void MainWindow::draw_image()
{
	//this->resize(img->width(), img->height());
	ui->ShowImage->resize(img->width(), img->height());
	//ui->centralWidget->resize(img->width(), img->height());
	ui->ShowImage->setPixmap(QPixmap::fromImage(*img));
}