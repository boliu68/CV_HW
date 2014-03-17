#include "scissor_diag.h"
#include "ui_scissor_diag.h"
#include "mainwindow.h"

scissor_diag::scissor_diag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scissor_diag)
{
	MainWindow* ptr =(MainWindow*)parentWidget();
	is_snap = ptr->is_snap;
	is_brush = ptr->is_mask;
	is_modified = ptr->is_modified;
    ui->setupUi(this);
	workstates = image_only_contour;

	
	if (is_snap)
		ui->sc_snap_on->setText("Snap Seed OFF");
	else
		ui->sc_snap_on->setText("Snap Seed ON");
	if(is_brush)
		ui->sc_brush->setText("Brush OFF");
	else
		ui->sc_brush->setText("Brush ON");
	if(is_modified)
		this->ui->sc_cost_function->setText("Cost Function(Basic)");
	else
		this->ui->sc_cost_function->setText("Cost Function(Modified)");

}

scissor_diag::~scissor_diag()
{
    delete ui;
}
