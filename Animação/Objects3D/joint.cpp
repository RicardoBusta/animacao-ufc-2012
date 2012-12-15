#include "joint.h"

Joint::Joint(Object3D* children_object)
{
    children_object_ = children_object;
}

void Joint::AddChildJoint(Joint* child) {
    children_joint_.push_back(child);
}

void Joint::DrawObject() {
    children_object_->Draw();

    for(size_t i = 0 ; i < children_joint_.size() ; i++ )
        children_joint_.at(i)->Draw();
}
