/********************************************************************************
** Form generated from reading UI file 'scissor_diag.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCISSOR_DIAG_H
#define UI_SCISSOR_DIAG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_scissor_diag
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *sc_image_only;
    QPushButton *image_contour;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QPushButton *sc_OK;
    QPushButton *sc_cost_graph;
    QPushButton *sc_pixel_node;
    QPushButton *sc_min_path;
    QPushButton *sc_path_tree;

    void setupUi(QDialog *scissor_diag)
    {
        if (scissor_diag->objectName().isEmpty())
            scissor_diag->setObjectName(QStringLiteral("scissor_diag"));
        scissor_diag->resize(251, 338);
        label = new QLabel(scissor_diag);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(false);
        label->setGeometry(QRect(10, 10, 81, 31));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(scissor_diag);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setEnabled(false);
        label_2->setGeometry(QRect(10, 130, 91, 16));
        label_2->setFont(font);
        sc_image_only = new QPushButton(scissor_diag);
        sc_image_only->setObjectName(QStringLiteral("sc_image_only"));
        sc_image_only->setGeometry(QRect(10, 60, 91, 41));
        image_contour = new QPushButton(scissor_diag);
        image_contour->setObjectName(QStringLiteral("image_contour"));
        image_contour->setGeometry(QRect(120, 60, 91, 41));
        line = new QFrame(scissor_diag);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 40, 241, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(scissor_diag);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(0, 110, 251, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(scissor_diag);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(0, 250, 251, 16));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        sc_OK = new QPushButton(scissor_diag);
        sc_OK->setObjectName(QStringLiteral("sc_OK"));
        sc_OK->setGeometry(QRect(70, 280, 91, 41));
        sc_cost_graph = new QPushButton(scissor_diag);
        sc_cost_graph->setObjectName(QStringLiteral("sc_cost_graph"));
        sc_cost_graph->setGeometry(QRect(120, 160, 91, 41));
        sc_pixel_node = new QPushButton(scissor_diag);
        sc_pixel_node->setObjectName(QStringLiteral("sc_pixel_node"));
        sc_pixel_node->setGeometry(QRect(10, 160, 91, 41));
        sc_min_path = new QPushButton(scissor_diag);
        sc_min_path->setObjectName(QStringLiteral("sc_min_path"));
        sc_min_path->setGeometry(QRect(120, 210, 91, 41));
        sc_path_tree = new QPushButton(scissor_diag);
        sc_path_tree->setObjectName(QStringLiteral("sc_path_tree"));
        sc_path_tree->setGeometry(QRect(10, 210, 91, 41));

        retranslateUi(scissor_diag);
        QObject::connect(sc_OK, SIGNAL(clicked()), scissor_diag, SLOT(sc_OK()));
        QObject::connect(image_contour, SIGNAL(clicked()), scissor_diag, SLOT(sc_image_contour()));
        QObject::connect(sc_image_only, SIGNAL(clicked()), scissor_diag, SLOT(sc_image_only()));
        QObject::connect(sc_pixel_node, SIGNAL(clicked()), scissor_diag, SLOT(sc_pixel_node()));
        QObject::connect(sc_cost_graph, SIGNAL(clicked()), scissor_diag, SLOT(sc_cost_graph()));
        QObject::connect(sc_path_tree, SIGNAL(clicked()), scissor_diag, SLOT(sc_path_tree()));
        QObject::connect(sc_min_path, SIGNAL(clicked()), scissor_diag, SLOT(sc_min_path()));

        QMetaObject::connectSlotsByName(scissor_diag);
    } // setupUi

    void retranslateUi(QDialog *scissor_diag)
    {
        scissor_diag->setWindowTitle(QApplication::translate("scissor_diag", "Dialog", 0));
        label->setText(QApplication::translate("scissor_diag", "Work Mode:", 0));
        label_2->setText(QApplication::translate("scissor_diag", "Debug Mode:", 0));
        sc_image_only->setText(QApplication::translate("scissor_diag", "Image Only", 0));
        image_contour->setText(QApplication::translate("scissor_diag", "Image with \n"
" Contour", 0));
        sc_OK->setText(QApplication::translate("scissor_diag", "OK", 0));
        sc_cost_graph->setText(QApplication::translate("scissor_diag", "Cost Graph", 0));
        sc_pixel_node->setText(QApplication::translate("scissor_diag", "Pixel Nodes", 0));
        sc_min_path->setText(QApplication::translate("scissor_diag", "Minimum Path", 0));
        sc_path_tree->setText(QApplication::translate("scissor_diag", "Path Tree", 0));
    } // retranslateUi

};

namespace Ui {
    class scissor_diag: public Ui_scissor_diag {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCISSOR_DIAG_H
