#-------------------------------------------------
#
# Project created by QtCreator 2012-11-12T23:37:41
#
#-------------------------------------------------

CONFIG  += qt opengl warn_on release thread openmp #debug
QT *= xml opengl
QT += core gui


INCLUDEPATH += D:/libQGLViewer/
LIBS *= -LD:/libQGLViewer/ -lQGLViewer2


TARGET = AnimationStudio
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    viewer.cpp \
    arclength.cpp \
    posinterpolator.cpp \
    oriinterpolator.cpp \
    scenecontainer.cpp \
    joint.cpp \
    object3d.cpp \
    interpolator.cpp \
    timebar.cpp

HEADERS  += mainwindow.h \
    viewer.h \
    arclength.h \
    posinterpolator.h \
    oriinterpolator.h \
    animation_step.h \
    curve.h \
    scenecontainer.h \
    joint.h \
    object3d.h \
    interpolator.h \
    timebar.h

FORMS    += mainwindow.ui

exists( /usr/lib/libQGLViewer.so ) {
LIBS *= -lqglviewer-qt4
}

