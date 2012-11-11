#include "glmathelements.h"

#include <QtOpenGL>
#include "graphics/material.h"

void GLMathElements::drawAxis(float size)
{
    Material material;

    //glDisable(GL_);

    //x axis (red)
    glBegin(GL_LINES);
    glColor3f(0.9,0,0);
    glVertex3f(0,0,0);
    glVertex3f(size,0,0);
    glEnd();

    //y axis (green)
    glBegin(GL_LINES);
    glColor3f(0,0.9,0);
    glVertex3f(0,0,0);
    glVertex3f(0,size,0);
    glEnd();

    //z axis (blue)
    glBegin(GL_LINES);
    glColor3f(0,0,0.9);
    glVertex3f(0,0,0);
    glVertex3f(0,0,size);
    glEnd();

    glEnd();
}
