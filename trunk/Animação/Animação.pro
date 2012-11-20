#-------------------------------------------------
#
# Project created by QtCreator 2012-11-20T14:48:34
#
#-------------------------------------------------

QT       += core gui xml opengl

TARGET = Animação
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


unix:!macx:!symbian: LIBS += -L$$PWD/../../workspace/libQGLViewer-2.3.17/QGLViewer/ -lQGLViewer

INCLUDEPATH += $$PWD/../../workspace/libQGLViewer-2.3.17/QGLViewer
DEPENDPATH += $$PWD/../../workspace/libQGLViewer-2.3.17/QGLViewer

LIBS += -lGLU
