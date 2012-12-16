#ifndef JOINT_H
#define JOINT_H

#include "object3d.h"

class Joint : public Object3D
{
public:
    Joint(Object3D* children_object);

    void AddChildJoint(Joint* child);

    virtual void DrawTrajectory();

protected:
    virtual void DrawObject(bool animate_position, bool animate_orientation);

private:
    Object3D* children_object_;
    std::vector<Joint*> children_joint_;
};

#endif // JOINT_H
