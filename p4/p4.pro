TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    maxflow.cpp \
    graph.cpp \
    pixel.cpp \
    mvm.cpp

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
    instances.inc
