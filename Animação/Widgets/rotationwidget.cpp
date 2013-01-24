#include "Widgets/rotationwidget.h"
#include "Objects3D/torus.h"

RotationWidget::RotationWidget(Object3D* to_rotate)
{
    setNewPosition(to_rotate->position());
    to_rotate_ = to_rotate;
    quadric_ = gluNewQuadric();
}

RotationWidget::~RotationWidget() {
    gluDeleteQuadric(quadric_);
}

void RotationWidget::setClick(qglviewer::Vec) {

}

void RotationWidget::drawCircle(double, qglviewer::Quaternion ori, int) {
    glPushMatrix();
    glMultMatrixd(ori.matrix());
    Torus t(0.96*radius_,1.04*radius_,64,36);
    t.draw(0);
    glPopMatrix();
}

void RotationWidget::drawObject() {
    int steps = 40;
    radius_ = 0.5;
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glDisable(GL_LIGHTING);
    glColor3d(1.0,0.0,0.0);
    drawCircle(radius_,qglviewer::Quaternion(qglviewer::Vec(0.0,1.0,0.0),qglviewer::Vec(1.0,0.0,0.0)),steps);

    glColor3d(0.0,1.0,0.0);
    drawCircle(radius_,qglviewer::Quaternion(qglviewer::Vec(0.0,1.0,0.0),qglviewer::Vec(0.0,1.0,0.0)),steps);

    glColor3d(0.0,0.0,1.0);
    drawCircle(radius_,qglviewer::Quaternion(qglviewer::Vec(0.0,1.0,0.0),qglviewer::Vec(0.0,0.0,1.0)),steps);

    glEnable(GL_LIGHTING);
    glColor3d(1.0,1.0,1.0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glColor4d(1.0,1.0,1.0,0.5);
    gluSphere(quadric_,0.995*radius_,steps,steps);



    glPopAttrib();
}
