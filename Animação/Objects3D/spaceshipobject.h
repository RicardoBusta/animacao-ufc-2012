#ifndef GLUTOBJECT_H
#define GLUTOBJECT_H

#include "object3d.h"
#include "GL/glu.h"

class SpaceShipObject : public Object3D
{
public:
    SpaceShipObject();
    virtual ~SpaceShipObject();

private:
    void drawObject();

};

#endif // GLUTOBJECT_H
