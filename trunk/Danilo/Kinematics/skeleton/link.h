#ifndef LINK_H
#define LINK_H
#include "math/vec4.h"
#include "math/quaternion.h"

//link objeto que encontra-se entre dois joint ou entre um joint e o efetor final
class Link
{
public:
    Vec4       position_;
    Quaternion orientation_;
    int        _id;
    double     length_;
    Vec4       _posEffector;
    int        _pbase;
    Vec4       _color;
    double     mat[16];
    Quaternion orientation_global;

public:
    Link();
    Link(int id);
    void setPosition(Vec4 pos);
    void setOrientation(Vec4 axiAangle);
    void applyOrientation(Vec4 axisAngle);
    void applyOrientationI(Vec4 axisAngle);
    void objectDraw();
    void draw();
};

#endif // LINK_H
