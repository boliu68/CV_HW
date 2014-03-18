/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *Load_Image;
    QWidget *centralWidget;
    QLabel *ShowImage;
    QFrame *line;
    QPushButton *Vanish_Point;
    QLabel *infobox;
    QPlainTextEdit *int_scale;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(761, 539);
        Load_Image = new QAction(MainWindow);
        Load_Image->setObjectName(QStringLiteral("Load_Image"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ShowImage = new QLabel(centralWidget);
        ShowImage->setObjectName(QStringLiteral("ShowImage"));
        ShowImage->setGeometry(QRect(10, 0, 381, 491));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(470, 0, 16, 501));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        Vanish_Point = new QPushButton(centralWidget);
        Vanish_Point->setObjectName(QStringLiteral("Vanish_Point"));
        Vanish_Point->setEnabled(true);
        Vanish_Point->setGeometry(QRect(490, 30, 75, 23));
        infobox = new QLabel(centralWidget);
        infobox->setObjectName(QStringLiteral("infobox"));
        infobox->setGeometry(QRect(490, 270, 250, 200));
        QFont font;
        font.setFamily(QStringLiteral("Courier"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        infobox->setFont(font);
        infobox->setWordWrap(true);
        int_scale = new QPlainTextEdit(centralWidget);
        int_scale->setObjectName(QStringLiteral("int_scale"));
        int_scale->setEnabled(false);
        int_scale->setGeometry(QRect(590, 30, 104, 31));
        QFont font1;
        font1.setItalic(true);
        int_scale->setFont(font1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 761, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(Load_Image);

        retranslateUi(MainWindow);
        QObject::connect(Load_Image, SIGNAL(triggered()), MainWindow, SLOT(onLoadImage()));
        QObject::connect(Vanish_Point, SIGNAL(clicked()), MainWindow, SLOT(on_vanish()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        Load_Image->setText(QApplication::translate("MainWindow", "Load Image", 0));
        ShowImage->setText(QString());
        Vanish_Point->setText(QApplication::translate("MainWindow", "X axis", 0));
        infobox->setText(QApplication::translate("MainWindow", "Welcome!", 0));
        int_scale->setPlainText(QApplication::translate("MainWindow", "Insert Scale", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
