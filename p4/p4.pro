TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    maxflow.cpp \
    graph.cpp \
    pixel.cpp \
    mvm.cpp \
    svdcmp.cpp \
    stdafx.cpp \
    normal_func.cpp

OPENCVENABLE = 1
!include(QTFlagsOpenCV.pri) {
    error("Cannot include QTFlagsOpenCV.pri")
}

OTHER_FILES += \
    QTFlagsOpenCV.pri \
    libraryDetector.pri

HEADERS += \
    sampling.h \
    define.h \
    graph.h \
    block.h \
    pixel.h \
    mvm.h \
    instances.inc \
    svdcmp.h \
    stdafx.h \
    normal_class.h
