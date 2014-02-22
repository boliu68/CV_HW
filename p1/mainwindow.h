#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QPixmap>
#include "workstates.h"
#include <qevent.h>
#include "iscissor.h"
#include <QPainter>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

	QImage * img;
	QPainter * pter;
	void draw_image();
	void click_position(int x, int y, int &x_, int &y_); //obtain the position with respect to the label

	Iscissor * ics; //the iscissor class

	int workstates; //to indiciate in which work state.

	bool isctl_pressed;//to record whether the control buttion is pressed
	bool is_seed; //to record whether the seed point is alread put.

private slots:
	void OpenImage();

	//the slots to change workstates
    void on_image_only()
    {
        workstates = image_only;
        draw_image();
    }
    void on_image_contour(){workstates = image_only_contour;draw_image();}
    void on_pixel_node(){workstates = pixel_node;draw_image();}
    void on_cost_graph()
    {
        workstates = cost_graph;
        draw_image();
    }
    void on_path_tree(){workstates = path_tree;draw_image();}
    void on_min_path(){workstates = min_path;this->setMouseTracking(true);draw_image();}

protected:
	//overwrite the track the mouse press event
	void mousePressEvent(QMouseEvent * e);
	void keyPressEvent(QKeyEvent *e);  
	void keyReleaseEvent(QKeyEvent *e);

};

#endif // MAINWINDOW_H
