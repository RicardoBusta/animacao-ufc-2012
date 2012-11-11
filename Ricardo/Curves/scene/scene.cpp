#include "scene.h"

#include "graphics/camera.h"

#include "graphics/glprimitive.h"
#include "graphics/material.h"
#include "math/matrix4f.h"
#include "math/vector3f.h"

#include "graphics/glmathelements.h"
#include "graphics/glvectorfunctions.h"

#include "graphics/curve.h"

#include <QtOpenGL>

Scene::Scene()
{
    transform.setIdentity();

    rotx = 0;
    roty = 0;

    points.push_back( new Vector3f( 10, 10, 10) );
    points.push_back( new Vector3f( 100, -100, 20) );
    points.push_back( new Vector3f( 200, 80, 100) );
    points.push_back( new Vector3f( 500, -30, 50) );

    calculateCurve();
}

Scene::~Scene()
{
}

void Scene::draw()
{
    glLoadIdentity();

    glTranslatef(0,0,-1000);
    glRotatef(rotx,1,0,0);
    glRotatef(roty,0,1,0);

    GLMathElements::drawAxis(300);

    glColor3f(0.8,0.8,0);
    for(std::vector<Vector3f*>::iterator it = points.begin(); it!= points.end(); it++){
        glPushMatrix();
        transform.setPosition(*(*it));
        transform.gl();
        GLPrimitive::sphere(4);
        //glVertex3f((*it)->getX(),(*it)->getY(),(*it)->getZ());
        glPopMatrix();
    }

    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    for(std::vector<Vector3f*>::iterator it = curve.begin(); it!= curve.end(); it++){
        glVertex3f((*it)->getX(),(*it)->getY(),(*it)->getZ());
    }
    glEnd();
}

void Scene::calculateCurve()
{
    genBezier();
}

void Scene::clearCurve()
{
}

void Scene::genBezier()
{
    for(std::vector<Vector3f*>::iterator it = points.begin(); it!= points.end(); it++){
        curve.push_back( new Vector3f((*it)->getX(),(*it)->getY(),(*it)->getZ()) );
    }
}








