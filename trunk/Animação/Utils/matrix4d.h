#ifndef MATRIX4D_H
#define MATRIX4D_H

#include <QGLViewer/vec.h>
#include <QGLViewer/quaternion.h>

#include <Utils/genericmatrix.h>

class Matrix4D : public GenericMatrix
{
public:
    Matrix4D();
    Matrix4D(qglviewer::Vec translation);
    Matrix4D(qglviewer::Quaternion orientation);

    Matrix4D operator =(Matrix4D op);
    Matrix4D operator *(Matrix4D op);

    qglviewer::Vec apply(qglviewer::Vec op, bool vector);
};

#endif // MATRIX4D_H
