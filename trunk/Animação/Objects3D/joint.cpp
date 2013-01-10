#include "joint.h"

Joint::Joint(Object3D* children_object)
{
    label_ = "Untitled";
    children_object_ = children_object;
}

void Joint::AddChildJoint(Joint* child) {
    children_joint_.push_back(child);
}

int Joint::HowManyChilds() {
    return children_joint_.size();

}

Joint* Joint::ChildAt(int index) {
    return children_joint_.at(index);
}

void Joint::DrawObject() {
    children_object_->Draw();

    for(size_t i = 0 ; i < children_joint_.size() ; i++ )
        children_joint_.at(i)->Draw();
}

