#include "scissor_diag.h"
#include "ui_scissor_diag.h"

scissor_diag::scissor_diag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scissor_diag)
{
    ui->setupUi(this);
	workstates = image_only_contour;
	is_snap = false;
	is_brush = true;
	is_modified = true;
}

scissor_diag::~scissor_diag()
{
    delete ui;
}
