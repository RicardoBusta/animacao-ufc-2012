#include "skeleton.h"
#include <gsl/gsl_matrix.h>


Skeleton::Skeleton()
{
}

Joint::Joint(Link* children_object)
{
    children_object_ = children_object;
    transform_global.setIdentity();
    parent_ = NULL;
}

void Joint::AddChildJoint(Joint* child) {
    child->setParent(this);
    child->setPositionAbsolute(this->posAbsolute+child->position_);
    children_joint_.push_back(child);
}

int Joint::HowManyChilds() {
    return children_joint_.size();

}

Joint* Joint::ChildAt(int index) {
    return children_joint_.at(index);
}

void Joint::DrawObject() {
    //

    glPushMatrix();


    Matrix4f aux,aux2,res;
    glTranslated(position_.x1,position_.x2,position_.x3);
    aux.translate(position_.x1,position_.x2,position_.x3);
    glMultMatrixd(orientation_.getMatrix().matrix);
    aux2.setMatrix4f(orientation_.getMatrix().matrix);
    res = aux.multMatrix(aux2,aux);
    this->transform = res;



    for(size_t i = 0 ; i < children_joint_.size() ; i++){

        children_joint_.at(i)->DrawObject();


    }
    children_object_->draw();
    this->getPositionAbsolute();
    children_object_->position_.drawVec4(15);
    glPopMatrix();

}


void Joint::setParent(Joint *parent)
{
    this->parent_ = parent;
}

Joint* Joint::getParent()
{
    return this->parent_;
}

Vec4 Joint::getPositionAbsolute()
{
    Matrix4f m;
    Joint* joint;
    joint = this->parent_;
    m.setIdentity();
    if (this->parent_ == NULL){
        transform_global = transform;
        return m.vector(position_);
    }
    while(joint!=NULL){
        m = m.multMatrix(m,joint->transform);
        joint = joint->parent_;

    }
    Matrix4f aux;
    aux.setIdentity();
    aux = transform;
    this->transform_global = m.multMatrix(transform,m);
    m = m.transpose();
    return m.vector(position_);

}

void Joint::setPositionAbsolute(Vec4 pos)
{
    posAbsolute = pos;
}

void Joint::setPosition(Vec4 pos)
{
    position_ = pos;

}

Vec4 Joint::getPositionEffector()
{
    glColor3f(1,1,1);
    Vec4 posEffectorGlobal;
    posEffectorGlobal = transform_global.transpose().vector(children_object_->_posEffector);
    posEffectorGlobal.drawVec4(20);
    return posEffectorGlobal;
}

Joint * Joint::getRoot()
{
    Joint* joint;
    joint = this->parent_;
    if (joint==NULL){
        return joint;
    }
    while(joint!=NULL){
        joint = joint->parent_;

    }
    return joint;
}





