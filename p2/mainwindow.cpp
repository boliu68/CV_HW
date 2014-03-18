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

	size = 0.5;

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
