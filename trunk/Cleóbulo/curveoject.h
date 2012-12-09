#ifndef CURVEOJECT_H
#define CURVEOJECT_H

#include "object3d.h"

class Curve;

class CurveOject : public Object3D
{
public:
    CurveOject(Curve* cuve);

private:
    void DrawObject();
    Curve* curve_;
};

#endif // CURVEOJECT_H
