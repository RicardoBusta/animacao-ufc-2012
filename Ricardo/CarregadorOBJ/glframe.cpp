#include "glframe.h"

GLFrame::GLFrame(QWidget *parent)
    :QWidget(parent)
{

    glwidget = new GLWidget(this);
}

GLFrame::~GLFrame()
{
    if(glwidget!=NULL) delete glwidget;
}

void GLFrame::resizeEvent(QResizeEvent *)
{
    glwidget->resize(this->size());
    glwidget->update();
}
