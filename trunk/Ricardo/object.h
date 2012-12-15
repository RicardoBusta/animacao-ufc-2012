#ifndef OBJECT_H
#define OBJECT_H

#include <QQuaternion>
#include <QVector3D>

class Object
{
public:
    Object();

    QVector3D position;
    QQuaternion rotation;

    void draw();
};

#endif // OBJECT_H
