#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::OpenImage()
{
	QString filename = QFileDialog::getOpenFileName(
   this,
   "Load Images",
   QDir::currentPath(),
   "Images files (*.jpg *.png)");

	
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

    mask = new QImage(img->width(), img->height(), img->format());
    mask->fill(0);

	//Show the image
	draw_image();

	//initialize the IS class
	ics = new Iscissor(img);
	pathtree = new QImage(ics->drawPathTree());
}
