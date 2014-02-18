#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::OpenImage()
{
	QString filename = QFileDialog::getOpenFileName(
   this,
   "Load Images",
   QDir::currentPath(),
   "Images files (*.jpg *.png);");

	
	QImage * img = new QImage;

	if (! (img->load(filename)))
	{
		 QMessageBox::information(this,
                                     tr("Fail to open Image"),
                                     tr("Fail to open Image!"));
	}
	
	this->resize(img->width(), img->height());
	ui->ShowImage->resize(img->width(), img->height());
	ui->ShowImage->setPixmap(QPixmap::fromImage(*img));
}
