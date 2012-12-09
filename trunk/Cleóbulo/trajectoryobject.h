#ifndef TRAJECTORYOBJECT_H
#define TRAJECTORYOBJECT_H

#include "object3d.h"

class ObjectAnimator;

class TrajectoryObject : public Object3D
{
public:
    TrajectoryObject(ObjectAnimator* animator);

    void Update();
    void Update(int start_frame, int end_frame);

private:
    void DrawObject();

    std::vector<qglviewer::Vec> positions_;
    ObjectAnimator* animator_;
};

#endif // TRAJECTORYOBJECT_H
