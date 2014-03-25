#include "show_texture.h"
#include "ui_show_texture.h"

show_texture::show_texture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::show_texture)
{
    ui->setupUi(this);
}

show_texture::~show_texture()
{
    delete ui;
}

void show_texture::set_image(QImage* img)
{
	texture = img;
	//int w = img->width(), h = img->height();
	//ui->show->move(0,0);
	this->resize(img->width(), img->height());
	ui->show->resize(img->width(), img->height());
	ui->show->setPixmap(QPixmap::fromImage(*texture));
}