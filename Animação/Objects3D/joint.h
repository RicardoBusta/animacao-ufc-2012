#ifndef JOINT_H
#define JOINT_H

#include "object3d.h"

class Joint : public Object3D
{
public:
    Joint(Object3D* children_object);

    void addChildJoint(Joint* child);

    int howManyChilds();
    Joint* childAt(int index);
    Object3D *childObject();


protected:
    virtual void drawObject();
    virtual void drawBoundingBox();
    virtual void drawBone();

private:
    Object3D* child_object_;
    std::vector<Joint*> children_joint_;

    Joint *parent_joint_;
};

#endif // JOINT_H
