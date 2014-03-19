#ifndef SHOW_TEXTURE_H
#define SHOW_TEXTURE_H

#include <QDialog>

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QPixmap>
#include <qevent.h>
#include <QPainter>
#include <vector>
#include <QColor>
#include <qthread.h>
#include "states.h"
#include <QFont>
#include <QRegExp>
#include <singleviewmodel.h>

namespace Ui {
class show_texture;
}

class show_texture : public QDialog
{
    Q_OBJECT

private:
	QImage* texture;

public:
    explicit show_texture(QWidget *parent = 0);
    ~show_texture();
	void set_image(QImage*);


private:
    Ui::show_texture *ui;
};

#endif // SHOW_TEXTURE_H
