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
class scissor_diag;
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
	bool img_loaded;

private:
    Ui::MainWindow *ui;
	scissor_diag * sd;

	QImage * img;
	QImage * pimg;//used for painting;
	QImage * pathtree;
	QImage * mask;
	QPainter * pter;

	Iscissor * ics; //the iscissor class
	vector<vector<QPoint>> ex_path;
	vector<vector<QPoint>> scale_expath;
	vector<vector<QPoint>> click_point;
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

	void draw_image();
	bool click_position(int x, int y, int &x_, int &y_); //obtain the position with respect to the label
	void modify_expath(float scale);
	void reset_image();
	void closet_point();
	void paint_path(bool contain_mask = true);
	void choose_path(int x, int y);
	void add_mask(int x, int y);

private slots:
	void OpenImage();
	void save_contour();
	void save_mask();

	//the slots to change workstates
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 288329599a6db329418469ab0871736966e4671b
    void on_image_only();
=======
    /*void on_image_only();
>>>>>>> bbd39c6fcbf5b20e7815e28bb07fd623dea7770c
    void on_image_contour();
    void on_pixel_node();
    void on_cost_graph();
    void on_path_tree();
<<<<<<< HEAD
    void on_min_path();
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 9bba361707a7b06d346d2c45679ca382bc54b6bb
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
<<<<<<< HEAD
=======
	void on_image_only();
	void on_image_contour();
	void on_pixel_node();
	void on_cost_graph();
	void on_path_tree();
	void on_min_path();
>>>>>>> 8281ddbe12dc7237ab07fc602fd8cbdca6b6f23b
=======
    void on_image_only();
    void on_image_contour();
    void on_pixel_node();
    void on_cost_graph();
    void on_path_tree();
    void on_min_path();
>>>>>>> 909e849172b2ab1b25e78db1e17fab014974d539
=======
>>>>>>> 3636f17478f45c645b5db5a062bdf6bf2e58ede9
>>>>>>> 9bba361707a7b06d346d2c45679ca382bc54b6bb
=======
>>>>>>> 288329599a6db329418469ab0871736966e4671b
=======
	void closet_point();
	void paint_path();
>>>>>>> f61be8bfd49c90353c47466843719ef968cf0a62
=======
    void on_min_path();*/
	void on_scissor();
	void on_brush();
>>>>>>> bbd39c6fcbf5b20e7815e28bb07fd623dea7770c

protected:
	//overwrite the track the mouse press event
	void mousePressEvent(QMouseEvent * e);
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent *e);  
	void keyReleaseEvent(QKeyEvent *e);
};

#endif // MAINWINDOW_H
