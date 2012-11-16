#ifndef POINTCUBICINTERPOLATION_H
#define POINTCUBICINTERPOLATION_H

#include "vector3f.h"

class PointCubicInterpolation
{
public:
    PointCubicInterpolation();

    float M_Bezier[4][4];
    float M_Hermite[4][4];
    float C[4][3];

    void setControlPoints(Vector3f p0, Vector3f p1, Vector3f p2, Vector3f p3);

    Vector3f getPoint(float t);
};

#endif // POINTCUBICINTERPOLATION_H
