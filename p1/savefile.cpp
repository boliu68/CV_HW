#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <QPolygon>
#include <QRegion>

void MainWindow::save_contour()
{
	float size_tmp = size;
	int workstates_tmp = workstates;
	size = 1.0;
	workstates = image_only_contour;

	reset_image();
	paint_path(false);

	//save files with open dialoug
	QString filename = QFileDialog::getSaveFileName(this,
		tr("Save Image"),
		"",
		tr("*.bmp;; *.png;; *.jpg;; *.tif;; *.GIF")); //Ñ¡ÔñÂ·¾¶
	if(filename.isEmpty())
	{
		 QMessageBox::information(this,
                                     tr("Fail to open Image"),
                                     tr("Fail to open Image!"));
		 return;
	}
	else
	{
		if(! ( pimg->save(filename) ) ) //±£´æÍ¼Ïñ
		{
			QMessageBox::information(this,
				tr("Failed to save the image"),
				tr("Failed to save the image!"));
			return;
		}
	}

	size = size_tmp;
	workstates = workstates_tmp;
	reset_image();
	paint_path(is_mask);
	draw_image();
}

void MainWindow::save_mask()
{
	QImage mask(img->width(), img->height(), img->format());
	mask.fill(Qt::black);
	QPainter mask_painter(&mask);
	mask_painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
	//mask_painter.setClipRegion(qrg);
	mask_painter.drawPolygon(&ex_path[0][0], ex_path[0].size());

	//save files with open dialoug
	QString filename = QFileDialog::getSaveFileName(this,
		tr("Save Image"),
		"",
		tr("*.bmp;; *.png;; *.jpg;; *.tif;; *.GIF")); //Ñ¡ÔñÂ·¾¶
	if(filename.isEmpty())
	{
		 QMessageBox::information(this,
                                     tr("Fail to open Image"),
                                     tr("Fail to open Image!"));
		 return;
	}
	else
	{
		if(! ( mask.save(filename) ) ) //±£´æÍ¼Ïñ
		{
			QMessageBox::information(this,
				tr("Failed to save the image"),
				tr("Failed to save the image!"));
			return;
		}
	}
}