#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::draw_image()
{
	draw_pimg();

	int corner_x = ui->centralWidget->x() + ui->ShowImage->x();
	int corner_y = ui->centralWidget->y() + ui->ShowImage->y();

	ui->ShowImage->resize(pimg->width(), pimg->height());
	ui->Vanish_Point->move(pimg->width() + 20, 20);

	ui->D3->move(pimg->width() + 20, ui->Vanish_Point->y() + ui->D3->height() + 20);
	ui->texture->move(pimg->width() + 50 + ui->texture->width(), ui->Vanish_Point->y() + ui->D3->height() + 20);
	ui->vrml->move(pimg->width() + 20, ui->D3->y() + ui->vrml->height() + 20);
	ui->quit->move(pimg->width() + 50 + ui->vrml->width(), ui->D3->y() + ui->vrml->height() + 20);

	ui->int_scale->move(pimg->width() + 20 + ui->int_scale->width(), 20);
	ui->infobox->move(pimg->width() + 20, pimg->height() - ui->infobox->height());
	ui->line->move(pimg->width() + 10, 0);
	ui->centralWidget->resize(pimg->width() + corner_x + ui->infobox->width() + 30, pimg->height() + corner_y + 30);

	ui->infobox->setFont(QFont("Courier", 20 * std::min(size, 1.0), QFont::Bold, true));
	ui->infobox->resize(img->width() * std::min(size, 1.0), img->height() * std::min(size, 1.0));

	this->resize(pimg->width() + corner_x + ui->infobox->width() + 30, pimg->height() + corner_y + 30);

	ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
}


void MainWindow::draw_pimg()
{
	QImage * tmp_img = pimg;
	pimg = new QImage(*img);
	delete tmp_img;

	draw_text();

	QPainter pter(pimg);
	pter.setFont(QFont("Courier", 8, QFont::Bold, true));

	if(is_texture)
	{
		pter.setPen(QPen(Qt::green, 4 * size));
		
		//draw polygon
		if(polygon_vertex.size() >= 2)
		{
			std::vector<Vertex*>::iterator iter = polygon_vertex.begin();
			while(iter != polygon_vertex.end() - 1)
			{
				pter.drawLine((*iter)->Coor2d().x, (*iter)->Coor2d().y, (*(iter + 1))->Coor2d().x,  (*(iter + 1))->Coor2d().y);
				iter ++;
			}
		}
	}
	else if(is_3d)
	{

		if(!is_bottom)
		{
			//draw the z axis line
			pter.setPen(QPen(Qt::white, 4 * size));
			if(vbottom == NULL) pter.drawText(QPoint(bottom.x, bottom.y), "Bottom"); //write "bottom"
			pter.drawLine(QPoint(bottom.x, bottom.y), QPoint(vanish_pt[2].x / vanish_pt[2].z, vanish_pt[2].y / vanish_pt[2].z));
		}

		pter.setPen(QPen(Qt::green, 20 * size));
		pter.drawPoint(d3_select_pt.x, d3_select_pt.y);
	}
	else{
		switch(is_vanished)
		{
		case y_done:
			{
				pter.setPen(QPen(Qt::white, 4 * size));
				std::vector<QPoint>::iterator iter;
				for(iter  = vanish_lines[2].begin(); iter < vanish_lines[2].end() && (iter + 1) < vanish_lines[2].end(); iter += 2)
				{
					pter.drawLine(*iter, *(iter + 1));
				}
			}
		case x_done:
			{
				pter.setPen(QPen(Qt::gray, 4 * size));
				std::vector<QPoint>::iterator iter;
				for(iter  = vanish_lines[1].begin(); iter < vanish_lines[1].end() && (iter + 1) < vanish_lines[1].end(); iter += 2)
				{
					pter.drawLine(*iter, *(iter + 1));
				}
			}
		case no_done:
			{
				pter.setPen(QPen(Qt::yellow, 4 * size));
				std::vector<QPoint>::iterator iter;
				for(iter  = vanish_lines[0].begin(); iter < vanish_lines[0].end() && (iter + 1) < vanish_lines[0].end();iter += 2)
				{
					pter.drawLine(*iter, *(iter + 1));
				}
				break;
			}
		case x_scale:
		case y_scale:
		case z_scale:
			{
				pter.setPen(QPen(Qt::yellow, 4 * size));
				//draw the line between origin and vanish point.
				pter.drawLine(origin_pt, QPoint(vanish_pt[is_vanished - x_scale].x / vanish_pt[is_vanished - x_scale].z, vanish_pt[is_vanished - x_scale].y / vanish_pt[is_vanished - x_scale].z));
				pter.setPen(QPen(Qt::red, 20 * size));
				pter.drawPoint(QPoint(proj_pt.x, proj_pt.y));
				pter.setPen(QPen(Qt::green, 30 * size));
				pter.drawPoint(QPoint(scale_pt.x, scale_pt.y));
				pter.drawText(QPoint(scale_pt.x, scale_pt.y), "Select Point");
			}
		default: break;
		}
	}


	//draw the vertex and id s
	pter.setPen(QPen(Qt::white, 4 * size));
	std::vector<Vertex *>::iterator iter = store_vertex.begin();
	std::vector<Vertex *>::iterator piter = polygon_vertex.begin();
	while(iter != store_vertex.end())
	{
		QString id;
		id.sprintf("%d", (*iter)->ID());

		if(vbottom != NULL && vbottom->ID() == (*iter)->ID())
		{
			pter.setPen(QPen(Qt::green, 4 * size));
			pter.drawPoint((*iter)->Coor2d().x, (*iter)->Coor2d().y);
			pter.drawText((*iter)->Coor2d().x, (*iter)->Coor2d().y, id);
			iter++;continue;
		}
		else if(vtop != NULL && vtop->ID() == (*iter)->ID())
		{
			pter.setPen(QPen(Qt::red, 4 * size));
			pter.drawPoint((*iter)->Coor2d().x, (*iter)->Coor2d().y);
			pter.drawText((*iter)->Coor2d().x, (*iter)->Coor2d().y, id);
			iter++;continue;
			//the top is chosen
		}
		else if(polygon_vertex.size()>0)
		{
			piter = polygon_vertex.begin();
			while(piter != polygon_vertex.end())
			{
				if((*piter)->ID() == (*iter)->ID())
				{
					pter.setPen(QPen(Qt::green, 4 * size));
					pter.drawPoint((*iter)->Coor2d().x, (*iter)->Coor2d().y);
					pter.drawText((*iter)->Coor2d().x, (*iter)->Coor2d().y, id);
					break;
				}
				piter++;
			}

			if(piter != polygon_vertex.end()) 
			{iter ++;continue;}
		}

		pter.setPen(QPen(Qt::white, 4 * size));
		pter.drawPoint((*iter)->Coor2d().x, (*iter)->Coor2d().y);
		pter.drawText((*iter)->Coor2d().x, (*iter)->Coor2d().y, id);
		iter ++;
	}


	if(vtop != NULL)
	{//end of the 3d
		vtop = NULL;
		vbottom = NULL;
	}

	pter.end();

	tmp_img = pimg;
	pimg = new QImage(tmp_img->scaled(tmp_img->width() * size, tmp_img->height() * size));
	delete tmp_img;
}


