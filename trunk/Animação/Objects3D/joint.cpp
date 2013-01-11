#include "joint.h"

Joint::Joint(Object3D* child_object)
{
    if(child_object!=NULL){
        label_ = (child_object->label() + " Joint");
    }else{
        label_ = "Empty Joint";
    }
    child_object_ = child_object;
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
    child_object_->Draw();

    for(size_t i = 0 ; i < children_joint_.size() ; i++ )
        children_joint_.at(i)->Draw();
}


Object3D *Joint::ChildObject()
{
    return child_object_;
}
