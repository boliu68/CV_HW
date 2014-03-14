#include "scissor_diag.h"
#include "ui_scissor_diag.h"
#include "mainwindow.h"

Scissor_diag::Scissor_diag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scissor_diag)
{
    workstates = image_only_contour;
    MainWindow *mw=(MainWindow*)parent;
    is_snap = mw->is_snap;
    is_brush = mw->is_mask;
    is_modified = mw->is_modified;
    ui->setupUi(this);
}

Scissor_diag::~Scissor_diag()
{
    delete ui;
}
