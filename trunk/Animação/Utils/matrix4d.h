#ifndef MATRIX4D_H
#define MATRIX4D_H

#include <QGLViewer/vec.h>
#include <QGLViewer/quaternion.h>

#include <Utils/genericmatrix.h>

namespace Matrix4D
{
    GenericMatrix generate();
    GenericMatrix generate(qglviewer::Vec translation);
    GenericMatrix generate(qglviewer::Quaternion orientation);

    qglviewer::Vec apply(GenericMatrix matrix, qglviewer::Vec op, bool vector);
}

#endif // MATRIX4D_H
