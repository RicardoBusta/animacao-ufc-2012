#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <QGLViewer/vec.h>
#include <QGLViewer/quaternion.h>
#include <GL/glu.h>

class ObjectAnimator;

class Object3D {
public:
    Object3D();
    Object3D(qglviewer::Vec pos);
    Object3D(qglviewer::Quaternion ori);
    Object3D(qglviewer::Vec pos, qglviewer::Quaternion ori);
    ~Object3D();

    std::string                    label();
    void                           SetLabel(std::string label);

    int                            id();
    inline void                    SetDrawObject          (bool draw) { draw_object_ = draw; }
    inline void                    SetDrawPositionParticle(bool draw) { draw_position_particle_ = draw; }
    inline void                    SetDrawOrientationAxes (bool draw) { draw_orientation_axes_  = draw; }

    inline void                    SetNewPosition(qglviewer::Vec position) { position_ = position; }
    inline void                    SetNewOrientation(qglviewer::Quaternion orientation) { orientation_ = orientation; }
    inline qglviewer::Vec          position()    { return position_; }
    inline qglviewer::Quaternion   orientation() { return orientation_; }

    void                           Draw();

    void                           SetAnimator(ObjectAnimator *animator);
    ObjectAnimator*                GetAnimator();
protected:

    void                           DefaultInitialisation();
    void                           DrawPositionParticle();
    void                           DrawOrientationAxes();
    virtual void                   DrawObject();
    virtual void                   DrawBoundingBox();

    std::string label_;
    bool draw_object_;
    bool draw_position_particle_;
    bool draw_orientation_axes_;
    bool draw_bounding_box_;
    qglviewer::Vec bounding_box_max_;
    qglviewer::Vec bounding_box_min_;
    qglviewer::Vec color_;
    qglviewer::Vec position_;
    qglviewer::Quaternion orientation_;
private:
    GLUquadricObj* quadric_;
    int id_;

    ObjectAnimator *animator;
};



#endif // OBJECT3D_H
