#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_texture()
{
	//is_texture = true;
	Face* new_face ;
	if(!is_exist_texture)
		new_face = mod->generateFace(polygon_vertex);
	else
		new_face = gen_face;

	if(new_face == NULL)
	{
		//error		 
		QMessageBox::information(this,
                                     tr("Generate Face Error"),
                                     tr("Generate Face Error!"));
		is_exist_texture = false;
		polygon_vertex.clear();
		draw_image();
		return;
	}

	QString info = "Face ";
	QString tmp;
	info += tmp.sprintf("(id:%d) Info:\n",new_face->ID());

    //for(int i = 0; i<polygon_vertex.size(); i++)
    for(int i = 0; i<4; i++)
	{
		 Vertex* face_vertex = new_face->getVertex(i);
		 if(face_vertex != NULL)
			info += tmp.sprintf("Vertex:%d:(%.3f,%.3f,%.3f)\n", face_vertex->ID(), face_vertex->Coor3d().x, face_vertex->Coor3d().y, face_vertex->Coor3d().z);
         bool check=true;
         for(int j=0;j<store_vertex.size();j++)
             if(store_vertex[j]==face_vertex)
             {
                 check=false;
                 break;
             }
         if(check)
             store_vertex.push_back(face_vertex);
         draw_image();
	}

	ui->infobox->setText(info);

	is_exist_texture = false;
	polygon_vertex.clear();
	draw_image();

	show_texture* show = new show_texture();
	QImage img_tmp = (new_face->Texture());
	show->set_image(&img_tmp);
	show->show();
}
