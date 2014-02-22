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
#include <vector>

using namespace std;

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
	QImage * pimg;//used for painting;
	QImage * pathtree;
	QPainter * pter;
	void draw_image();
	bool click_position(int x, int y, int &x_, int &y_); //obtain the position with respect to the label

	Iscissor * ics; //the iscissor class
	vector<vector<QPoint>> ex_path;
	vector<vector<QPoint>> scale_expath;
	vector<vector<QPoint>> click_point;
	int path_id; //to indicate the id of path;
	float size;//the size the shown image

	int workstates; //to indiciate in which work state.

	bool isctl_pressed;//to record whether the control buttion is pressed
	bool isplus_pressed;
	bool isminus_pressed;
	bool isentr_pressed;

	bool is_seed; //to record whether the seed point is alread put.

private slots:
	void OpenImage();
	void modify_expath(float scale);
	void reset_image();

	//the slots to change workstates
    void on_image_only();
    void on_image_contour();
    void on_pixel_node();
    void on_cost_graph();
    void on_path_tree();
    void on_min_path();
	void closet_point();
	void paint_path();

protected:
	//overwrite the track the mouse press event
	void mousePressEvent(QMouseEvent * e);
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent *e);  
	void keyReleaseEvent(QKeyEvent *e);

};

#endif // MAINWINDOW_H
