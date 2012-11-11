#-------------------------------------------------
#
# Project created by QtCreator 2012-10-10T14:13:26
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = Curves
TEMPLATE = app

DEFINES += \
    #SHADERS_ENABLED

SOURCES += \
    main.cpp \
    interface/mainwindow.cpp \
    graphics/material.cpp \
    graphics/glwidget.cpp \
    graphics/glprimitive.cpp \
    graphics/camera.cpp \
    math/vector3f.cpp \
    math/matrix4f.cpp \
    scene/scene.cpp \
    interface/glframe.cpp \
    graphics/glvectorfunctions.cpp \
    graphics/glmathelements.cpp \
    graphics/curve.cpp

HEADERS  += \
    interface/mainwindow.h \
    graphics/material.h \
    graphics/glwidget.h \
    graphics/glprimitive.h \
    graphics/camera.h \
    math/vector3f.h \
    math/matrix4f.h \
    scene/scene.h \
    interface/glframe.h \
    graphics/glvectorfunctions.h \
    graphics/glmathelements.h \
    graphics/curve.h

FORMS    += \
        interface/mainwindow.ui

RESOURCES +=
