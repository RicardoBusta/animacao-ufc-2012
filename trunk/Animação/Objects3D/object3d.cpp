#include "object3d.h"
#include <GL/glu.h>

#include <Interpolation/objectanimator.h>

#include "Utils/scenecontainer.h"
#include "Widgets/viewer.h"

Object3D::Object3D()
{ 
    DefaultInitialisation();

    animator = NULL;

    color_ = qglviewer::Vec(1,1,1);

    draw_bounding_box_ = false;
    bounding_box_max_ = qglviewer::Vec(0.5,0.5,0.5);
    bounding_box_min_ = qglviewer::Vec(-0.5,-0.5,-0.5);
}

Object3D::Object3D(qglviewer::Vec pos) :
    position_(pos)
{
    DefaultInitialisation();
}

Object3D::Object3D(qglviewer::Quaternion ori) :
    orientation_(ori)
{
    DefaultInitialisation();
}

Object3D::Object3D(qglviewer::Vec pos, qglviewer::Quaternion ori) :
    position_(pos), orientation_(ori)
{
    DefaultInitialisation();
}

Object3D::~Object3D() {
    if(quadric_!=NULL)
        gluDeleteQuadric(quadric_);
}

std::string Object3D::label() {
    return label_;
}

void Object3D::SetLabel(std::string label) {
    label_ = label;
}

int Object3D::id() {
    return id_;
}

void Object3D::DefaultInitialisation() {
    quadric_ = NULL;
    draw_object_ = true;
    draw_position_particle_ = false;
    draw_orientation_axes_ = false;

    static int next_id = 0;
    id_ = next_id;
    next_id++;

    label_ = "-";

}

void Object3D::Draw(bool options) {

    glPushMatrix();

    glTranslated(position_.x,position_.y,position_.z);
    glMultMatrixd(orientation_.matrix());

    SceneContainer::viewer_reference_->BindShader();
    if(draw_object_)
        DrawObject(options);
    SceneContainer::viewer_reference_->ReleaseShader();
    if(draw_position_particle_)
        DrawPositionParticle();
    if(draw_orientation_axes_)
        DrawOrientationAxes();
    if(draw_bounding_box_)
        DrawBoundingBox();
    if(SceneContainer::DrawBones())
        DrawBone();

    glPopMatrix();
}

void Object3D::DrawPositionParticle() {
    if(quadric_ == NULL)
        quadric_ = gluNewQuadric();

    /*glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_LIGHTING);*/
    gluSphere(quadric_,0.05,5,5);
    /*glPopAttrib();*/
}

void Object3D::DrawOrientationAxes() {

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

void Object3D::DrawObject(bool options) {
}

void Object3D::SetAnimator(ObjectAnimator *animator)
{
    this->animator = animator;
}

ObjectAnimator *Object3D::GetAnimator()
{
    return animator;
}

void Object3D::DrawBoundingBox()
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

void Object3D::DrawBoxObject()
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


void Object3D::DrawBone()
{
//    glPushAttrib(GL_ALL_ATTRIB_BITS);
//    glDisable(GL_LIGHTING);
//    glDisable(GL_DEPTH_TEST);
//    glBegin(GL_LINES);
//    glVertex3f(0,0,0);
//    glVertex3f(1,1,1);
//    glEnd();
//    glPopAttrib();
}
