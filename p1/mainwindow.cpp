#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	//state initialization
	isctl_pressed = false;
	is_seed = false;
    workstates=image_only;
}

MainWindow::~MainWindow()
{
    delete ui;
}
