#include "curve.h"

#include <QtOpenGL>

#include <math/vector3f.h>

Curve::Curve()
{
}

Curve::~Curve(){
    clear();
}

void Curve::clear(){
    for(std::vector<Vector3f*>::iterator it = points.begin(); it!=points.end(); it++){
        delete (*it);
    }
    points.clear();
}

void Curve::addPoint(Vector3f *point)
{
    points.push_back(point);
}

void Curve::gl(){
    glColor3f(1,1,1);
    glBegin(GL_LINE_STRIP);
//        glBegin(GL_POINTS);
    for(std::vector<Vector3f*>::iterator it = points.begin(); it!=points.end(); it++){
        glVertex3f( (*it)->getX(),(*it)->getY(),(*it)->getZ() );
    }
    glEnd();
}
