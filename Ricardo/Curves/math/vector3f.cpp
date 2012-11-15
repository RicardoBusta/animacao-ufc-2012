#include "vector3f.h"

#include <cmath>

#include "math/matrix4f.h"

Vector3f::Vector3f(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3f::Vector3f(const Vector3f& vec)
{
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
}


Vector3f::~Vector3f()
{
}

void Vector3f::normalizeSelf()
{
    float d = sqrt(x*x + y*y + z*z);
    if(d!=0){
        this->x/=d;
        this->y/=d;
        this->z/=d;
    }
}

void Vector3f::setX(float x)
{
    this->x = x;
}

void Vector3f::setY(float y)
{
    this->y = y;
}

void Vector3f::setZ(float z)
{
    this->z = z;
}

float Vector3f::getX() const
{
    return x;
}

float Vector3f::getY() const
{
    return y;
}

float Vector3f::getZ() const
{
    return z;
}

void Vector3f::set(Vector3f op){
    this->x = op.x;
    this->y = op.y;
    this->z = op.z;
}

void Vector3f::crossProductSelf(Vector3f *op)
{
    float x=this->x;
    float y=this->y;

    this->x = (y * op->z) - (this->z * op->y);
    this->y = (this->z * op->x) - (x * op->z);
    this->z = (x * op->y) - (y * op->x);
}

void Vector3f::realProductSelf(float op)
{
    this->x *= op;
    this->y *= op;
    this->z *= op;
}

void Vector3f::subtractSelf(Vector3f *op)
{
    this->x -= op->x;
    this->y -= op->y;
    this->z -= op->z;
}

void Vector3f::addSelf(Vector3f *op)
{
    this->x += op->x;
    this->y += op->y;
    this->z += op->z;
}

void Vector3f::transformSelf(Matrix4f *m)
{
    float r[3];

    for(int i=0;i<3;i++){
        r[i] = ( this->x * m->get( 0+(i*4) ) ) + ( this->y * m->get( 1+(i*4) ) ) + ( this->y * m->get( 2+(i*4) ) );
    }

    this->x = r[0];
    this->y = r[1];
    this->z = r[2];
}

Vector3f Vector3f::crossProduct(Vector3f *op) const
{
    Vector3f result;
    result.x = (this->y * op->z) - (this->z * op->y);
    result.y = (this->z * op->x) - (this->x * op->z);
    result.z = (this->x * op->y) - (this->y * op->x);
    return result;
}

Vector3f Vector3f::realProduct(float op) const
{
    Vector3f result;
    result.x = this->x*op;
    result.y = this->y*op;
    result.z = this->z*op;
    return result;
}

Vector3f Vector3f::subtract(Vector3f *op) const
{
    Vector3f result;
    result.x = ( this->x - op->x );
    result.y = ( this->y - op->y );
    result.z = ( this->z - op->z );
    return result;
}

Vector3f Vector3f::add(Vector3f *op) const
{
    Vector3f result;
    result.x = ( this->x + op->x );
    result.y = ( this->y + op->y );
    result.z = ( this->z + op->z );
    return result;
}

float Vector3f::dotProduct(Vector3f *op) const
{
    return ( x*op->x + y*op->y + z*op->z );
}

Vector3f Vector3f::operator=(Vector3f v)
{
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;

    return *this;
}

#ifdef DEBUG_MODE
#include <iostream>
using namespace std;

void Vector3f::stdPrint() const{
    cout << "x: " << this->x << " y: " << this->y << " z: " << this->z << endl;
}
#endif
