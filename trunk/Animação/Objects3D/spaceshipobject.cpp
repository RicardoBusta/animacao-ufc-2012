#include "spaceshipobject.h"


SpaceShipObject::SpaceShipObject()
{
}

void SpaceShipObject::DrawObject() {
    /*double height = 3.0;
    qglviewer::Quaternion orientation = qglviewer::Quaternion(qglviewer::Vec(0,0,1),qglviewer::Vec(0,1,0));
    gluCylinder(quadric_,0.5,0.5,height,16,16);
    glPushMatrix();
    glTranslated(0,-height/2.0,height);
    glMultMatrixd(orientation.matrix());
    gluCylinder(quadric_,0.5,0.5,height,16,16);
    glPopMatrix();*/


    qglviewer::Quaternion orientation = qglviewer::Quaternion(qglviewer::Vec(0,0,1),qglviewer::Vec(1,0,0));
    glPushMatrix();
    glMultMatrixd(orientation.matrix());
    double s = 0.5;
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_LIGHTING);
    glBegin(GL_TRIANGLES);

    glColor3f(1,1,1);
    //Wings
    glVertex3f(-2*s,0,0);
    glVertex3f(2*s,0,0);
    glVertex3f(0,0,2*s);

    glVertex3f(-2*s,0,0);
    glVertex3f(0,0,2*s);
    glVertex3f(2*s,0,0);

    // Bottom
    glVertex3f(-1*s,0,0);
    glVertex3f(1*s,0,0);
    glVertex3f(0,0,3*s);

    glColor3f(0,1,1);

    // Top Left
    glVertex3f(-1*s,0,0);
    glVertex3f(0,0,3*s);
    glVertex3f(0,s,0);

    // Top Right
    glVertex3f(1*s,0,0);
    glVertex3f(0,s,0);
    glVertex3f(0,0,3*s);

    // Back
    glVertex3f(s,0,0);
    glVertex3f(-s,0,0);
    glVertex3f(0,s,0);

    glColor3f(0,0,1);
    // Tail
    glVertex3f(0,0,0);
    glVertex3f(0,0,1.5*s);
    glVertex3f(0,2*s,0);

    glVertex3f(0,0,0);
    glVertex3f(0,2*s,0);
    glVertex3f(0,0,1.5*s);
    glEnd();

    glPopAttrib();
    glPopMatrix();
}
