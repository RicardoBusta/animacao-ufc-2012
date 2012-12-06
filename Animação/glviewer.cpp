#include "glviewer.h"

GLViewer::GLViewer(QWidget *parent) :
    QGLViewer(parent)
{
}

void GLViewer::init()
{
    this->setBackgroundColor(QColor(0,0,0));
    this->setAxisIsDrawn();
    this->setFPSIsDisplayed();
    this->setGridIsDrawn();
}

void GLViewer::draw()
{
    glDisable(GL_LIGHTING);
    glBegin(GL_LINE_STRIP);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glVertex3f(1,1,0);
    glVertex3f(1,1,1);
    glEnd();
}

void GLViewer::postDraw(){
    bool state = gridIsDrawn();
    setGridIsDrawn(false);
    QGLViewer::postDraw();

    if(state){
        setGridIsDrawn();

        glPushAttrib(GL_COLOR);
        glPushMatrix();
        glColor3f(0.7,0.7,0.7);
        glRotatef(90,1,0,0);
        drawGrid();
        glPopMatrix();
        glPopAttrib();
    }
}
