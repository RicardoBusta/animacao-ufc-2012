#include "vec4.h"

Vec4::Vec4(double x1,double x2,double x3,double x4)
{
    this->x1 = x1;
    this->x2 = x2;
    this->x3 = x3;
    this->x4 = x4;
}

void Vec4::setVec4(Vec4 p){
    this->x1 = p.x1;
    this->x2 = p.x2;
    this->x3 = p.x3;
}

bool Vec4::operator == (Vec4 v){
    if ((this->x1==v.x1)&&(this->x2==v.x2)&&(this->x3==v.x3)){
        return true;
    }else{
        return false;
    }
}

bool Vec4::operator != (Vec4 v){
    if ((this->x1==v.x1)&&(this->x2==v.x2)&&(this->x3==v.x3)){
        return false;
    }else{
        return true;
    }
}

Vec4 Vec4::operator + (Vec4 v){
    Vec4 r;
    r.x1 = this->x1+v.x1;
    r.x2 = this->x2+v.x2;
    r.x3 = this->x3+v.x3;
    return r;
}

Vec4 Vec4::operator - (Vec4 v){
    Vec4 r;
    r.x1 = this->x1-v.x1;
    r.x2 = this->x2-v.x2;
    r.x3 = this->x3-v.x3;
    return r;
}

Vec4 Vec4::operator / (double k){
    Vec4 r;
    r.x1 = this->x1/k;
    r.x2 = this->x2/k;
    r.x3 = this->x3/k;
    return r;
}


Vec4 Vec4::operator * (double k){
    Vec4 r;
    r.x1 = this->x1*k;
    r.x2 = this->x2*k;
    r.x3 = this->x3*k;
    return r;
}


double Vec4::operator * (Vec4 v){
    return this->x1*v.x1+this->x2*v.x2+this->x3*v.x3;
}


void Vec4::setVec4(double x1,double x2, double x3, double x4){
    this->x1 = x1;
    this->x2 = x2;
    this->x3 = x3;
    this->x4 = x4;
}

double Vec4::module(){
    return sqrt(pow(x1,2)+pow(x2,2)+pow(x3,2));
}

Vec4 Vec4::unitary(){
    return *this/this->module();
}

void Vec4::showVec4(){
    printf("(%.4f;%.4f;%.4f)\n",x1,x2,x3);
}


double Vec4::scalarProduct(Vec4 a, Vec4 b){
    return (a.x1*b.x1+a.x2*b.x2+a.x3*b.x3);
}

double Vec4::angle(Vec4 a, Vec4 b){
    //retorna o ângulo real entre dois vetores
    return acos((a*b)/(a.module()*b.module()));
}



Vec4 Vec4::crossProduct(Vec4 a,Vec4 b){
    Vec4 r;
    r.x1 = a.x2*b.x3 - b.x2*a.x3;
    r.x2 = a.x3*b.x1 - b.x3*a.x1;
    r.x3 = a.x1*b.x2 - a.x2*b.x1;
    return r;
}

void Vec4::drawVec4(int length)
{
//    glBegin(GL_POINTS);
//        glVertex3f(x1,x2,x3);
//    glEnd();
    glPushMatrix();
    glTranslated(x1,x2,x3);
    GLUquadricObj *quadric;
    quadric = gluNewQuadric();
    gluSphere(quadric,0.005*length,20,20);
    glPopMatrix();
}

void Vec4::drawLineVec4(Vec4 a, Vec4 b)
{
    glBegin(GL_LINES);
        glVertex3f(a.x1,a.x2,a.x3);
        glVertex3f(b.x1,b.x2,b.x3);
    glEnd();
}

double Vec4::distance(Vec4 a,Vec4 b)
{
    Vec4 res;
    res.setVec4(a.x1-b.x1,a.x2-b.x2,a.x3-b.x3);
    return res.module();
}
