#-------------------------------------------------
#
# Project created by QtCreator 2012-11-20T14:48:34
#
#-------------------------------------------------

QT       += core gui xml opengl

TARGET = Animação
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glviewer.cpp

HEADERS  += mainwindow.h \
    glviewer.h

FORMS    += mainwindow.ui



unix:!macx: LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/ -lqglviewer-qt4

INCLUDEPATH += $$PWD/../../../../usr/include/QGLViewer
DEPENDPATH += $$PWD/../../../../usr/include/QGLViewer

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../usr/lib/x86_64-linux-gnu/libqglviewer-qt4.a
