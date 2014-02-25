#-------------------------------------------------
#
# Project created by QtCreator 2014-02-14T16:07:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CV_HW
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    iscissor.cpp \
    fibheap.cpp \
    binheap.cpp \
    OpenImage.cpp \
    drawimage.cpp \
    utils.cpp \
    scissor_diag.cpp \
    scissor_configure.cpp \
    sc_ok.cpp \
    savefile.cpp \
    Mouse.cpp \
    Keyboard.cpp \
    imageonly.cpp \
    debugmode.cpp

HEADERS  += mainwindow.h \
    iscissor.h \
    fibheap.h \
    binheap.h \
    helper.h \
    workstates.h \
    scissor_diag.h \
    helper.h
FORMS    += mainwindow.ui \
    scissor_diag.ui \
    scissor_config.ui

OPENCVENABLE = 1
!include(QTFlagsOpenCV.pri) {
    error("Cannot include QTFlagsOpenCV.pri")
}

OTHER_FILES += \
    libraryDetector.pri
