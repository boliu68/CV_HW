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
#include <QColor>
#include "scissor_diag.h"

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
	int workstates; //to indiciate in which work state.
	void on_image_only();
    void on_image_contour();
    void on_pixel_node();
    void on_cost_graph();
    void on_path_tree();
    void on_min_path();
    void on_brush(bool isbrush);
	bool img_loaded;
	bool is_snap;
<<<<<<< HEAD
	bool is_mask;
	bool is_modified;//to record whether the modified cost funtion is used.
=======
    bool is_mask;
    bool is_modified;//to record whether the modified cost funtion is used.
>>>>>>> 51150595053c4d3b9a7d395e993fe83a917b5715
	void change_function();

private:
    Ui::MainWindow *ui;
    Scissor_diag * sd;

	QImage * img;
	QImage * pimg;//used for painting;
	QImage * pathtree;
	QImage * mask;
	QImage * store_mask;
	QPainter * pter;

	Iscissor * ics; //the iscissor class
    vector<vector<QPoint> > ex_path;
    vector<vector<QPoint> > scale_expath;
    vector<vector<QPoint> > click_point;
	vector<QPoint> mask_point;

	int path_id; //to indicate the id of path;
	int chosen_path;//to indicate the path that is click by mouse
	float size;//the size the shown image

	bool isctl_pressed;//to record whether the control buttion is pressed
	bool isplus_pressed;
	bool isminus_pressed;
	bool isentr_pressed;
	bool isback_pressed;
	bool is_seed; //to record whether the seed point is alread put.
<<<<<<< HEAD
	
=======

>>>>>>> 51150595053c4d3b9a7d395e993fe83a917b5715
	void draw_image();
	bool click_position(int x, int y, int &x_, int &y_); //obtain the position with respect to the label
	void modify_expath(float scale);
	void reset_image();
	void closet_point();
	void paint_path(bool contain_mask = true);
	void choose_path(int x, int y);
	void add_mask(int x, int y);
	void reset_all();

private slots:
	void OpenImage();
	void save_contour();
	void save_mask();

	//the slots to change workstates
    /*void on_image_only();
    void on_image_contour();
    void on_pixel_node();
    void on_cost_graph();
    void on_path_tree();
    void on_min_path();*/
	void on_scissor();

protected:
	//overwrite the track the mouse press event
	void mousePressEvent(QMouseEvent * e);
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent *e);  
	void keyReleaseEvent(QKeyEvent *e);
};

#endif // MAINWINDOW_H
