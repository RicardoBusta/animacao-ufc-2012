#ifndef MATRIX4D_H
#define MATRIX4D_H

#include <QGLViewer/vec.h>
#include <QGLViewer/quaternion.h>

#include <vector>

class Matrix4D
{
public:
    std::vector<double> data_;

    Matrix4D();
    Matrix4D(qglviewer::Vec translation);
    Matrix4D(qglviewer::Quaternion orientation);

    virtual ~Matrix4D();

    Matrix4D operator =(Matrix4D op);
    Matrix4D operator *(Matrix4D op);

    qglviewer::Vec apply(qglviewer::Vec op, bool vector);
};

#endif // MATRIX4D_H
