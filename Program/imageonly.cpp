#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
*The two options for image only
* and the image only with contour;
*/

void MainWindow::on_image_only()
{
	workstates = image_only;
	
	//re paint
	//pter->drawImage(0, 0, *img);
	QImage * img_tmp = NULL;
	img_tmp = new QImage(img->scaled(pimg->width(), pimg->height()));
	delete pimg;
	pimg = img_tmp;

	draw_image();
}



void MainWindow::on_image_contour()
{
	workstates = image_only_contour;
	draw_image();
}


