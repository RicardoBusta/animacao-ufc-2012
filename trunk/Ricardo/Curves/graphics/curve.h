#ifndef CURVE_H
#define CURVE_H

#include <vector>

class Vector3f;

class Curve
{
public:
    Curve();
    ~Curve();

    std::vector<Vector3f*> points;

    void addPoint(Vector3f *point);
    void clear();

    void gl();
};

#endif // CURVE_H
