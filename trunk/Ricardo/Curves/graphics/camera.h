#ifndef CAMERA_H
#define CAMERA_H

class Vector3f;
class Matrix4f;

class Camera
{
public:
    Camera();
    ~Camera();

    void glApply();
    void updateMatrix();

    void moveForward(float amount);
    void moveSide(float amount);
    void moveUp(float amount);
private:
    //Control points
    Vector3f *posAt;
    Vector3f *lookAt;
    Vector3f *upAt;

    //Reference points
    Vector3f *forward;
    Vector3f *side;
    Vector3f *up;

    //Data
    Matrix4f *matrix;
};

#endif // CAMERA_H
