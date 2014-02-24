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

	path_id = 0;
	size = 1;

	is_seed = false;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    workstates=image_only;
=======
	workstates = image_only_contour;
>>>>>>> 8281ddbe12dc7237ab07fc602fd8cbdca6b6f23b
=======
	workstates = image_only_contour;
=======
    workstates=image_only;
>>>>>>> 3636f17478f45c645b5db5a062bdf6bf2e58ede9
>>>>>>> 9bba361707a7b06d346d2c45679ca382bc54b6bb
=======
	workstates = image_only_contour;
>>>>>>> 288329599a6db329418469ab0871736966e4671b
}

MainWindow::~MainWindow()
{
    delete ui;
}
