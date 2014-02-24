#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
/*
* Draw the image on the label widget.
*/
void MainWindow::draw_image()
{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	//this->resize(img->width(), img->height());
    //ui->ShowImage->resize(img->width(), img->height());
	//ui->centralWidget->resize(img->width(), img->height());
    if(workstates ==image_only||workstates ==image_only_contour)
    {
        ui->ShowImage->resize(img->width(), img->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*img));
=======
=======
>>>>>>> 9bba361707a7b06d346d2c45679ca382bc54b6bb

=======
>>>>>>> 288329599a6db329418469ab0871736966e4671b
	if(workstates == image_only||workstates ==image_only_contour)
    {

		QImage * img_tmp;
		img_tmp = pimg;
		pimg = new QImage(pimg->scaled(img->width() * size, img->height() * size, Qt::KeepAspectRatio));
		delete img_tmp;
		
        ui->ShowImage->resize(pimg->width(), pimg->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
		ui->centralWidget->resize(pimg->width(), pimg->height());
		this->resize(pimg->width(), pimg->height());
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> 909e849172b2ab1b25e78db1e17fab014974d539
=======
=======
	//this->resize(img->width(), img->height());
    //ui->ShowImage->resize(img->width(), img->height());
	//ui->centralWidget->resize(img->width(), img->height());
    if(workstates ==image_only||workstates ==image_only_contour)
    {
        ui->ShowImage->resize(img->width(), img->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*img));
>>>>>>> 3636f17478f45c645b5db5a062bdf6bf2e58ede9
>>>>>>> 9bba361707a7b06d346d2c45679ca382bc54b6bb
    }
=======
	}
>>>>>>> 288329599a6db329418469ab0871736966e4671b
    else if(workstates ==cost_graph)
    {
        QImage cg=ics->drawCostGraph();
        ui->ShowImage->resize(cg.width(), cg.height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(cg));
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
		ui->centralWidget->resize(cg.width(), cg.height());
		this->resize(cg.width(), cg.height());
>>>>>>> 909e849172b2ab1b25e78db1e17fab014974d539
=======
		ui->centralWidget->resize(cg.width(), cg.height());
		this->resize(cg.width(), cg.height());
=======
>>>>>>> 3636f17478f45c645b5db5a062bdf6bf2e58ede9
>>>>>>> 9bba361707a7b06d346d2c45679ca382bc54b6bb
=======
		ui->centralWidget->resize(cg.width(), cg.height());
		this->resize(cg.width(), cg.height());
>>>>>>> 288329599a6db329418469ab0871736966e4671b
    }
    else if(workstates==path_tree)
    {
        QImage cg=ics->drawPathTree();
        ui->ShowImage->resize(cg.width(), cg.height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(cg));
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    }
}
=======
	this->resize(pimg->width(), pimg->height());
	ui->ShowImage->resize(pimg->width(), pimg->height());
	ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
	//ui->centralWidget->resize(img->width(), img->height());
}
>>>>>>> 8281ddbe12dc7237ab07fc602fd8cbdca6b6f23b
=======
=======
>>>>>>> 9bba361707a7b06d346d2c45679ca382bc54b6bb
=======
>>>>>>> 288329599a6db329418469ab0871736966e4671b
		ui->centralWidget->resize(cg.width(), cg.height());
		this->resize(cg.width(), cg.height());
    }

}

<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> 909e849172b2ab1b25e78db1e17fab014974d539
=======
=======
    }
}
>>>>>>> 3636f17478f45c645b5db5a062bdf6bf2e58ede9
>>>>>>> 9bba361707a7b06d346d2c45679ca382bc54b6bb
=======
>>>>>>> 288329599a6db329418469ab0871736966e4671b
