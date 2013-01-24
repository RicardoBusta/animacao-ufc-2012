#ifndef MATRIX4F_H
#define MATRIX4F_H
#include "vec4.h"
class Matrix4f
{
public:
    double matrix[16];
public:
    Matrix4f();
    Matrix4f(double vet[16]);
    void setMatrix4f(double vet[16]);
    double* getMatrix();
    void showMatrix4f();
    void get(double output[]) const;
    void multMatrix2(Matrix4f a,Matrix4f b,double output[]);
    Matrix4f multMatrix(Matrix4f a,Matrix4f b);
    double get(int index) const;
    void translate(double x, double y, double z);
    void setTranslate(Vec4 vector);
    void translate( Vec4 vector );
    void setIdentity();
    Matrix4f transpose();
    Matrix4f inverse();
    Vec4 vector(Vec4 p);



};

#endif // MATRIX4F_H
