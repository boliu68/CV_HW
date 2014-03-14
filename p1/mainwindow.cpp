#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	//state initialization
	isctl_pressed = false;
	isplus_pressed = false;
	isminus_pressed = false;
	isentr_pressed = false;
	isback_pressed = false;
	img_loaded = false;
	is_snap = false;
	is_modified = true;

	path_id = 0;
	chosen_path = -1;
	size = 1;

	is_seed = false;
	workstates = image_only_contour;
    is_mask=false;
}

MainWindow::~MainWindow()
{
    delete ui;
}
