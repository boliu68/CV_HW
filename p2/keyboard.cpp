#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>

using namespace std;

void MainWindow::keyPressEvent(QKeyEvent * e)
{
	//judge whether control is pressed
	if (e->key() == Qt::Key_Control)
	{
		isctl_pressed = true;
	}
	if (e->key() == Qt::Key_Equal || e->key() == Qt::Key_Plus)
	{
		isplus_pressed = true;
	}
	if (e->key() == Qt::Key_hyphen || e->key() == Qt::Key_Minus)
	{
		isminus_pressed = true;
	}
	if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
	{
		isentr_pressed= true;
	}
	if(e->key() == Qt::Key_Backspace)
	{
		isback_pressed = true;
	}


	if (isctl_pressed && isplus_pressed)
	{
		//enlarge the picture
		size = size + 0.1;
		draw_image();
	}

	if (isctl_pressed && isminus_pressed)
	{
		//ensmaller the picture.
		size = size - 0.1;
		draw_image();
	}
}

void MainWindow::keyReleaseEvent(QKeyEvent * e)
{
	if (e->key() == Qt::Key_Control)
	{
		isctl_pressed = false;
	}
	if (e->key() == Qt::Key_Plus || e->key() == Qt::Key_Equal)
	{
		isplus_pressed = false;
	}
	if (e->key() == Qt::Key_hyphen || e->key() == Qt::Key_Minus)
	{
		isminus_pressed = false;
	}
	if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
	{
		isentr_pressed= false;
	}
	if(e->key() == Qt::Key_Backspace)
	{
		isback_pressed = false;
	}
}
