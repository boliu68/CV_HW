/********************************************************************************
** Form generated from reading UI file 'show_texture.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOW_TEXTURE_H
#define UI_SHOW_TEXTURE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_show_texture
{
public:
    QLabel *show;

    void setupUi(QDialog *show_texture)
    {
        if (show_texture->objectName().isEmpty())
            show_texture->setObjectName(QStringLiteral("show_texture"));
        show_texture->resize(400, 300);
        show = new QLabel(show_texture);
        show->setObjectName(QStringLiteral("show"));
        show->setGeometry(QRect(10, 10, 371, 271));

        retranslateUi(show_texture);

        QMetaObject::connectSlotsByName(show_texture);
    } // setupUi

    void retranslateUi(QDialog *show_texture)
    {
        show_texture->setWindowTitle(QApplication::translate("show_texture", "Dialog", 0));
        show->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class show_texture: public Ui_show_texture {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOW_TEXTURE_H
