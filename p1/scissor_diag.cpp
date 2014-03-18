#include "scissor_diag.h"
#include "ui_scissor_diag.h"
#include "mainwindow.h"

Scissor_diag::Scissor_diag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scissor_diag)
{
<<<<<<< HEAD
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

=======
    workstates = image_only_contour;
    MainWindow *mw=(MainWindow*)parent;
    is_snap = mw->is_snap;
    is_brush = mw->is_mask;
    is_modified = mw->is_modified;
    ui->setupUi(this);
>>>>>>> 51150595053c4d3b9a7d395e993fe83a917b5715
}

Scissor_diag::~Scissor_diag()
{
    delete ui;
}
