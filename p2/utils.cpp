#include "mainwindow.h"
#include "ui_mainwindow.h"

bool MainWindow::click_position(int x, int y, int& x_, int& y_)
{
	x_ = floor((x - ui->ShowImage->x() - ui->centralWidget->x()) / size);
	y_ = floor((y - ui->ShowImage->y() - ui->centralWidget->y()) / size);

	return (x_ >=0 && y_ >=0 && x_ < img->width() && y_ < img->height());
}

