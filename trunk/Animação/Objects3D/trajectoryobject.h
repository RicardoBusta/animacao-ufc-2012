#ifndef TRAJECTORYOBJECT_H
#define TRAJECTORYOBJECT_H

#include "object3d.h"
#include <GL/glu.h>

class ObjectAnimator;

class TrajectoryObject : public Object3D
{
public:
    enum TrajectoryType {kPosition,kOrientation,kBoth};
    TrajectoryObject(ObjectAnimator* animator);
    virtual ~TrajectoryObject();

    void update();
    void update(int start_frame, int end_frame);

    void setType(TrajectoryType type);

private:
    void drawObject();

    void drawPositionsCurve();

    TrajectoryType type_;
    std::vector<qglviewer::Vec> positions_;
    std::vector<qglviewer::Vec> keyframes_;
    ObjectAnimator* animator_;
    GLUquadric* quadric_;
    double radius_;
};

#endif // TRAJECTORYOBJECT_H
