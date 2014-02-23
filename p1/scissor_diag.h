#ifndef SCISSOR_DIAG_H
#define SCISSOR_DIAG_H
#include <QDialog>
#include "workstates.h"
//#include "mainwindow.h"

namespace Ui {
	class scissor_diag;
	class MainWindow;
}

class scissor_diag : public QDialog
{
    Q_OBJECT

public:
    explicit scissor_diag(QWidget *parent = 0);
	int workstates;
    ~scissor_diag();
	//MainWindow * ptr;

private slots:
	void sc_image_contour();
	void sc_image_only();
	void sc_pixel_node();
	void sc_cost_graph();
	void sc_path_tree();
	void sc_min_path();
	void sc_OK();

private:
    Ui::scissor_diag *ui;
};

#endif // SCISSOR_DIAG_H
