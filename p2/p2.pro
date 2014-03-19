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
    singleviewmodel.cpp \
    utils.cpp \
    texture.cpp \
    on_vanish.cpp \
    move.cpp \
    loadimage.cpp \
    keyboard.cpp \
    draw_img.cpp \
    click.cpp \
    3d.cpp \
    show_texture.cpp

HEADERS  += mainwindow.h \
    singleviewmodel.h \
    helper.h \
    states.h \
    show_texture.h

FORMS    += mainwindow.ui \
    show_texture.ui

OPENCVENABLE = 1
!include(QTFlagsOpenCV.pri) {
    error("Cannot include QTFlagsOpenCV.pri")
}

OTHER_FILES += \
    QTFlagsOpenCV.pri \
    libraryDetector.pri
