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
	
	restart();
	img->load(filename);
	img_loaded = true;
	mod = new SingleViewModel(img);
	draw_image();

	//QMessageBox::information(this,
                                     //tr("Please insert the line segment for x, y and z axis."),
                                     //tr("Please insert the line segment for x, y and z axis!"));
	
	this->ui->infobox->setText("Please select lines in x direction.");
}


void MainWindow::restart()
{
		//initialize
	mod = NULL;

	is_vanished  = no_done;
	is_origin = false;
	
	isctl_pressed = false;//to record whether the control buttion is pressed
	isplus_pressed = false;
	isminus_pressed = false;
	isentr_pressed = false;
	isback_pressed = false;
	d3_states = no_done;
	is_texture = false;
	is_bottom = false;
	is_exist_texture = false;

	vbottom = NULL;
	vtop = NULL;

	bottom.x = -1;
	bottom.y = -1;

	for(int i = 0; i < 3; i++)
	{
		vanish_lines[i].clear();
		ref_vpt[i] = NULL;
	}

	size = 0.5;
	store_vertex.clear();
	polygon_vertex.clear();
}