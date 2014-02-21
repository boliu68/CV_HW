#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::OpenImage()
{
	QString filename = QFileDialog::getOpenFileName(
   this,
   "Load Images",
   QDir::currentPath(),
   "Images files (*.jpg *.png);");

	
	img = new QImage;

	if (! (img->load(filename)))
	{
		 QMessageBox::information(this,
                                     tr("Fail to open Image"),
                                     tr("Fail to open Image!"));
	}
	
	//initialize the painter
	pter = new QPainter(img);

	//Show the image
	draw_image();

	//initialize the IS class
	ics = new Iscissor(img);

}
