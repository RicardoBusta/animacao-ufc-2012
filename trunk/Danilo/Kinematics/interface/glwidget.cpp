#include "glwidget.h"
#include "math/vec4.h"
#include "skeleton/link.h"
#include "simple/simpledraw.h"
//Link* l = new Link(0);
//Link* l2 = new Link(1);
//Vec4 k = Vec4(-1,0,0,90);
//double d = 0.25;
/*Vec4 goal = Vec4(2,2,2)*/
SimpleDraw joint;


static int width,height;

//Vec4 v = Vec4(1,0,0);
GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateGL()));
    timer.start(10);
    type = 0;
//    l->setPosition(k);
//    l2->setPosition(v);
    goal.setVec4(2,2,2);
}


void GLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

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
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    glLightfv(GL_LIGHT0, GL_POSITION, light1pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light1diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light1specular);

    glLightfv(GL_LIGHT1, GL_POSITION, light2pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light2diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light2specular);

    glLightfv(GL_LIGHT2, GL_POSITION, light3pos);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light3diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light3specular);

    static GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMateriali(GL_FRONT_AND_BACK,GL_SHININESS, 256);

}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glRotated(1,0,1,0);
    //hemiSphere->draw();
    //Vec4 O;
    //O.drawVec4(10);
    SimpleDraw::drawAxis(1);
    //SimpleDraw::structure();
    joint.structure();
//    goal.setVec4(1,0,3);
    Vec4 posEffector = joint.joint[3]->getPositionEffector();
    //goal = (goal-posEffector)*d;
    //if((goal-posEffector).module()>0.0001){
        //goal.setVec4(2,-2,2);
        joint.solveIK(goal,joint.joint[3],type);
    //}
    glColor3f(1,0.8,0.8);
    goal.drawVec4(20);
//    k.drawVec4(10);
//    v.drawVec4(10);
//    l->draw();
    //l->applyOrientation(k);
//    l2->draw();



    //cylinder->draw();
    //prism->draw();
    //cube->draw();

    //Functions::saveImage(width,height,"teste.tga"); salvar imagem
}

void GLWidget::resizeGL(int w, int h)
{
     //width  = w;
     //height = h;
     glViewport(0,0,w,h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(100,(float)w/h,0.001,120000.0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     gluLookAt(2,4.5,2, 0,1,0, 0,1,0);

}

void GLWidget::setGoal(Vec4 g)
{
    goal = g;
}

void GLWidget::setType(int t)
{
    type = t;
}
