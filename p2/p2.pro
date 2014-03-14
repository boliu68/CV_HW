#-------------------------------------------------
#
# Project created by QtCreator 2014-03-14T10:53:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = p2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    singleviewmodel.cpp

HEADERS  += mainwindow.h \
    singleviewmodel.h

FORMS    += mainwindow.ui

OPENCVENABLE = 1
!include(QTFlagsOpenCV.pri) {
    error("Cannot include QTFlagsOpenCV.pri")
}

OTHER_FILES += \
    QTFlagsOpenCV.pri \
    libraryDetector.pri
