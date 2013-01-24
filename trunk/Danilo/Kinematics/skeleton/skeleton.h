#ifndef SKELETON_H
#define SKELETON_H
#include "link.h"
#include "math/matrix4f.h"
class Skeleton
{
public:
    Skeleton();
};

class Joint : public Link
{
public:
    Joint(Link* children_object);

    void AddChildJoint(Joint* child);
    Matrix4f transform;
    Matrix4f transform_global;

    int HowManyChilds();
    Joint* ChildAt(int index);
    void setParent(Joint *parent);
    void DrawObject();
    Joint* getParent();
    Joint* getRoot();
    Vec4 getPositionAbsolute();
    Vec4 getPositionEffector();
    void setPositionAbsolute(Vec4 pos);
    void setPosition(Vec4 pos);

private:
    Link* children_object_;
    Joint* parent_;
    Vec4 posAbsolute;
    std::vector<Joint*> children_joint_;
};
#endif // SKELETON_H
