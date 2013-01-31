#include "object3d.h"
#include <GL/glu.h>

#include <Interpolation/objectanimator.h>

#include "Utils/scenecontainer.h"
#include "Widgets/viewer.h"

std::map<int,Object3D*> Object3D::object_reference_;

Object3D::Object3D()
{ 
    defaultInitialisation();
}

Object3D::Object3D(qglviewer::Vec pos) :
    position_(pos)
{
    defaultInitialisation();
}

Object3D::Object3D(qglviewer::Quaternion ori) :
    orientation_(ori)
{
    defaultInitialisation();
}

Object3D::Object3D(qglviewer::Vec pos, qglviewer::Quaternion ori) :
    position_(pos), orientation_(ori)
{
    defaultInitialisation();
}

Object3D::~Object3D() {
    if(quadric_!=NULL)
        gluDeleteQuadric(quadric_);

    object_reference_.erase(id_);
}

std::string Object3D::label() {
    return label_;
}

void Object3D::setLabel(std::string label) {
    label_ = label;
}

int Object3D::id() {
    return id_;
}

void Object3D::defaultInitialisation() {
    size_ = 1.0f;
    quadric_ = NULL;
    draw_object_ = true;
    draw_position_particle_ = false;
    draw_orientation_axes_ = false;

    static int next_id = 0;
    id_ = next_id;
    next_id++;

    object_reference_[id_] = this;

    label_ = "-";

    animator = NULL;

    color_ = qglviewer::Vec(1,1,1);

    draw_bounding_box_ = false;
    bounding_box_max_ = qglviewer::Vec(0.5,0.5,0.5);
    bounding_box_min_ = qglviewer::Vec(-0.5,-0.5,-0.5);
}

void Object3D::glTransform(){
    glTranslated(position_.x,position_.y,position_.z);
    glMultMatrixd(orientation_.matrix());
}

void Object3D::draw(int depth) {
    glPushMatrix();

    glTransform();

    if(SceneContainer::renderOptions(RENDER_SHADER)){
        SceneContainer::viewer_reference_->bindShader();
        if(draw_object_)
            drawObject(depth);
        SceneContainer::viewer_reference_->releaseShader();
    }else{
        if(draw_object_)
            drawObject(depth);
    }
    if(draw_position_particle_)
        drawPositionParticle();
    if(draw_orientation_axes_)
        drawOrientationAxes();
    if(draw_bounding_box_)
        drawBoundingBox();
    if(SceneContainer::drawBones())
        drawBone(depth);

    glPopMatrix();
}

void Object3D::drawPositionParticle() {
    if(quadric_ == NULL)
        quadric_ = gluNewQuadric();

    /*glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_LIGHTING);*/
    gluSphere(quadric_,0.05,5,5);
    /*glPopAttrib();*/
}

void Object3D::drawOrientationAxes() {

    double radius = 2.0;
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(radius, 0.0, 0.0);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, radius, 0.0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, radius);
    glEnd();
    glPopAttrib();
}

void Object3D::drawObject(int) {
}

void Object3D::setAnimator(ObjectAnimator *animator)
{
    this->animator = animator;
}

ObjectAnimator *Object3D::getAnimator()
{
    return animator;
}

void Object3D::drawBoundingBox()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINE_STRIP);

    glVertex3f(bounding_box_max_.x,bounding_box_max_.y,bounding_box_max_.z);
    glVertex3f(bounding_box_max_.x,bounding_box_max_.y,bounding_box_min_.z);
    glVertex3f(bounding_box_min_.x,bounding_box_max_.y,bounding_box_min_.z);
    glVertex3f(bounding_box_min_.x,bounding_box_max_.y,bounding_box_max_.z);
    glVertex3f(bounding_box_max_.x,bounding_box_max_.y,bounding_box_max_.z);

    glVertex3f(bounding_box_max_.x,bounding_box_min_.y,bounding_box_max_.z);
    glVertex3f(bounding_box_max_.x,bounding_box_min_.y,bounding_box_min_.z);
    glVertex3f(bounding_box_min_.x,bounding_box_min_.y,bounding_box_min_.z);
    glVertex3f(bounding_box_min_.x,bounding_box_min_.y,bounding_box_max_.z);
    glVertex3f(bounding_box_max_.x,bounding_box_min_.y,bounding_box_max_.z);

    glEnd();

    glBegin(GL_LINES);

    glVertex3f(bounding_box_max_.x,bounding_box_max_.y,bounding_box_min_.z);
    glVertex3f(bounding_box_max_.x,bounding_box_min_.y,bounding_box_min_.z);

    glVertex3f(bounding_box_min_.x,bounding_box_max_.y,bounding_box_min_.z);
    glVertex3f(bounding_box_min_.x,bounding_box_min_.y,bounding_box_min_.z);

    glVertex3f(bounding_box_min_.x,bounding_box_max_.y,bounding_box_max_.z);
    glVertex3f(bounding_box_min_.x,bounding_box_min_.y,bounding_box_max_.z);

    glEnd();

    glPopAttrib();
}

