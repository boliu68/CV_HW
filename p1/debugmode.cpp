#include "mainwindow.h"
#include "ui_mainwindow.h"	

void MainWindow::on_pixel_node()
{
	workstates = pixel_node;

	//draw pixel node
	delete pimg;
	pimg = new QImage(ics->drawPixelNode());

	draw_image();
}


void MainWindow::on_cost_graph()
{
	workstates = cost_graph;
	
	//obtain the cost graph
	delete pimg;
	pimg = new QImage(ics->drawCostGraph());
	draw_image();
}

void MainWindow::on_path_tree()
{
	workstates = path_tree;

	//obtain the path tree
	delete pimg;
	pimg = new QImage(ics->drawPathTree());
	draw_image();
}

void MainWindow::on_min_path()
{
	workstates = min_path;

	//obtain the min path
}