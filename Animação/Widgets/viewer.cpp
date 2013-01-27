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

static double gx = 0;
static qglviewer::Vec goal;
static qglviewer::Vec effector;

Viewer::Viewer(QWidget* parent) :
    QGLViewer(parent){
    grid_size_ = 2.0;
    grid_div_ = 20;

    connect( &ikTimer, SIGNAL(timeout()), this, SLOT(ikTimeout()) );
}

#include "Utils/iksolver.h"
#include "Utils/matrix4d.h"

void Viewer::draw() {

    SceneContainer::drawObjects();
    SceneContainer::drawExtras();

    if(SceneContainer::ikMode() and SceneContainer::selectedObject()!=NULL){
        qglviewer::Vec effector = ((Joint*)SceneContainer::selectedObject())->globalTransformationMatrix().apply(qglviewer::Vec(0,0,0),false);
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glPointSize(10);
        glBegin(GL_POINTS);
        glColor3f(0,1,0);
        glVertex3f(goal.x,goal.y,goal.z);
        glColor3f(1,0,0);
        glVertex3f(effector.x,effector.y, effector.z);
        glEnd();
        glPopAttrib();
    }

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
    /*
    static GLfloat light1pos[4] = { -0.892, 0.3, 0.9, 0.0 };
    static GLfloat light1diffuse[] = { 0.8f, 0.8f, 0.8, 1.0f };
    static GLfloat light1specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };

    static GLfloat light2pos[4] = { 0.588, 0.46, 0.248, 0.0 };
    static GLfloat light2diffuse[] = { 0.498f, 0.5f, 0.6, 1.0f };
    static GLfloat light2specular[] = { 0.2f, 0.2f, 0.2f, 1.0f };

    static GLfloat light3pos[4] = { 0.216, -0.392, -0.216, 0.0 };
    static GLfloat light3diffuse[] = { 0.798f, 0.838f, 1.0, 1.0f };
    static GLfloat light3specular[] = { 0.06f, 0.0f, 0.0f, 1.0f };

    glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    //glLightfv(GL_LIGHT0, GL_POSITION, light1pos);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, light1diffuse);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, light1specular);

    glLightfv(GL_LIGHT1, GL_POSITION, light2pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light2diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light2specular);

    glLightfv(GL_LIGHT2, GL_POSITION, light3pos);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light3diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light3specular);*/

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
    ikTimer.start(100);
}

void Viewer::ikStop()
{
    ikTimer.stop();
}

#include <Utils/matrix4d.h>

void Viewer::ikTimeout()
{
    if(SceneContainer::ikMode() and SceneContainer::selectedObject()!=NULL){
        goal = effector + qglviewer::Vec(0.1,0,0);
        effector = ((Joint*)SceneContainer::selectedObject())->globalTransformationMatrix().apply(qglviewer::Vec(0,0,0),false);

        IKSolver::solve((Joint*)SceneContainer::selectedObject(),goal,1);
    }

    repaint();
}
