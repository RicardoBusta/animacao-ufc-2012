#ifndef SCENE_H
#define SCENE_H

#include <fileobj.h>

class Scene
{
public:
    Scene();
    ~Scene();  

    float rotx, roty;

    void draw();

    FileObj obj;
};

#endif // SCENE_H
