#ifndef ANIMATION_STEP_H
#define ANIMATION_STEP_H

#include <QGLViewer/vec.h>
#include <QGLViewer/quaternion.h>

class PositionStep {
public:
    PositionStep(){}

    PositionStep(qglviewer::Vec pos, int frame) :
        position_(pos), frame_(frame){
    }

    qglviewer::Vec position_;
    int frame_;
};

class OrientationStep {
public:
    OrientationStep(){}

    OrientationStep(qglviewer::Quaternion ori, int frame) :
        orientation_(ori), frame_(frame){
    }

    qglviewer::Quaternion orientation_;
    int frame_;
};

#endif // ANIMATION_STEP_H
