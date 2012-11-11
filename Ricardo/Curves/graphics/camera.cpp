#include "camera.h"

#include <QtOpenGL>

#include "../math/vector3f.h"
#include "../math/matrix4f.h"

#ifdef DEBUG_MODE
#include <iostream>
using namespace std;
#endif

Camera::Camera()
{
    posAt = new Vector3f( 0.0, 0.0, 0.0 );
    lookAt = new Vector3f( 0.0, 0.0, -1.0 );
    upAt = new Vector3f( 0.0, 1.0, 0.0 );

    forward = new Vector3f();
    side = new Vector3f();
    up = new Vector3f();

    matrix = new Matrix4f();

    updateMatrix();
}

Camera::~Camera(){
    if(posAt!=NULL){
        delete posAt;
    }
    if(lookAt!=NULL){
        delete lookAt;
    }
    if(upAt!=NULL){
        delete upAt;
    }

    if(forward!=NULL){
        delete forward;
    }
    if(side!=NULL){
        delete side;
    }
    if(up!=NULL){
        delete up;
    }

    if(matrix!=NULL){
        delete matrix;
    }
}

void Camera::updateMatrix()
{
    //---------------------------------
    //forward = lookAt - posAt (the direction you are looking)
    forward->set( lookAt->subtract( posAt ) );
    forward->normalizeSelf();
    //---------------------------------
    //side = forward x up - (a vector pointing to the side)
    side->set( forward->crossProduct( upAt ) );
    side->normalizeSelf();
    //---------------------------------
    //recompute up = side x forward (new up with the camera tilt)
    up->set( side->crossProduct( forward ) );
    //---------------------------------
    matrix->set( 0, side->getX() );
    matrix->set( 4, side->getY() );
    matrix->set( 8, side->getZ() );
    matrix->set(12, 0.0);
    //------------------
    matrix->set( 1, up->getX() );
    matrix->set( 5, up->getY() );
    matrix->set( 9, up->getZ() );
    matrix->set(13, 0.0);
    //------------------
    matrix->set( 2, -forward->getX() );
    matrix->set( 6, -forward->getY() );
    matrix->set(10, -forward->getZ() );
    matrix->set(14, 0.0);
    //------------------
    matrix->set( 3, 0.0);
    matrix->set( 7, 0.0);
    matrix->set(11, 0.0);
    matrix->set(15, 1.0);
    //------------------
}

void Camera::glApply(){
    glLoadIdentity();
    float matrix4f[16];
    matrix->get(matrix4f);
    glTranslatef(-posAt->getX(), -posAt->getY(), -posAt->getZ());
    glMultMatrixf(matrix4f);
}

void Camera::moveForward(float amount)
{
    Vector3f res;
    res.set( forward->realProduct( amount ) );
    posAt->addSelf( &res );
}

void Camera::moveSide(float amount)
{
    Vector3f res;
    res.set( side->realProduct( amount ) );
    posAt->addSelf( &res );
}

void Camera::moveUp(float amount)
{
    Vector3f res;
    res.set( up->realProduct( amount ) );
    posAt->addSelf( &res );
}
