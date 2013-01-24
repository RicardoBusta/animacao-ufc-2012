#ifndef QUATERNION_H
#define QUATERNION_H
#include "vec4.h"
#include "matrix4f.h"
class Quaternion
{
private:
    double s,x,y,z;
public:
    Quaternion();
    Quaternion(double r,double x, double y, double z);
    Quaternion(double x, double y, double z);
    Quaternion(double r, Vec4 v);
    //sets
    void setQuaternion(double r,double x, double y, double z);
    void setQuaternion(Vec4 AxisAngle);
    void setQuaternion(double r, Vec4 v);
    void setScalar(double s);
    void setPosX(double x);
    void setPosY(double y);
    void setPosZ(double z);
    //gets
    double getScalar(); //escalar
    double getPosX(); //coordenada x
    double getPosY(); //coordenada y
    double getPosZ(); //coordenada z
    Vec4 getVector();
    Quaternion getQuaternion();
    //fuctions
    Quaternion conjugate(); //conjugado do quaternion
    double normal(); //módulo
    Quaternion normalize(); // normalizacao
    Quaternion inverse();
    Vec4 toAxis();
    double toAngle();
    void toAxisAngle(Vec4 *axis, double *angle); //converter um quaternion para eixo e angulo
    void toEulerAngle(Vec4 *axis); //converter um quaternion para eixo e angulo
    void printQuaternion();
    Matrix4f getMatrix();
    static Quaternion toRotation(Quaternion q);
    static Quaternion fromRotation(Quaternion q);
    static Vec4 getVecRotation(Quaternion q,Vec4 v);
    //operadores
//    Quaternion operator +(Quaternion q);
//    Quaternion operator -(Quaternion q);
    Quaternion operator *(double k);
    Quaternion operator /(double k);
    //Quaternion operator *(Quaternion q);
    friend bool operator==(Quaternion p,Quaternion q);
    friend Quaternion operator+(Quaternion p,Quaternion q);
    friend Quaternion operator-(Quaternion p,Quaternion q);
    friend Quaternion operator*(Quaternion p,Quaternion q);
    friend Quaternion operator/(Quaternion p,Quaternion q);
    static double dot(Quaternion p, Quaternion q);

    static Quaternion Exp(Quaternion q);
    static Quaternion Exp(Quaternion q,double t);
    static Quaternion Log(Quaternion q);







}
;

#endif // QUATERNION_H
