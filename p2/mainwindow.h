#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QPixmap>
#include <qevent.h>
#include <QPainter>
#include <vector>
#include <QColor>
#include <qthread.h>
#include "states.h"
#include <QFont>
#include <QRegExp>
#include <singleviewmodel.h>
#include "show_texture.h"


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
	QImage* img;
	QImage* pimg;

	SingleViewModel* mod;
	
	bool img_loaded;
	int is_vanished;//the line segment for calculate vanish point is not yet assigned.
	bool is_origin; //the point of origin point is not yet assigned.

	bool isctl_pressed;//to record whether the control buttion is pressed
	bool isplus_pressed;
	bool isminus_pressed;
	bool isentr_pressed;
	bool isback_pressed;
	int d3_states;
	bool is_bottom;
	bool is_texture;
	bool is_exist_texture;

	double size;
	std::vector<QPoint> vanish_lines[3];
	QPoint origin_pt;
	cv::Point2d scale_pt;
	cv::Point3d vanish_pt[3];
	cv::Point2d proj_pt;
	
	//for 3d measurement
	cv::Point2d bottom;
	Vertex * vbottom;
	Vertex * vtop;
	cv::Point2d top;
	std::vector<Vertex *> store_vertex;
	cv::Point2d d3_select_pt; 

	cv::Point2d ref_pt[3];
	double ref_length[3];
	Vertex *ref_vpt[3];

	vector<Vertex*> polygon_vertex;
	vector<cv::Point2d> polygon_point;
	Face* gen_face;

	void draw_image();
	void draw_text();
	void draw_pimg();
	void resize_widget();
	void change_vanish(QString vp_str, QString info_str, int xyz);
	void draw_line_cross(QPainter* pter, double x1, double y1, double x2, double y2);
	void restart();

	bool click_position(int x, int y, int& x_, int& y_);

protected:
	void mouseMoveEvent(QMouseEvent* e);
	void mousePressEvent(QMouseEvent * e);
	void keyPressEvent(QKeyEvent * e);
	void keyReleaseEvent(QKeyEvent * e);

private slots:
	void onLoadImage();
	void on_vanish();
	//void on_3d();
	void on_top();
	void on_bot();
	void on_face();
	void on_texture();
	void save_config();
	void load_config();
	void on_vrml();
};

#endif // MAINWINDOW_H
