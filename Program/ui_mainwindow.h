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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *SaveContour;
    QAction *SaveMask;
    QAction *actionWork_Mode;
    QAction *actionDebug_Mode;
    QAction *ImageOnly;
    QAction *actionWork_Mode_2;
    QAction *ImageContour;
    QAction *actionDebug_Mode_2;
    QAction *PixelNode;
    QAction *CostGraph;
    QAction *PathTree;
    QAction *MinPath;
    QAction *QuitButton;
    QAction *LoadImage;
    QAction *Load_Image;
    QAction *scissor;
    QAction *brush;
    QWidget *centralWidget;
    QLabel *ShowImage;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTool;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(463, 576);
        QFont font;
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        MainWindow->setFont(font);
        SaveContour = new QAction(MainWindow);
        SaveContour->setObjectName(QStringLiteral("SaveContour"));
        QFont font1;
        font1.setFamily(QStringLiteral("Times New Roman"));
        font1.setPointSize(13);
        SaveContour->setFont(font1);
        SaveMask = new QAction(MainWindow);
        SaveMask->setObjectName(QStringLiteral("SaveMask"));
        SaveMask->setFont(font1);
        actionWork_Mode = new QAction(MainWindow);
        actionWork_Mode->setObjectName(QStringLiteral("actionWork_Mode"));
        actionDebug_Mode = new QAction(MainWindow);
        actionDebug_Mode->setObjectName(QStringLiteral("actionDebug_Mode"));
        ImageOnly = new QAction(MainWindow);
        ImageOnly->setObjectName(QStringLiteral("ImageOnly"));
        actionWork_Mode_2 = new QAction(MainWindow);
        actionWork_Mode_2->setObjectName(QStringLiteral("actionWork_Mode_2"));
        actionWork_Mode_2->setCheckable(false);
        actionWork_Mode_2->setEnabled(false);
        ImageContour = new QAction(MainWindow);
        ImageContour->setObjectName(QStringLiteral("ImageContour"));
        actionDebug_Mode_2 = new QAction(MainWindow);
        actionDebug_Mode_2->setObjectName(QStringLiteral("actionDebug_Mode_2"));
        actionDebug_Mode_2->setEnabled(false);
        PixelNode = new QAction(MainWindow);
        PixelNode->setObjectName(QStringLiteral("PixelNode"));
        CostGraph = new QAction(MainWindow);
        CostGraph->setObjectName(QStringLiteral("CostGraph"));
        PathTree = new QAction(MainWindow);
        PathTree->setObjectName(QStringLiteral("PathTree"));
        MinPath = new QAction(MainWindow);
        MinPath->setObjectName(QStringLiteral("MinPath"));
        QuitButton = new QAction(MainWindow);
        QuitButton->setObjectName(QStringLiteral("QuitButton"));
        QuitButton->setFont(font1);
        LoadImage = new QAction(MainWindow);
        LoadImage->setObjectName(QStringLiteral("LoadImage"));
        Load_Image = new QAction(MainWindow);
        Load_Image->setObjectName(QStringLiteral("Load_Image"));
        QFont font2;
        font2.setFamily(QStringLiteral("Times New Roman"));
        font2.setPointSize(13);
        font2.setUnderline(false);
        Load_Image->setFont(font2);
        scissor = new QAction(MainWindow);
        scissor->setObjectName(QStringLiteral("scissor"));
        scissor->setFont(font1);
        brush = new QAction(MainWindow);
        brush->setObjectName(QStringLiteral("brush"));
        brush->setFont(font1);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        ShowImage = new QLabel(centralWidget);
        ShowImage->setObjectName(QStringLiteral("ShowImage"));
        ShowImage->setEnabled(true);
        ShowImage->setGeometry(QRect(0, 0, 500, 500));
        QFont font3;
        font3.setFamily(QStringLiteral("Arial"));
        font3.setPointSize(15);
        ShowImage->setFont(font3);
        ShowImage->setFocusPolicy(Qt::ClickFocus);
        ShowImage->setAcceptDrops(true);
        ShowImage->setScaledContents(false);
        ShowImage->setIndent(0);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 463, 29));
        QFont font4;
        font4.setFamily(QStringLiteral("Consolas"));
        font4.setPointSize(15);
        font4.setUnderline(true);
        menuBar->setFont(font4);
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuFile->setGeometry(QRect(152, 108, 153, 160));
        QFont font5;
        font5.setUnderline(false);
        menuFile->setFont(font5);
        menuTool = new QMenu(menuBar);
        menuTool->setObjectName(QStringLiteral("menuTool"));
        menuTool->setGeometry(QRect(212, 108, 120, 73));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTool->menuAction());
        menuFile->addAction(Load_Image);
        menuFile->addSeparator();
        menuFile->addAction(SaveContour);
        menuFile->addAction(SaveMask);
        menuFile->addSeparator();
        menuFile->addAction(QuitButton);
        menuTool->addAction(scissor);

        retranslateUi(MainWindow);
        QObject::connect(Load_Image, SIGNAL(triggered()), MainWindow, SLOT(OpenImage()));
        QObject::connect(SaveContour, SIGNAL(triggered()), MainWindow, SLOT(save_contour()));
        QObject::connect(SaveMask, SIGNAL(triggered()), MainWindow, SLOT(save_mask()));
        QObject::connect(scissor, SIGNAL(triggered()), MainWindow, SLOT(on_scissor()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", " Intelligent Scissor Runze Zhang & Bo Liu", 0));
        SaveContour->setText(QApplication::translate("MainWindow", "Save Contour", 0));
        SaveMask->setText(QApplication::translate("MainWindow", "Save Mask", 0));
        actionWork_Mode->setText(QApplication::translate("MainWindow", "Work Mode", 0));
        actionDebug_Mode->setText(QApplication::translate("MainWindow", "Debug Mode", 0));
        ImageOnly->setText(QApplication::translate("MainWindow", "Image Only", 0));
        actionWork_Mode_2->setText(QApplication::translate("MainWindow", "Work Mode", 0));
        ImageContour->setText(QApplication::translate("MainWindow", "Image with Contour", 0));
        actionDebug_Mode_2->setText(QApplication::translate("MainWindow", "Debug Mode", 0));
        PixelNode->setText(QApplication::translate("MainWindow", "Pixel Node", 0));
        CostGraph->setText(QApplication::translate("MainWindow", "Cost Graph", 0));
        PathTree->setText(QApplication::translate("MainWindow", "Path Tree", 0));
        MinPath->setText(QApplication::translate("MainWindow", "Min Path", 0));
        QuitButton->setText(QApplication::translate("MainWindow", "Quit", 0));
        LoadImage->setText(QApplication::translate("MainWindow", "Load Image", 0));
        Load_Image->setText(QApplication::translate("MainWindow", "Load Image", 0));
        scissor->setText(QApplication::translate("MainWindow", "Scissor", 0));
        brush->setText(QApplication::translate("MainWindow", "Brush", 0));
        ShowImage->setText(QString());
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuTool->setTitle(QApplication::translate("MainWindow", "Tool", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
