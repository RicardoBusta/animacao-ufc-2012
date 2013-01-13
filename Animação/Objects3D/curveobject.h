#ifndef CURVEOJECT_H
#define CURVEOJECT_H

#include "object3d.h"

class Curve;

class CurveObject : public Object3D
{
public:
    CurveObject(Curve* cuve);

private:
    void DrawObject(bool);
    Curve* curve_;
};

#endif // CURVEOJECT_H
