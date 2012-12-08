#include "object3d.h"
#include <GL/glu.h>

Object3D::Object3D()
{
    DefaultInitialisation();
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

void Object3D::DefaultInitialisation() {
    quadric_ = NULL;
    draw_object_ = true;
    draw_position_particle_ = false;
    draw_orientation_axes_ = false;
}

void Object3D::Draw() {
    glPushMatrix();
    glTranslated(position_.x,position_.y,position_.z);
    glMultMatrixd(orientation_.matrix());    

    if(draw_position_particle_)
        DrawPositionParticle();
    if(draw_orientation_axes_)
        DrawOrientationAxes();
    if(draw_object_)
        DrawObject();

    glPopMatrix();
}

void Object3D::DrawPositionParticle() {
    if(quadric_ == NULL)
        quadric_ = gluNewQuadric();

    gluSphere(quadric_,2.0,5,5);
}

void Object3D::DrawOrientationAxes() {

    double radius = 2.0;

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
}

void Object3D::DrawObject() {

}
