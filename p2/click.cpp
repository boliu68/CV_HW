#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::mousePressEvent(QMouseEvent * e)
{
	if(img_loaded)
	{
		if(e->button() == Qt::LeftButton)
		{
			int x, y;
			if(click_position(e->x(), e->y(), x, y))
			{
				if(is_3d)
				{
					//add new point
					if(is_bottom)
					{
						//bottom is a new point
						bottom.x = x;
						bottom.y = y;
						is_bottom = false;
						//store_vertex is the origin
						//vbottom = mod->compute3DCoordinate(store_vertex[0], bottom);
						//store_vertex.push_back(vbottom);
					}
					else
					{
						d3_select_pt = mod->findPointOnDirection(cv::Point2d(x, y), bottom);
						top.x = d3_select_pt.x;
						top.y = d3_select_pt.y;

						//get the 3d coordinate of top point;
						if(vbottom == NULL)
						{
							 mod->compute3DCoordinate(bottom, top,
                             vbottom, vtop);
							 store_vertex.push_back(vbottom);
						}
						else
						{
							vtop = mod->compute3DCoordinate(vbottom, top);
						}
							
						store_vertex.push_back(vtop);

						QString info = "Bottom coordinate:\n";
						QString tmp;
						info += tmp.sprintf("(%f,%f,%f)\n", vbottom->Coor3d().x, vbottom->Coor3d().y, vbottom->Coor3d().z);
						info += "Top coordinate:\n";
						info += tmp.sprintf("(%f,%f,%f)", vtop->Coor3d().x, vtop->Coor3d().y, vtop->Coor3d().z);
						ui->infobox->setText(info);

						is_3d = false;
						is_bottom = true;
					}
				}
				else{
					if(is_vanished == no_done)
					{
						//get the line parallel to x, y, z
						vanish_lines[0].push_back(QPoint(x,y));
					}
					else if(is_vanished == x_done)
					{
						vanish_lines[1].push_back(QPoint(x,y));
					}
					else if(is_vanished == y_done)
					{
						vanish_lines[2].push_back(QPoint(x,y));
					}

					else if(!is_origin)
					{
						//assign the origin point
						origin_pt = QPoint(x,y);
						Vertex* origin_vertex = mod->setOrigin(cv::Point2d(x,y));

						if(origin_vertex != NULL)
						{
							is_origin = true;

							store_vertex.push_back(origin_vertex);

							QString tmp;
							QString info = "Please choose a point and insert the distance in 3 dimension.\n";
							info += "Origin Point information:\n";
							info += tmp.sprintf("2D Coordinate:%f,%f\n", origin_vertex->Coor2d().x, origin_vertex->Coor2d().y);
							info += tmp.sprintf("3D Coordinate:%f,%f,%f", origin_vertex->Coor3d().x, origin_vertex->Coor3d().y,origin_vertex->Coor3d().z);

							ui->infobox->setText(info);
							ui->Vanish_Point->setText("Confirm");
							is_vanished = x_scale;

							this->setMouseTracking(true);
							ui->centralWidget->setMouseTracking(true);
							ui->ShowImage->setMouseTracking(true);
						}
						else
						{
							QMessageBox::information(this,
								tr("The input origin point is not valid."),
								tr("The input origin point is not valid."));
						}
					}
					else if(is_vanished == x_scale)
					{
						scale_pt = mod->findPointOnDirection(cv::Point2d(x, y), mod->Xv);
						ui->int_scale->setEnabled(true);
						ui->Vanish_Point->setEnabled(true);
					}
					else if(is_vanished == y_scale)
					{
						scale_pt = mod->findPointOnDirection(cv::Point2d(x, y), mod->Yv); 
						ui->int_scale->setEnabled(true);
						ui->Vanish_Point->setEnabled(true);
					}
					else if(is_vanished == z_scale)
					{
						scale_pt = mod->findPointOnDirection(cv::Point2d(x, y), mod->Zv); 
						ui->int_scale->setEnabled(true);
						ui->Vanish_Point->setEnabled(true);
					}
				}
				//flush the image
				draw_image();
			}
		}
		else if(e->button() == Qt::RightButton)
		{
			int x, y;
			if(click_position(e->x(), e->y(), x, y))
			{				
				if(is_texture)
				{
                    Vertex * nearest = mod->findNearestVertex(cv::Point2d(x,y));
                    //Vertex* nearest = store_vertex[polygon_vertex.size()];
					vector<Vertex *>::iterator iter= polygon_vertex.begin();
					while(iter != polygon_vertex.end())
					{
						if((*iter)->ID() == nearest->ID())
							break;
						iter ++;
					}

					if(iter == polygon_vertex.end())
					{
						//not in vector
						polygon_vertex.push_back(nearest);
					}

					//polygon_point.push_back(cv::Point2d(x,y));

					if(polygon_vertex.size() == 4)
					{
						//begin to generate the face
						 Face* tmp_face = mod->generateFace(polygon_vertex);
						 gen_face.push_back(tmp_face);
						 is_texture = false;
					}
				}
				else if(is_3d)
				{
					//add new point
					if(is_bottom)
					{
						//bottom is a existed point
						bottom.x = x;
						bottom.y = y;
						is_bottom = false;
						//store_vertex is the origin
						vbottom = mod->findNearestVertex(bottom);
						bottom.x = vbottom->Coor2d().x;
						bottom.y = vbottom->Coor2d().y;
					}
					else if(vtop == NULL)
					{
						top.x = x;
						top.y = y;
						vtop = mod->findNearestVertex(top);
						top.x = vtop->Coor2d().x;
						top.y = vtop->Coor2d().y;

						//Output the result
						QString info = "Bottom coordinate:\n";
						QString tmp;
						info += tmp.sprintf("(%f,%f,%f)\n", vbottom->Coor3d().x, vbottom->Coor3d().y, vbottom->Coor3d().z);
						info += "Top coordinate:\n";
						info += tmp.sprintf("(%f,%f,%f)", vtop->Coor3d().x, vtop->Coor3d().y, vtop->Coor3d().z);
						ui->infobox->setText(info);

						is_3d = false;
						is_bottom = true;
					}
				}

			}
			draw_image();
		}
	}
}
