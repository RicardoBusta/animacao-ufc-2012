#ifndef SCENE_H
#define SCENE_H

class Camera;
class Material;
class Curve;
class Vector3f;

#include <vector>
#include <math/matrix4f.h>

class Scene
{
public:
    Scene();
    ~Scene();  

    float rotx, roty;
    Matrix4f transform;

    void draw();

    std::vector<Vector3f*> points;
    std::vector<Vector3f*> curve;

    void calculateCurve();

    void clearCurve();
    void genBezier();
};

#endif // SCENE_H
