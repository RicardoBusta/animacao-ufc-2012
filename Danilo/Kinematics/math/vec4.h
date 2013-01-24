#ifndef VEC4_H
#define VEC4_H
#include <stdio.h>
#include <math.h>
#include <QtOpenGL>
class Vec4
{
public:
    double x1,x2,x3,x4;
public:
    Vec4(double x=0.0,double y=0.0,double z=0.0,double w=1.0);
    void setVec4(Vec4 p);
    void setVec4(double x1=0.0,double x2=0.0,double x3=0.0,double x4=1.0);
    bool operator == (Vec4 v);
    bool operator != (Vec4 v);
    Vec4 operator + (Vec4 v);
    Vec4 operator - (Vec4 v);
    Vec4 operator / (double k);
    Vec4 operator * (double k);
    double operator * (Vec4 v);
    double module();
    Vec4 unitary();
    void showVec4();
    static Vec4 crossProduct(Vec4 a, Vec4 b);
    static double angle(Vec4 a,Vec4 b);
    static double distance(Vec4 a,Vec4 b);
    static double scalarProduct(Vec4 a,Vec4 b);
    void drawVec4(int length=1);
    static void drawLineVec4(Vec4 a,Vec4 b);

};


#endif // VEC4_H
