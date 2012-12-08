#include "joint.h"

Joint::Joint()
{
}

void Joint::DrawObject() {
    children_object_->Draw();

    for(size_t i = 0 ; i < children_joint_.size() ; i++ )
        children_joint_.at(i)->Draw();
}
