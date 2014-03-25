#include "mainwindow.h"
#include "ui_mainwindow.h"


/*void MainWindow::on_3d()
{
	ui->infobox->setText("Please assign the bottom and top point");
	is_3d = true;
	is_bottom = true;
	is_texture = false;
}*/

void MainWindow::on_bot()
{
	d3_states = only_bottom;
	vbottom = NULL;
	bottom.x = -1;
	bottom.y = -1;
	ui->texture2->setEnabled(false);
	polygon_vertex.clear();
	draw_image();
}

void MainWindow::on_top()
{
	d3_states = top_bottom;
	vbottom = NULL;
	vtop = NULL;
	bottom.x = -1;
	bottom.y = -1;
	top.x = -1;
	top.y = -1;
	is_bottom = true;
	ui->texture2->setEnabled(false);
	polygon_vertex.clear();
	draw_image();
}

void MainWindow::on_face()
{
	d3_states = point_face;
	ui->texture2->setEnabled(true);
	polygon_vertex.clear();
	is_exist_texture = false;
	vbottom = NULL;
	vtop = NULL;
	draw_image();
}