#include "joint.h"

Joint::Joint(Object3D* child_object)
{
    if(child_object!=NULL){
        label_ = (child_object->label() + " Joint");
    }else{
        label_ = "Empty Joint";
    }
    child_object_ = child_object;

    parent_joint_ = NULL;
}

void Joint::AddChildJoint(Joint* child) {
    children_joint_.push_back(child);
    child->parent_joint_ = this;
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

void Joint::DrawBoundingBox()
{
    child_object_->DrawBoundingBox();
}

void Joint::DrawBone()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);

    for(size_t i=0;i<children_joint_.size();i++){
        qglviewer::Vec pos = children_joint_.at(i)->position();

        glVertex3f(0,0,0);
        glVertex3f(pos.x,pos.y,pos.z);
    }
    glEnd();
    glPopAttrib();
}
