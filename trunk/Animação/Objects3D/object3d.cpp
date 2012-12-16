#include "object3d.h"
#include <GL/glu.h>

#include <Interpolation/objectanimator.h>

Object3D::Object3D()
{ 
    DefaultInitialisation();

    animator = NULL;

    is_joint_ = false;
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
}

void Object3D::Draw(bool animate_position, bool animate_orientation) {
    glPushMatrix();

    if(animate_position)
        glTranslated(position_.x,position_.y,position_.z);

    if(animate_orientation)
        glMultMatrixd(orientation_.matrix());

    if(draw_position_particle_)
        DrawPositionParticle();
    if(draw_orientation_axes_)
        DrawOrientationAxes();
    if(draw_object_)
        DrawObject(animate_position,animate_orientation);

    glPopMatrix();

    DrawTrajectory();
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

void Object3D::DrawObject(bool animate_position, bool animate_orientation) {
}

void Object3D::DrawTrajectory()
{
    if(animator != NULL and animator->GetTrajectory()!=NULL){
        animator->GetTrajectory()->Draw();
    }
}

void Object3D::SetAnimator(ObjectAnimator *animator)
{
    this->animator = animator;
}

ObjectAnimator *Object3D::GetAnimator()
{
    return animator;
}
