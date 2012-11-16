#ifndef SCENE_H
#define SCENE_H

#include "graphics/curve.h"

class Scene
{
public:
    Scene();
    ~Scene();  

    float rotx, roty;

    void draw();

    Curve curve;
};

#endif // SCENE_H
