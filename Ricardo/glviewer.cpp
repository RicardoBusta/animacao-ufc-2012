#include "glviewer.h"

#include "animation.h"
#include <QVector3D>

GLViewer::GLViewer(QWidget *parent) :
    QGLViewer(parent)
{
    ortho = true;
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
//    glBegin(GL_LINE_STRIP);
//    glColor3f(1,0,0);
//    glVertex3f(0,0,0);
//    glVertex3f(1,0,0);
//    glVertex3f(1,1,0);
//    glVertex3f(1,1,1);
//    glEnd();

    float s = 0.5;

    glBegin(GL_TRIANGLES);

    glColor3f(1,1,1);
    //Wings
    glVertex3f(-2*s,0,0);
    glVertex3f(2*s,0,0);
    glVertex3f(0,0,2*s);

    glVertex3f(-2*s,0,0);
    glVertex3f(0,0,2*s);
    glVertex3f(2*s,0,0);

    //Bottom
    glVertex3f(-1*s,0,0);
    glVertex3f(1*s,0,0);
    glVertex3f(0,0,3*s);

    glColor3f(0,1,1);
    //TopLeft
    glVertex3f(-1*s,0,0);
    glVertex3f(0,0,3*s);
    glVertex3f(0,1*s,0);

    //TopRight
    glVertex3f(1*s,0,0);
    glVertex3f(0,1*s,0);
    glVertex3f(0,0,3*s);

    glColor3f(1,0,0);
    //Back
    glVertex3f(1*s,0,0);
    glVertex3f(-1*s,0,0);
    glVertex3f(0,1*s,0);

    glColor3f(0,0,1);
    //Tail
    glVertex3f(0,0,0);
    glVertex3f(0,0,1.5*s);
    glVertex3f(0,2*s,0);

    glVertex3f(0,0,0);
    glVertex3f(0,2*s,0);
    glVertex3f(0,0,1.5*s);

    glEnd();

//    glBegin(GL_LINES);
//    QVector3D v = animation->frame.at(animation->currentFrame);
//    glVertex3f(0,0,0);
//    glVertex3f(v.x(),v.y(),v.z());
//    glEnd();
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