void MainWindow::draw_text()
{
	QPainter pter(pimg);
	pter.setFont(QFont("Courier", 8, QFont::Bold, true));
	pter.setPen(QPen(Qt::white, 4 * size));

	switch(is_vanished)
	{
	case x_scale:
	case y_scale:
	case z_scale:
	case z_done:
		{
			pter.drawPoint(QPoint(vanish_pt[2].x / vanish_pt[2].z,vanish_pt[2].y  / vanish_pt[2].z));
			pter.drawText(QPoint(vanish_pt[2].x  / vanish_pt[2].z,vanish_pt[2].y  / vanish_pt[2].z), "Z");
		}
	case y_done:
		{
			pter.drawPoint(QPoint(vanish_pt[1].x  / vanish_pt[1].z,vanish_pt[1].y  / vanish_pt[1].z));
			pter.drawText(QPoint(vanish_pt[1].x  / vanish_pt[1].z,vanish_pt[1].y  / vanish_pt[1].z), "Y");
		}
	case x_done:
		{
			pter.drawPoint(QPoint(vanish_pt[0].x  / vanish_pt[0].z,vanish_pt[0].y  / vanish_pt[0].z));
			pter.drawText(QPoint(vanish_pt[0].x  / vanish_pt[0].z,vanish_pt[0].y  / vanish_pt[0].z), "X");
		}
	default: break;
	}


	if(is_origin)
	{
		//draw the origin point.
		pter.setPen(QPen(Qt::red, 10 * size));
		pter.drawPoint(origin_pt);
		pter.setPen(QPen(Qt::white, 4 * size));
		pter.drawText(origin_pt, "0");
	}

	pter.end();
}