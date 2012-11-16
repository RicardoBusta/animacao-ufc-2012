#include "curve.h"

#include <QtOpenGL>

#include <math/vector3f.h>

#include "graphics/glprimitive.h"
#include <math/matrix4f.h>

Curve::Curve()
{
    transform = new Matrix4f();
    transform->setIdentity();
}

Curve::~Curve(){
    delete transform;
    clear();
}

void Curve::clear(){
    for(std::vector<Vector3f*>::iterator it = controlPoints.begin(); it!=controlPoints.end(); it++){
        delete (*it);
    }
    controlPoints.clear();

    for(std::vector<Vector3f*>::iterator it = calculatedPoints.begin(); it!=calculatedPoints.end(); it++){
        delete (*it);
    }
    calculatedPoints.clear();
}

void Curve::calculateCurve()
{
    interp.setControlPoints( *controlPoints[0],*controlPoints[1],*controlPoints[2],*controlPoints[3] );

    for(float t=0.0f; t<1.0f; t+= (1.0f/20.0f) ){
        calculatedPoints.push_back( new Vector3f( interp.getPoint(t) ) );
    }
    calculatedPoints.push_back( new Vector3f( interp.getPoint(1.0) ) );
}

void Curve::addPoint(Vector3f *point)
{
    controlPoints.push_back(point);
}

void Curve::glControlPoints()
{
    glColor3f(0.5,0.5,0.5);
    for(std::vector<Vector3f*>::iterator it = controlPoints.begin(); it!= controlPoints.end(); it++){
        glPushMatrix();
        transform->setPosition(*(*it));
        transform->gl();
        GLPrimitive::sphere(6);
        //glVertex3f((*it)->getX(),(*it)->getY(),(*it)->getZ());
        glPopMatrix();
    }
}

void Curve::glCalculatedPoints()
{
    glColor3f(0.9,0,0);
    for(std::vector<Vector3f*>::iterator it = calculatedPoints.begin(); it!= calculatedPoints.end(); it++){
        glPushMatrix();
        transform->setPosition(*(*it));
        transform->gl();
        GLPrimitive::sphere(6);
        //glVertex3f((*it)->getX(),(*it)->getY(),(*it)->getZ());
        glPopMatrix();
    }
}

void Curve::glCurve()
{
    glBegin(GL_LINE_STRIP);
//    glBegin(GL_POINTS);
    glColor3f(0.9,0.9,0.9);
    for(std::vector<Vector3f*>::iterator it = calculatedPoints.begin(); it!= calculatedPoints.end(); it++){
        glVertex3f((*it)->getX(),(*it)->getY(),(*it)->getZ());
    }
    glEnd();
}

void Curve::glControlLine()
{
}
