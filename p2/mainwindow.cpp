#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	//initialize
	mod = NULL;

	img_loaded = false;
	is_vanished  = no_done;
	is_origin = false;
	
	isctl_pressed = false;//to record whether the control buttion is pressed
	isplus_pressed = false;
	isminus_pressed = false;
	isentr_pressed = false;
	isback_pressed = false;
	is_3d = false;
	is_texture = false;
	is_bottom = false;

	vbottom = NULL;
	vtop = NULL;

	bottom.x = -1;
	bottom.y = -1;

	for(int i = 0; i < 3; i++)
		ref_vpt[i] = NULL;

	size = 0.5;

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

