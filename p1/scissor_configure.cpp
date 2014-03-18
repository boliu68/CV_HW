#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

void MainWindow::on_scissor()
{
<<<<<<< HEAD
	//delete sd;
	sd = new scissor_diag(this);
=======
    sd = new Scissor_diag(this);
>>>>>>> 51150595053c4d3b9a7d395e993fe83a917b5715
	sd->show();
}
