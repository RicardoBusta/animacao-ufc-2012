#ifndef CURVE_H
#define CURVE_H

#include <vector>

#include "math/pointcubicinterpolation.h"

class Vector3f;

class Curve
{
public:
    PointCubicInterpolation interp;

    Curve();
    ~Curve();

    std::vector<Vector3f*> controlPoints;
    std::vector<Vector3f*> calculatedPoints;

    Matrix4f *transform;

    void addPoint(Vector3f *point);
    void clear();

    void calculateCurve();

    void glControlPoints();
    void glCalculatedPoints();
    void glCurve();
    void glControlLine();
};

#endif // CURVE_H
