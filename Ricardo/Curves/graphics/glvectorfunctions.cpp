#include "glvectorfunctions.h"

#include <QtOpenGL>

#include "math/vector3f.h"
#include <cmath>

Vector3f GLVectorFunctions::f(float t){
    Vector3f v;

    //x
    v.setX( 100*sin(t) );
    //y
    v.setY( 10*t );
    //z
    v.setZ( 100*cos(t) );

    return v;
}

void GLVectorFunctions::gl(){

    glColor3f(1,1,1);
    glBegin(GL_LINE_STRIP);
    Vector3f v;
    for(int i=0;i<10000;i++){
        v = f((float)i/100.0);
        glVertex3f(v.getX(), v.getY(), v.getZ());
    }
    glEnd();
}
