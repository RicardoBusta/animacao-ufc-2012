#include "spaceshipobject.h"

static QImage shiptex;

SpaceShipObject::SpaceShipObject()
{
     shiptex = QGLWidget::convertToGLFormat( QImage(":ship.png") );
}

void SpaceShipObject::DrawObject(bool) {
    /*double height = 3.0;
    qglviewer::Quaternion orientation = qglviewer::Quaternion(qglviewer::Vec(0,0,1),qglviewer::Vec(0,1,0));
    gluCylinder(quadric_,0.5,0.5,height,16,16);
    glPushMatrix();
    glTranslated(0,-height/2.0,height);
    glMultMatrixd(orientation.matrix());
    gluCylinder(quadric_,0.5,0.5,height,16,16);
    glPopMatrix();*/

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    GLuint texId;
    glGenTextures( 1, &texId );
    glBindTexture( GL_TEXTURE_2D, texId );
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, shiptex.width(), shiptex.height(), 0, GL_RGBA,GL_UNSIGNED_BYTE, shiptex.bits());


    qglviewer::Quaternion orientation = qglviewer::Quaternion(qglviewer::Vec(0,0,1),qglviewer::Vec(1,0,0));
    glPushMatrix();
    glMultMatrixd(orientation.matrix());
    double s = 0.5;
    //glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_LIGHTING);
    glBegin(GL_TRIANGLES);

    glColor3f(1,1,1);
    //Wings
    glTexCoord2f(1.0,1.0);
    glVertex3f(-2*s,0,0);
    glTexCoord2f(0.5,0.5);
    glVertex3f(2*s,0,0);
    glTexCoord2f(0.5,1.0);
    glVertex3f(0,0,2*s);

    glTexCoord2f(1.0,1.0);
    glVertex3f(-2*s,0,0);
    glTexCoord2f(0.5,1.0);
    glVertex3f(0,0,2*s);
    glTexCoord2f(0.5,0.5);
    glVertex3f(2*s,0,0);

    // Bottom
    glTexCoord2f(1.0,1.0);
    glVertex3f(-1*s,0,0);
    glTexCoord2f(0.5,0.5);
    glVertex3f(1*s,0,0);
    glTexCoord2f(0.5,1.0);
    glVertex3f(0,0,3*s);

    //glColor3f(0,1,1);

    // Top Left
    glTexCoord2f(0.0,1.0);
    glVertex3f(-1*s,0,0);
    glTexCoord2f(0.0,0.0);
    glVertex3f(0,0,3*s);
    glTexCoord2f(0.5,1.0);
    glVertex3f(0,s,0);

    // Top Right
    glTexCoord2f(0.0,1.0);
    glVertex3f(1*s,0,0);
    glTexCoord2f(0.5,1.0);
    glVertex3f(0,s,0);
    glTexCoord2f(0.0,0.0);
    glVertex3f(0,0,3*s);

    // Back
    glTexCoord2f(0.5,0.0);
    glVertex3f(s,0,0);
    glTexCoord2f(1.0,0.5);
    glVertex3f(-s,0,0);
    glTexCoord2f(1.0,0.0);
    glVertex3f(0,s,0);

    //glColor3f(0,0,1);
    // Tail
    glTexCoord2f(0.5,1.0);
    glVertex3f(0,0,0);
    glTexCoord2f(0.5,0.5);
    glVertex3f(0,0,1.5*s);
    glTexCoord2f(1.0,1.0);
    glVertex3f(0,2*s,0);

    glTexCoord2f(0.5,1.0);
    glVertex3f(0,0,0);
    glTexCoord2f(0.5,0.5);
    glVertex3f(0,2*s,0);
    glTexCoord2f(1.0,1.0);
    glVertex3f(0,0,1.5*s);
    glEnd();

    glPopAttrib();
    glPopMatrix();
}
