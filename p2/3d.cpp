#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::on_3d()
{
	ui->infobox->setText("Please assign the bottom and top point");
	is_3d = true;
	is_bottom = true;
	is_texture = false;
}