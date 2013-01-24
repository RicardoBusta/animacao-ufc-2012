#include "link.h"
#include <QMatrix4x4>
#include <simple/simpledraw.h>
Link::Link()
{
    position_    = Vec4(0,0,0,1);
    orientation_ = Quaternion(1,0,0,0);
    length_      = 1.0;
    _pbase       = 5;
    _color       = Vec4(1,1,1);
}


Link::Link(int id)
{
    position_    = Vec4(0,0,0,1);
    orientation_ = Quaternion(1,0,0,0);
    length_      = 1.0;
    _pbase       = 5;
    _id          = id;
    _color       = Vec4(1,1,1);
}

void Link::objectDraw()
{
    double radius = 0.3*length_;
    double alpha  = 2*M_PI/_pbase;
    Vec4 vertexs[_pbase+1];
    for (int i=0;i<_pbase;i++){
        vertexs[i].setVec4(cos(alpha*i)*radius+position_.x1,position_.x2,sin(alpha*i)*radius+position_.x3);
    }
    vertexs[_pbase] = Vec4(position_.x1,position_.x2+length_,position_.x3);
    _posEffector = Vec4(position_.x1,position_.x2+length_,position_.x3);
    glColor3d(_color.x1,_color.x2,_color.x3);
    Vec4 normal;

    //glTranslated(position_.x1,position_.x2,position_.x3);
    glBegin(GL_POLYGON);
        normal = (vertexs[_pbase]*(-1)).unitary();
        glNormal3d(normal.x1,normal.x2,normal.x3);
        for (int i=0;i<_pbase;i++){
            glVertex3d(vertexs[i].x1,vertexs[i].x2,vertexs[i].x3);
        }
    glEnd();
    glBegin(GL_TRIANGLES);
        for (int i=0;i<_pbase;i++){
            if(i<_pbase-1){
                normal = Vec4::crossProduct(vertexs[i+1]-vertexs[i],vertexs[_pbase]-vertexs[i+1]).unitary();
                glNormal3d(normal.x1,normal.x2,normal.x3);
                glVertex3d(vertexs[i].x1,vertexs[i].x2,vertexs[i].x3);
                glVertex3d(vertexs[i+1].x1,vertexs[i+1].x2,vertexs[i+1].x3);
                glVertex3d(vertexs[_pbase].x1,vertexs[_pbase].x2,vertexs[_pbase].x3);
            }else{
                normal = Vec4::crossProduct(vertexs[0]-vertexs[i],vertexs[_pbase]-vertexs[0]).unitary();
                glNormal3d(normal.x1,normal.x2,normal.x3);
                glVertex3d(vertexs[i].x1,vertexs[i].x2,vertexs[i].x3);
                glVertex3d(vertexs[0].x1,vertexs[0].x2,vertexs[0].x3);
                glVertex3d(vertexs[_pbase].x1,vertexs[_pbase].x2,vertexs[_pbase].x3);
            }
        }
    glEnd();
}


void Link::draw()
{
    glPushMatrix();

    glTranslated(position_.x3,position_.x2,position_.x3);
    glMultMatrixd(orientation_.getMatrix().matrix);

    objectDraw();

    glPopMatrix();
//    glPushMatrix();
//    QMatrix4x4 mat;
//    Quaternion q;
//    glTranslated(0,0,0);
//    q = Quaternion::toRotation(orientation_);
//    mat.rotate(q.getScalar(),q.getPosX(),q.getPosY(),q.getPosZ());
//    //
//    //glTranslated(position_.x1,position_.x2,position_.x3);
//    glMultMatrixd(mat.data());
//    //glTranslated(0,0,0);
//    //desenhando o corpo
//    SimpleDraw::drawAxis(0.5);
//    //glTranslated(-position_.x1,-position_.x2,-position_.x3);




//    glPopMatrix();
}

void Link::applyOrientation(Vec4 axisAngle)
{
    Quaternion q;
    q.setQuaternion(axisAngle);
    q = q.normalize();
    //orientation_global = q*orientation_;
    orientation_ = orientation_*q;

    //q = q.toRotation(orientation_);
    //orientation_ = Quaternion(cos(M_PI_4),sin(M_PI_2),0,0);


}

void Link::setPosition(Vec4 pos)
{
    position_.setVec4(pos);
}

void Link::applyOrientationI(Vec4 axisAngle)
{
    Quaternion q;
    q.setQuaternion(axisAngle);
    q = q.normalize();
    orientation_ = orientation_*q.inverse();//(orientation_*q*orientation_.inverse()).normalize();


}

