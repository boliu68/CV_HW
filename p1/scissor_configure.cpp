#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

void MainWindow::on_scissor()
{
	//delete sd;
	sd = new scissor_diag(this);
	sd->show();
}