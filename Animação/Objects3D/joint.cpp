#include "joint.h"

Joint::Joint(Object3D* children_object)
{
    children_object_ = children_object;
    is_joint_ = true;
}

void Joint::AddChildJoint(Joint* child) {
    children_joint_.push_back(child);
}

void Joint::DrawObject(bool animate_position, bool animate_orientation) {
    children_object_->Draw(animate_position,animate_orientation);

    for(size_t i = 0 ; i < children_joint_.size() ; i++ )
        children_joint_.at(i)->Draw(animate_position,animate_orientation);
}

void Joint::DrawTrajectory(bool animate_position, bool animate_orientation){
    for( uint i = 0; i < children_joint_.size(); i++ ){
        Joint *joint = children_joint_.at(i);
        joint->DrawTrajectory(animate_position,animate_orientation);
    }

    if(children_object_!=NULL){
        children_object_->DrawTrajectory(animate_position,animate_orientation);
    }
}
