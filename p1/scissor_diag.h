#ifndef SCISSOR_DIAG_H
#define SCISSOR_DIAG_H
#include <QDialog>
#include "workstates.h"
//#include "mainwindow.h"

namespace Ui {
	class scissor_diag;
}

class Scissor_diag : public QDialog
{
    Q_OBJECT

public:
    explicit Scissor_diag(QWidget *parent = 0);
    int workstates;
    bool is_snap;
    bool is_brush;
    bool is_modified;
    ~Scissor_diag();
	//MainWindow * ptr;

private slots:
	void sc_image_contour();
	void sc_image_only();
	void sc_pixel_node();
	void sc_cost_graph();
	void sc_path_tree();
	void sc_min_path();
	void sc_OK();
	void sc_snap();
	void sc_brush();
	void cs_cf();
	void sc_change_blur();

private:
    Ui::scissor_diag *ui;
};

#endif // SCISSOR_DIAG_H
