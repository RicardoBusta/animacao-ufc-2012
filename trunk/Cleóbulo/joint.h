#ifndef JOINT_H
#define JOINT_H

#include "object3d.h"

class Joint : public Object3D
{
public:
    Joint();

protected:
    virtual void DrawObject();

private:
    Object3D* children_object_;
    std::vector<Joint*> children_joint_;
};

#endif // JOINT_H
