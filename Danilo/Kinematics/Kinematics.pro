#-------------------------------------------------
#
# Project created by QtCreator 2012-10-13T16:17:40
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = Curves
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    interface/glwidget.cpp \
    skeleton/skeleton.cpp \
    math/vec4.cpp \
    math/matrix4x4.cpp \
    skeleton/link.cpp \
    math/quaternion.cpp \
    simple/simpledraw.cpp \
    math/matrix4f.cpp \
    math/iksolve.cpp \


HEADERS  += mainwindow.h \
    interface/glwidget.h \
    skeleton/skeleton.h \
    math/vec4.h \
    math/matrix4x4.h \
    skeleton/link.h \
    math/quaternion.h \
    simple/simpledraw.h \
    math/matrix4f.h \
    math/iksolve.h \


FORMS    += mainwindow.ui
