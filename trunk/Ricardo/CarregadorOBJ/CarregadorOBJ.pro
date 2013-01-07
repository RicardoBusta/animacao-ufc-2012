#-------------------------------------------------
#
# Project created by QtCreator 2013-01-06T17:35:39
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CarregadorOBJ
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glframe.cpp \
    glwidget.cpp \
    scene.cpp \
    fileobj.cpp

HEADERS  += mainwindow.h \
    glframe.h \
    glwidget.h \
    scene.h \
    fileobj.h

FORMS    += mainwindow.ui
