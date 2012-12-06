#include "glviewer.h"

GLViewer::GLViewer(QWidget *parent) :
    QGLViewer(parent)
{
}


void GLViewer::draw()
{
    glBegin(GL_LINE_STRIP);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glVertex3f(1,1,0);
    glVertex3f(1,1,1);
    glEnd();
}
