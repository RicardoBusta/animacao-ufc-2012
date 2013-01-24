#include "simpledraw.h"
#include <GL/glut.h>
#include "math/iksolve.h"
static bool flag = true;
SimpleDraw::SimpleDraw()
{
    link[0] =new Link(0);
            link[1] = new Link(1);
            link[2] = new Link(2);
            link[3] = new Link(3);

    joint[0] = new Joint(link[0]);
    joint[1] = new Joint(link[1]);
            joint[2] = new Joint(link[2]);
            joint[3] = new Joint(link[3]);
    //definição dos links


    link[0]->_color = Vec4(0,1,0);
    link[1]->_color = Vec4(0,0,1);
    link[2]->_color = Vec4(1,1,0);
    link[3]->_color = Vec4(1,0,0);

    //definição dos joints

    joint[0]->setPosition(Vec4(0,0,0));
    joint[1]->setPosition(Vec4(0,1,0));
    joint[2]->setPosition(Vec4(0,1,0));
    joint[3]->setPosition(Vec4(0,1,0));

    //definindo a hierarquia
    joint[0]->AddChildJoint(joint[1]);
    joint[1]->AddChildJoint(joint[2]);
    joint[2]->AddChildJoint(joint[3]);

    //aplicando rotações
    joint[0]->applyOrientation(Vec4(0,0,1,90));
    joint[1]->applyOrientation(Vec4(0,1,1,85));
    joint[2]->applyOrientation(Vec4(0,0,1,60));
    joint[3]->applyOrientation(Vec4(0,0,1,10));

}

void SimpleDraw::drawAxis(double length)
{

    glColor4f(1.0,0.0,0.0,0.8);
    glBegin(GL_LINES);
       glVertex3d(length,0.0,0.0);
       glVertex3d(0.0,0.0,0.0);
    glEnd();
    glColor4f(0.0,1.0,0.0,0.8);
    glBegin(GL_LINES);
       glVertex3d(0.0,length,0.0);
       glVertex3d(0.0,0.0,0.0);
    glEnd();
    glColor4f(0.0,0.0,1.0,0.8);
    glBegin(GL_LINES);
       glVertex3d(0.0,0.0,length);
       glVertex3d(0.0,0.0,0.0);
       glEnd();

}

void SimpleDraw::structure()
{



    //funções extras
    joint[0]->DrawObject();
    glColor3d(0.5,0.5,1);
 //   Vec4 goal(2,2,2);
    //printf("\nJoint 0 --------------\n:");
    //joint[0]->transform.transpose().showMatrix4f();
    //joint[0]->getPositionAbsolute().drawVec4(40);
    //joint[0]->getPositionAbsolute().showVec4();
    //joint[0]->getPositionAbsolute().showVec4();
    //printf("\nJoint 1 --------------\n:");
    //joint[1]->transform.transpose().showMatrix4f();
    //joint[1]->getPositionAbsolute().drawVec4(40);
    //joint[1]->getPositionAbsolute().showVec4();
    //joint[1]->getPositionAbsolute().showVec4();
    //printf("\nJoint 2 --------------\n:");
    //joint[2]->transform.transpose().showMatrix4f();
   // joint[2]->getPositionAbsolute().showVec4();
   // joint[2]->getPositionAbsolute().drawVec4(40);
    //joint[2]->getPositionAbsolute().showVec4();
   // printf("\nJoint 3 --------------\n:");
    //joint[3]->transform.transpose().showMatrix4f();
 //joint[3]->getPositionAbsolute().showVec4();
//    joint[3]->getPositionAbsolute().drawVec4(40);
    glColor3f(1,0,1);
//    goal.drawVec4(10);
//    joint[0]->DrawObject();
    //joint[0]->DrawObject();
    //IKSolve::IKSolveKinematicsInverse(joint[3],goal);
    //joint[3]->getPositionAbsolute().showVec4();
    //joint[1]->getPositionAbsolute().drawVec4(20);
    //joint[0]->DrawObject();

}

void SimpleDraw::solveIK(Vec4 goal,Joint *joint,int type)
{
    //joint[3]->getPositionEffector();
    IKSolve::IKSolveKinematicsInverse(joint,goal,type);

}
