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
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *Load_Image;
    QAction *savecfg;
    QAction *loadcfg;
    QWidget *centralWidget;
    QLabel *ShowImage;
    QFrame *line;
    QPushButton *Vanish_Point;
    QLabel *infobox;
    QPlainTextEdit *int_scale;
    QPushButton *vrml;
    QPushButton *quit;
    QRadioButton *cal_bot;
    QRadioButton *cal_top;
    QRadioButton *cal_face;
    QPushButton *texture2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(828, 539);
        Load_Image = new QAction(MainWindow);
        Load_Image->setObjectName(QStringLiteral("Load_Image"));
        savecfg = new QAction(MainWindow);
        savecfg->setObjectName(QStringLiteral("savecfg"));
        savecfg->setEnabled(false);
        loadcfg = new QAction(MainWindow);
        loadcfg->setObjectName(QStringLiteral("loadcfg"));
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
        infobox->setGeometry(QRect(490, 170, 321, 311));
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
        int_scale->setGeometry(QRect(620, 20, 104, 31));
        QFont font1;
        font1.setItalic(true);
        int_scale->setFont(font1);
        vrml = new QPushButton(centralWidget);
        vrml->setObjectName(QStringLiteral("vrml"));
        vrml->setEnabled(false);
        vrml->setGeometry(QRect(490, 180, 75, 23));
        quit = new QPushButton(centralWidget);
        quit->setObjectName(QStringLiteral("quit"));
        quit->setEnabled(true);
        quit->setGeometry(QRect(640, 180, 75, 23));
        cal_bot = new QRadioButton(centralWidget);
        cal_bot->setObjectName(QStringLiteral("cal_bot"));
        cal_bot->setEnabled(false);
        cal_bot->setGeometry(QRect(490, 80, 131, 16));
        cal_top = new QRadioButton(centralWidget);
        cal_top->setObjectName(QStringLiteral("cal_top"));
        cal_top->setEnabled(false);
        cal_top->setGeometry(QRect(490, 110, 121, 16));
        cal_face = new QRadioButton(centralWidget);
        cal_face->setObjectName(QStringLiteral("cal_face"));
        cal_face->setEnabled(false);
        cal_face->setGeometry(QRect(490, 140, 101, 16));
        texture2 = new QPushButton(centralWidget);
        texture2->setObjectName(QStringLiteral("texture2"));
        texture2->setEnabled(false);
        texture2->setGeometry(QRect(630, 100, 91, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 828, 21));
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
        menuFile->addSeparator();
        menuFile->addAction(savecfg);
        menuFile->addAction(loadcfg);

        retranslateUi(MainWindow);
        QObject::connect(Load_Image, SIGNAL(triggered()), MainWindow, SLOT(onLoadImage()));
        QObject::connect(Vanish_Point, SIGNAL(clicked()), MainWindow, SLOT(on_vanish()));
        QObject::connect(vrml, SIGNAL(clicked()), MainWindow, SLOT(on_vrml()));
        QObject::connect(quit, SIGNAL(clicked()), MainWindow, SLOT(close()));
        QObject::connect(cal_bot, SIGNAL(clicked()), MainWindow, SLOT(on_bot()));
        QObject::connect(cal_top, SIGNAL(clicked()), MainWindow, SLOT(on_top()));
        QObject::connect(cal_face, SIGNAL(clicked()), MainWindow, SLOT(on_face()));
        QObject::connect(texture2, SIGNAL(clicked()), MainWindow, SLOT(on_texture()));
        QObject::connect(savecfg, SIGNAL(triggered()), MainWindow, SLOT(save_config()));
        QObject::connect(loadcfg, SIGNAL(triggered()), MainWindow, SLOT(load_config()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        Load_Image->setText(QApplication::translate("MainWindow", "Load Image", 0));
        savecfg->setText(QApplication::translate("MainWindow", "Save Config", 0));
        loadcfg->setText(QApplication::translate("MainWindow", "Load Config", 0));
        ShowImage->setText(QString());
        Vanish_Point->setText(QApplication::translate("MainWindow", "X axis", 0));
        infobox->setText(QApplication::translate("MainWindow", "Welcome!", 0));
        int_scale->setPlainText(QString());
        vrml->setText(QApplication::translate("MainWindow", "VRML", 0));
        quit->setText(QApplication::translate("MainWindow", "Quit", 0));
        cal_bot->setText(QApplication::translate("MainWindow", "Calculate Bottom", 0));
        cal_top->setText(QApplication::translate("MainWindow", "Calculate Top", 0));
        cal_face->setText(QApplication::translate("MainWindow", "Choose Face", 0));
        texture2->setText(QApplication::translate("MainWindow", "Calculate \n"
"Texture", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
