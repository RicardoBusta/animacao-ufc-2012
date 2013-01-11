#include "Widgets/viewer.h"
#include <vector>

#include "Curves/arclength.h"
#include <GL/glu.h>
#include "Interpolation/posinterpolator.h"
#include "Utils/scenecontainer.h"
#include "Objects3D/joint.h"
#include "Widgets/rotationwidget.h"

#include <iostream>
#include "Interpolation/objectanimator.h"

RotationWidget* rotation = new RotationWidget(new Object3D());

Viewer::Viewer(QWidget* parent) :
    QGLViewer(parent){
    grid_size_ = 2.0;
    grid_div_ = 20;
}

void Viewer::draw() {

    SceneContainer::DrawObjects();

    this->drawText(10,10,QString("Frame: %1").arg(SceneContainer::current_frame()));

    //rotation->Draw();
}



void Viewer::Play() {
    if(!animationIsStarted()) {
        startAnimation();
    }
}

void Viewer::Stop() {
    if(animationIsStarted()) {
        stopAnimation();
    }
    if(SceneContainer::current_frame()!=0) {
        SceneContainer::SetCurrentFrame(0);
        emit CurrentFrame(0);
        updateGL();
    }
}

void Viewer::Pause() {
    if(animationIsStarted()) {
        stopAnimation();
    }
}

void Viewer::animate() {

    SceneContainer::GoToNextFrame();
    emit CurrentFrame(SceneContainer::current_frame());
}

void  Viewer::SetCurrentFrame(int frame) {
    SceneContainer::SetCurrentFrame(frame);
    updateGL();
}

void Viewer::init() {
    SceneContainer::CreateDefaultScene();
    emit SignalUpdateObjects();

    SceneContainer::SetFrameRange(0,100);
    SceneContainer::SetCurrentFrame(0);

    this->setBackgroundColor(QColor(45,45,45));
    this->setGridIsDrawn(true);
    this->grid_size_ = 10.0;

    setSceneRadius(10.0f);

    this->camera()->fitSphere(qglviewer::Vec(0,5,0),10);
}

void Viewer::postDraw(){
    bool state = gridIsDrawn();
    setGridIsDrawn(false);
    QGLViewer::postDraw();

    if(state){
        setGridIsDrawn();

        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glPushMatrix();
        glRotatef(90,1,0,0);
        glColor3f(0.7,0.7,0.7);
        drawGrid(grid_size_,grid_div_);
        glColor3f(0.1,0.1,0.1);
        drawGrid(grid_size_,grid_div_*2);
        glPopMatrix();
        glPopAttrib();
    }
}

QString Viewer::helpString() const {
    return QString();
}
