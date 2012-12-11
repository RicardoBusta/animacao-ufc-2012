#ifndef JOINT_H
#define JOINT_H

#include <QVector3D>
#include <QQuaternion>
#include <QVector>
#include "object.h"

class Joint
{
public:
    Joint();

    QVector3D position;
    QQuaternion rotation;

    QVector<Joint*> child;

    Object *object;

    void draw();
};

#endif // JOINT_H
