#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::mousePressEvent(QMouseEvent *e)
{
	if(e->button() == Qt::LeftButton && isctl_pressed)
	{
		//e->pos().rx;
		//e->pos().ry;
		setCursor(Qt::CrossCursor);
	}
}

void MainWindow::keyPressEvent(QKeyEvent * e)
{
	//judge whether control is pressed
	if (e->key() == Qt::Key_Control)
	{
		isctl_pressed = true;
	}
}

void MainWindow::keyReleaseEvent(QKeyEvent * e)
{
	if (e->key() == Qt::Key_Control)
	{
		isctl_pressed = false;
	}
}