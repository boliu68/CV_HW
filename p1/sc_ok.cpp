#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scissor_diag.h"

void scissor_diag::sc_OK()
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

	void scissor_diag::sc_image_contour()
	{
		MainWindow* ptr =(MainWindow*)parentWidget();
		ptr->workstates = image_only_contour;
		ptr->on_image_contour();
	}

	void scissor_diag::sc_image_only()
	{
		MainWindow* ptr =(MainWindow*)parentWidget();
		ptr->workstates = image_only;
		ptr->on_image_only();
	}

	void scissor_diag::sc_pixel_node()
	{
		MainWindow* ptr =(MainWindow*)parentWidget();
		ptr->workstates = pixel_node;
		ptr->on_pixel_node();
	}

	void scissor_diag::sc_cost_graph()
	{
		MainWindow* ptr =(MainWindow*)parentWidget();
		ptr->workstates = cost_graph;
		ptr->on_cost_graph();
	}

	void scissor_diag::sc_path_tree()
	{
		MainWindow* ptr =(MainWindow*)parentWidget();
		ptr->workstates = path_tree;
		ptr->on_path_tree();
	}

	void scissor_diag::sc_min_path(){
		MainWindow* ptr =(MainWindow*)parentWidget();
		ptr->workstates = min_path;
		ptr->on_min_path();
	}