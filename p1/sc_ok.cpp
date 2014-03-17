#include "mainwindow.h"
#include "scissor_diag.h"
#include "ui_scissor_diag.h"


void Scissor_diag::sc_OK()
{
	/*	MainWindow* ptr =(MainWindow*)parentWidget();
	ptr->workstates = this->workstates;

	if (ptr->img_loaded)
	{
	switch(workstates)
	{
	case image_only_contour:
	ptr->on_image_contour();break;
	case image_only:
	ptr->on_image_only();break;
	case pixel_node:
	ptr->on_pixel_node();break;
	case cost_graph:
	ptr->on_cost_graph();break;
	case path_tree:
	ptr->on_path_tree();break;
	case min_path:
	ptr->on_min_path();break;
	}
	}
	this->destroy();
	*/
	this->close();
}

void Scissor_diag::sc_image_contour()
{
	MainWindow* ptr =(MainWindow*)parentWidget();
	ptr->workstates = image_only_contour;
	ptr->on_image_contour();
}

void Scissor_diag::sc_image_only()
{
	MainWindow* ptr =(MainWindow*)parentWidget();
	ptr->workstates = image_only;
	ptr->on_image_only();
}

void Scissor_diag::sc_pixel_node()
{
	MainWindow* ptr =(MainWindow*)parentWidget();
	ptr->workstates = pixel_node;
	ptr->on_pixel_node();
}

void Scissor_diag::sc_cost_graph()
{
	MainWindow* ptr =(MainWindow*)parentWidget();
	ptr->workstates = cost_graph;
	ptr->on_cost_graph();
}

void Scissor_diag::sc_path_tree()
{
	MainWindow* ptr =(MainWindow*)parentWidget();
	ptr->workstates = path_tree;
	ptr->on_path_tree();
}

void Scissor_diag::sc_min_path(){
	MainWindow* ptr =(MainWindow*)parentWidget();
	ptr->workstates = min_path;
	ptr->on_min_path();
}

void Scissor_diag::sc_snap()
{
	if (is_snap)
		ui->sc_snap_on->setText("Snap Seed OFF");
	else
		ui->sc_snap_on->setText("Snap Seed ON");

	is_snap = !is_snap;

	MainWindow* ptr =(MainWindow*)parentWidget();
	ptr->is_snap = this->is_snap;
}

void Scissor_diag::sc_brush()
{
	if(is_brush)
		ui->sc_brush->setText("Brush OFF");
	else
		ui->sc_brush->setText("Brush ON");

	is_brush = !is_brush;

	MainWindow* ptr =(MainWindow*)parentWidget();
<<<<<<< HEAD
	//ptr->is_mask = this->is_brush;
	ptr->on_brush();
=======
    ptr->is_mask=is_brush;

    ptr->on_brush(is_brush);
>>>>>>> 51150595053c4d3b9a7d395e993fe83a917b5715
}

void Scissor_diag::sc_change_blur()
{
	return;
}

void Scissor_diag::cs_cf()
{
	if(is_modified)
		this->ui->sc_cost_function->setText("Cost Function(Basic)");
	else
		this->ui->sc_cost_function->setText("Cost Function(Modified)");
	is_modified = !is_modified;
	MainWindow* ptr =(MainWindow*)parentWidget();
	ptr->change_function();
	//ptr->is_modified = this->ism
	//ptr->is_modified = !ptr->is_modified;
	return;
}
