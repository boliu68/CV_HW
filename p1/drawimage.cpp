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
        ui->ShowImage->resize(pimg->width(), pimg->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
<<<<<<< HEAD
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
=======
		ui->centralWidget->resize(pimg->width() + 50, pimg->height() + 50);
		this->resize(pimg->width() + 50, pimg->height() + 50);
	}
	else if(workstates == pixel_node)
	{
		QImage pn=ics->drawPixelNode();
		delete pimg;
		pimg = new QImage(pn.scaled(pn.width() * size, pn.height() * size));
        ui->ShowImage->resize(pimg->width(), pimg->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
		ui->centralWidget->resize(pimg->width() + 50, pimg->height() + 50);
		this->resize(pimg->width() + 50, pimg->height() + 50);
>>>>>>> bbd39c6fcbf5b20e7815e28bb07fd623dea7770c
	}
>>>>>>> 288329599a6db329418469ab0871736966e4671b
    else if(workstates ==cost_graph)
    {
        QImage cg=ics->drawCostGraph();
<<<<<<< HEAD
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
<<<<<<< HEAD
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
=======
        ui->ShowImage->resize(pathtree->width(), pathtree->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*pathtree));
		ui->centralWidget->resize(pathtree->width(), pathtree->height());
		this->resize(pathtree->width(), pathtree->height());
>>>>>>> f61be8bfd49c90353c47466843719ef968cf0a62
=======
		delete pimg;
		pimg = new QImage(cg.scaled(cg.width() * size, cg.height() * size));
        ui->ShowImage->resize(pimg->width(), pimg->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
		ui->centralWidget->resize(pimg->width() + 50, pimg->height() + 50);
		this->resize(pimg->width() + 50, pimg->height() + 50);
    }
    else if(workstates==path_tree)
    {
		delete pimg;
		pimg = new QImage(pathtree->scaled(pathtree->width() * size, pathtree->height() * size));
        ui->ShowImage->resize(pimg->width(), pimg->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
		ui->centralWidget->resize(pimg->width() + 50, pimg->height() + 50);
		this->resize(pimg->width() + 50, pimg->height() + 50);
>>>>>>> bbd39c6fcbf5b20e7815e28bb07fd623dea7770c
    }
	else if(workstates == min_path)
	{
        ui->ShowImage->resize(pimg->width(), pimg->height());
        ui->ShowImage->setPixmap(QPixmap::fromImage(*pimg));
		ui->centralWidget->resize(pimg->width() + 50, pimg->height() + 50);
		this->resize(pimg->width() + 50, pimg->height() + 50);
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
