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

#include "Objects3D/particle.h"

#include "Utils/iksolver.h"
#include "Utils/matrix4d.h"

RotationWidget* rotation = new RotationWidget(new Object3D());

static qglviewer::Vec effector;

Viewer::Viewer(QWidget* parent) :
    QGLViewer(parent)
{
    goal = qglviewer::Vec(-5, 5.0, 1.0);
    grid_size_ = 2.0;
    grid_div_ = 20;

    connect( &ikTimer, SIGNAL(timeout()), this, SLOT(ikTimeout()) );
}

void Viewer::draw() {

    SceneContainer::drawObjects();
    SceneContainer::drawExtras();

    glColor3f(1,1,1);

    this->drawText(10,10,QString("Frame: %1").arg(SceneContainer::current_frame()));

    //rotation->Draw();
}

void Viewer::drawWithNames(){
    SceneContainer::setDrawWithNames(true);
    SceneContainer::drawObjectsNoShader();
    SceneContainer::setDrawWithNames(false);
}

void Viewer::play() {
    if(!animationIsStarted()) {
        startAnimation();
    }
}

void Viewer::stop() {
    if(animationIsStarted()) {
        stopAnimation();
    }
    if(SceneContainer::current_frame()!=0) {
        SceneContainer::setCurrentFrame(0);
        emit currentFrame(0);
        updateGL();
    }
}

void Viewer::pause() {
    if(animationIsStarted()) {
        stopAnimation();
    }
}

void Viewer::animate() {

    SceneContainer::goToNextFrame();
    emit currentFrame(SceneContainer::current_frame());
}

void  Viewer::setCurrentFrame(int frame) {
    SceneContainer::setCurrentFrame(frame);
    updateGL();
}

void Viewer::init() {
    SceneContainer::updateCurrentScene(0);
    emit signalUpdateObjects();

    SceneContainer::setFrameRange(0,100);
    SceneContainer::setCurrentFrame(0);

    this->setBackgroundColor(QColor(45,45,45));
    this->setGridIsDrawn(true);
    this->grid_size_ = 10.0;

    setSceneRadius(10.0f);

    this->camera()->fitSphere(qglviewer::Vec(0,5,0),10);

    //SHADER TEST

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    setSelectRegionWidth(5);
    setSelectRegionHeight(5);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    setCurrentShader(0);
    shader_enabled_ = true;
    //SHADER TEST
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

    SceneContainer::drawParticles();
    SceneContainer::drawPost();
}

QString Viewer::helpString() const {
    return QString();
}

void Viewer::setCurrentShader(int shader)
{
    current_shader_ = shader;
    shader_enabled_ = true;
    shaderProgram.removeAllShaders();
    SceneContainer::setAlternateColors(false);
    switch(shader){
    case 0:
        shaderProgram.addShaderFromSourceFile(QGLShader::Vertex, ":/shaders/phong.vert");
        shaderProgram.addShaderFromSourceFile(QGLShader::Fragment, ":/shaders/phong.frag");
        break;
    case 1:
        SceneContainer::setAlternateColors(true);
        shaderProgram.addShaderFromSourceFile(QGLShader::Vertex, ":/shaders/toon.vert");
        shaderProgram.addShaderFromSourceFile(QGLShader::Fragment, ":/shaders/toon.frag");
        break;
    default:
        shader_enabled_ = false;
        break;
    }
    repaint();
}

void Viewer::releaseShader()
{
    shaderProgram.release();
}

void Viewer::bindShader(){
    if(shader_enabled_){
        shaderProgram.bind();
    }
}

void Viewer::postSelection(const QPoint &point)
{
    //std::cout << selectedName() << std::endl;
    if(selectedName()>=-1){
        emit updateSelected(selectedName());
    }
}

//#include <QMouseEvent>

//void Viewer::mousePressEvent(QMouseEvent *event)
//{
//    if(event->modifiers()&Qt::ControlModifier){
//        select(event->pos());
//    }else{
//        QGLViewer::mousePressEvent(event);
//    }
//}


void Viewer::ikStart()
{
    ikTimer.start( 1000/60 );
}

void Viewer::ikStop()
{
    ikTimer.stop();
}

#include <Utils/matrix4d.h>

void Viewer::ikTimeout()
{
    //if(!SceneContainer::ikTarget.goalReached()){
        SceneContainer::ikTarget.solve();
        repaint();
    //}else{
//        ikStop();
//    }
}
