#ifndef CURVEOJECT_H
#define CURVEOJECT_H

#include "object3d.h"

class Curve;

class CurveObject : public Object3D
{
public:
    CurveObject(Curve* cuve);

private:
    void DrawObject(bool animate_position = true, bool animate_orientation = true);
    Curve* curve_;
};

#endif // CURVEOJECT_H
