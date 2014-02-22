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
	path_id = 0;
	size = 1;

	is_seed = false;
	workstates = image_only_contour;
}

MainWindow::~MainWindow()
{
    delete ui;
}
