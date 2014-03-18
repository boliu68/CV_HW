#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::onLoadImage()
{
	QString filename = QFileDialog::getOpenFileName(
   this,
   "Load Images",
   QDir::currentPath());
	
	img = new QImage;
	pimg = new QImage;
	img_loaded = true;

	if (! (pimg->load(filename)))
	{
		 QMessageBox::information(this,
                                     tr("Fail to open Image"),
                                     tr("Fail to open Image!"));
		 return;
	}
	
	img->load(filename);
	img_loaded = true;
	draw_image();

	//QMessageBox::information(this,
                                     //tr("Please insert the line segment for x, y and z axis."),
                                     //tr("Please insert the line segment for x, y and z axis!"));
	
	this->ui->infobox->setText("Please assign the X axis now.");
}