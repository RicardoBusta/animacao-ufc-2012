#ifndef JOINT_H
#define JOINT_H

#include "object3d.h"

class Joint : public Object3D
{
public:
    Joint(Object3D* children_object);

    void AddChildJoint(Joint* child);

    int HowManyChilds();
    Joint* ChildAt(int index);
    Object3D *ChildObject();


protected:
    virtual void DrawObject();

private:
    Object3D* child_object_;
    std::vector<Joint*> children_joint_;
};

#endif // JOINT_H
