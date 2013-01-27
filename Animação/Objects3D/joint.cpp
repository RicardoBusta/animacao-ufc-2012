#include "joint.h"

#include <QString>

#include "Utils/scenecontainer.h"
#include "Utils/matrix4d.h"

Joint::Joint(Object3D* child_object)
{
    if(child_object!=NULL){
        label_ = (QString::number(id()).toStdString() + " " + child_object->label() + " Joint");
    }else{
        label_ = "Empty Joint";
    }
    child_object_ = child_object;

    parent_joint_ = NULL;
}

Joint::~Joint(){
    if(child_object_ != NULL){
        delete child_object_;
    }

    while(!children_joint_.empty()){
        delete children_joint_.back();
        children_joint_.pop_back();
    }
}

void Joint::addChildJoint(Joint* child) {
    children_joint_.push_back(child);
    child->parent_joint_ = this;
}

int Joint::howManyChilds() {
    return children_joint_.size();

}

Joint* Joint::childAt(int index) {
    return children_joint_.at(index);
}

void Joint::drawObject(int depth) {

    if(SceneContainer::getDrawWithNames()){
        glPushName(id());
    }

    child_object_->draw(depth+1);
    if(SceneContainer::getDrawWithNames()){
        glPopName();
    }

    for(size_t i = 0 ; i < children_joint_.size() ; i++ )
        children_joint_.at(i)->draw(depth+1);


}


Object3D *Joint::childObject()
{
    return child_object_;
}

void Joint::drawBoundingBox()
{
    glPushMatrix();
    child_object_->glTransform();
    child_object_->drawBoundingBox();
    glPopMatrix();
}

void Joint::drawBone(int depth)
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);

    if(depth%2==0){
        glColor3ub(0,100,255);
    }else{
        glColor3ub(255,100,0);
    }

    for(size_t i=0;i<children_joint_.size();i++){
        qglviewer::Vec pos = children_joint_.at(i)->position();

        glVertex3f(0,0,0);
        glVertex3f(pos.x,pos.y,pos.z);
    }
    glEnd();
    glPopAttrib();
}


Joint *Joint::parent()
{
    return parent_joint_;
}


Matrix4D Joint::globalTransformationMatrix()
{
        if(parent()==NULL) return ( Matrix4D(position()) * Matrix4D(orientation()) );

        return ( parent()->globalTransformationMatrix() * ( Matrix4D(position()) * Matrix4D(orientation()) ) );
}


qglviewer::Vec Joint::globalPosition()
{
    return globalTransformationMatrix().apply(qglviewer::Vec(0,0,0),false);
//    qglviewer::Vec origin;
//    Joint* it = this;
//    while(it != NULL) {
//        origin = it->orientation().rotate(origin);
//        origin = origin + it->position();
//        it = it->parent();
//    }
//    return origin;
}