void Object3D::drawBoxObject()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glEnable(GL_CULL_FACE);

    glBegin(GL_QUADS);

    glColor3f(color_.x, color_.y, color_.z);

    //Top
    glNormal3f(0,1,0);
    glVertex3f(bounding_box_max_.x,bounding_box_max_.y,bounding_box_max_.z);
    glVertex3f(bounding_box_max_.x,bounding_box_max_.y,bounding_box_min_.z);
    glVertex3f(bounding_box_min_.x,bounding_box_max_.y,bounding_box_min_.z);
    glVertex3f(bounding_box_min_.x,bounding_box_max_.y,bounding_box_max_.z);

    //Bot
    glNormal3f(0,-1,0);
    glVertex3f(bounding_box_max_.x,bounding_box_min_.y,bounding_box_max_.z);
    glVertex3f(bounding_box_min_.x,bounding_box_min_.y,bounding_box_max_.z);
    glVertex3f(bounding_box_min_.x,bounding_box_min_.y,bounding_box_min_.z);
    glVertex3f(bounding_box_max_.x,bounding_box_min_.y,bounding_box_min_.z);

    //Front
    glNormal3f(0,0,1);
    glVertex3f(bounding_box_max_.x,bounding_box_max_.y,bounding_box_max_.z);
    glVertex3f(bounding_box_min_.x,bounding_box_max_.y,bounding_box_max_.z);
    glVertex3f(bounding_box_min_.x,bounding_box_min_.y,bounding_box_max_.z);
    glVertex3f(bounding_box_max_.x,bounding_box_min_.y,bounding_box_max_.z);

    //Back
    glNormal3f(0,0,-1);
    glVertex3f(bounding_box_max_.x,bounding_box_max_.y,bounding_box_min_.z);
    glVertex3f(bounding_box_max_.x,bounding_box_min_.y,bounding_box_min_.z);
    glVertex3f(bounding_box_min_.x,bounding_box_min_.y,bounding_box_min_.z);
    glVertex3f(bounding_box_min_.x,bounding_box_max_.y,bounding_box_min_.z);

    //Left
    glNormal3f(-1,0,0);
    glVertex3f(bounding_box_min_.x,bounding_box_max_.y,bounding_box_max_.z);
    glVertex3f(bounding_box_min_.x,bounding_box_max_.y,bounding_box_min_.z);
    glVertex3f(bounding_box_min_.x,bounding_box_min_.y,bounding_box_min_.z);
    glVertex3f(bounding_box_min_.x,bounding_box_min_.y,bounding_box_max_.z);


    //Right
    glNormal3f(1,0,0);
    glVertex3f(bounding_box_max_.x,bounding_box_max_.y,bounding_box_max_.z);
    glVertex3f(bounding_box_max_.x,bounding_box_min_.y,bounding_box_max_.z);
    glVertex3f(bounding_box_max_.x,bounding_box_min_.y,bounding_box_min_.z);
    glVertex3f(bounding_box_max_.x,bounding_box_max_.y,bounding_box_min_.z);

    glEnd();

    glPopAttrib();
}


void Object3D::drawBone(int depth)
{
}

Object3D *Object3D::getObjectByID(int id)
{
    if(object_reference_.find(id)!=object_reference_.end()){
        return object_reference_[id];
    }
    return NULL;

}
