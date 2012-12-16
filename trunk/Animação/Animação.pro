#-------------------------------------------------
#
# Project created by QtCreator 2012-11-20T14:48:34
#
#-------------------------------------------------

QT       += core gui xml opengl

TARGET = Animação
TEMPLATE = app

#DEFINES += DEBUG_TEXT

HEADERS += \
    Curves/curve.h \
    Curves/arclength.h \
    Interpolation/quaternioninterpolation.h \
    Interpolation/posinterpolator.h \
    Interpolation/oriinterpolator.h \
    Interpolation/objectanimator.h \
    Interpolation/interpolator.h \
    Interpolation/animation_step.h \
    Objects3D/trajectoryobject.h \
    Objects3D/spaceshipobject.h \
    Objects3D/object3d.h \
    Objects3D/joint.h \
    Objects3D/curveobject.h \
    Utils/scenecontainer.h \
    Widgets/viewer.h \
    Widgets/timebar.h \
    mainwindow.h \
    Objects3D/objectinfotree.h

SOURCES += \
    Curves/arclength.cpp \
    Interpolation/quaternioninterpolation.cpp \
    Interpolation/posinterpolator.cpp \
    Interpolation/oriinterpolator.cpp \
    Interpolation/objectanimator.cpp \
    Interpolation/interpolator.cpp \
    Objects3D/trajectoryobject.cpp \
    Objects3D/spaceshipobject.cpp \
    Objects3D/object3d.cpp \
    Objects3D/joint.cpp \
    Objects3D/curveobject.cpp \
    Utils/scenecontainer.cpp \
    Widgets/viewer.cpp \
    Widgets/timebar.cpp \
    main.cpp \
    mainwindow.cpp \
    Objects3D/objectinfotree.cpp



unix:!macx: LIBS += -L$$PWD/../../../../../../usr/lib/x86_64-linux-gnu/ -lqglviewer-qt4

INCLUDEPATH += $$PWD/../../../../../../usr/include/QGLViewer
DEPENDPATH += $$PWD/../../../../../../usr/include/QGLViewer

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../../usr/lib/x86_64-linux-gnu/libqglviewer-qt4.a

FORMS += \
    mainwindow.ui
