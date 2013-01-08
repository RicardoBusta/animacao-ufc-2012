#ifndef TORUS_H
#define TORUS_H

#include "Objects3D/object3d.h"
#include <vector>

class Slice {
public:
    explicit Slice(double radius, qglviewer::Vec original_point, qglviewer::Vec axis, int steps);

    qglviewer::Vec Step(int index);

private:
    void CreateSlice();

    int steps_;
    double radius_;
    qglviewer::Vec axis_;
    qglviewer::Vec original_point_;
    std::vector<qglviewer::Vec> slice_;
};

class Torus : public Object3D
{
public:
    explicit Torus(double inner_radius, double outer_radius, int slices, int steps);
    
private:
    int slices_, steps_;
    double inner_radius_;
    double outer_radius_;
    std::vector<Slice> torus_slices_;

    void CreateSlices();
    void DrawObject();
    
};

#endif // TORUS_H
