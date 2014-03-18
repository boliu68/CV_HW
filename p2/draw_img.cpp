#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::draw_image()
{
	draw_pimg();

	int corner_x = ui->centralWidget->x() + ui->ShowImage->x();
	int corner_y = ui->centralWidget->y() + ui->ShowImage->y();
	
	ui->infobox->setFont(QFont("Courier", 20 * std::min(size, 1.0), QFont::Bold, true));
	ui->infobox->resize(500 * std::min(size, 1.0), 400 * std::min(size, 1.0));

    ui->ShowImage->resize(pimg->width(), pimg->height());
	ui->Vanish_Point->move(pimg->width() + 20, 20);
	ui->int_scale->move(pimg->width() + 20 + ui->int_scale->width(), 20);
	ui->infobox->move(pimg->width() + 20, pimg->height() - ui->infobox->height());
	ui->line->move(pimg->width() + 10, 0);
	ui->centralWidget->resize(pimg->width() + corner_x + ui->infobox->width() + 30, pimg->height() + corner_y + 30);
	this->resize(pimg->width() + corner_x + ui->infobox->width() + 30, pimg->height() + corner_y + 30);

	ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
}


void MainWindow::draw_pimg()
{
	QImage * tmp_img = pimg;
	pimg = new QImage(*img);
	delete tmp_img;

	draw_text();

	QPainter pter(pimg);
	pter.setFont(QFont("Courier", 8, QFont::Bold, true));

	switch(is_vanished)
	{
	case y_done:
		{
			pter.setPen(QPen(Qt::white, 4 * size));
			std::vector<QPoint>::iterator iter;
			for(iter  = vanish_lines[2].begin(); iter < vanish_lines[2].end() && (iter + 1) < vanish_lines[2].end(); iter += 2)
			{
				pter.drawLine(*iter, *(iter + 1));
			}
		}
	case x_done:
		{
			pter.setPen(QPen(Qt::gray, 4 * size));
			std::vector<QPoint>::iterator iter;
			for(iter  = vanish_lines[1].begin(); iter < vanish_lines[1].end() && (iter + 1) < vanish_lines[1].end(); iter += 2)
			{
				pter.drawLine(*iter, *(iter + 1));
			}
		}
	case no_done:
		{
			pter.setPen(QPen(Qt::yellow, 4 * size));
			std::vector<QPoint>::iterator iter;
			for(iter  = vanish_lines[0].begin(); iter < vanish_lines[0].end() && (iter + 1) < vanish_lines[0].end();iter += 2)
			{
				pter.drawLine(*iter, *(iter + 1));
			}
		}
	default: break;
	}

	if(is_origin)
	{
		//draw the origin point.
		pter.setPen(QPen(Qt::red, 10 * size));
		pter.drawPoint(origin_pt);
		pter.setPen(QPen(Qt::white, 4 * size));
		pter.drawText(origin_pt, "0");
	}

	pter.end();

	tmp_img = pimg;
	pimg = new QImage(tmp_img->scaled(tmp_img->width() * size, tmp_img->height() * size));
	delete tmp_img;
}


void MainWindow::draw_text()
{
	QPainter pter(pimg);
	pter.setFont(QFont("Courier", 8, QFont::Bold, true));
	pter.setPen(QPen(Qt::white, 4 * size));

	switch(is_vanished)
	{
	case z_done:
		{
			pter.drawPoint(QPoint(vanish_pt[2].x,vanish_pt[2].y));
			pter.drawText(QPoint(vanish_pt[2].x,vanish_pt[2].y), "Z");
		}
	case y_done:
		{
			pter.drawPoint(QPoint(vanish_pt[1].x,vanish_pt[1].y));
			pter.drawText(QPoint(vanish_pt[1].x,vanish_pt[1].y), "Y");
		}
	case x_done:
		{
			pter.drawPoint(QPoint(vanish_pt[0].x,vanish_pt[0].y));
			pter.drawText(QPoint(vanish_pt[0].x,vanish_pt[0].y), "X");
		}
	default: break;
	}

	pter.end();
}