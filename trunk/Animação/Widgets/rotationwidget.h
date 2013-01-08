#ifndef ROTATIONWIDGET_H
#define ROTATIONWIDGET_H

#include "Objects3D/object3d.h"

class RotationWidget : public Object3D
{
public:
    RotationWidget(Object3D* to_rotate);
    ~RotationWidget();

    void SetClick(qglviewer::Vec click_position);

private:
    void DrawCircle(double radius, qglviewer::Quaternion ori, int steps);
    void DrawObject();

    Object3D* to_rotate_;

    double radius_;
    int current_click_;
    qglviewer::Vec first_click_;
    qglviewer::Vec last_click_;
    qglviewer::Quaternion current_quaternion_;

    GLUquadric* quadric_;
};

#endif // ROTATIONWIDGET_H
