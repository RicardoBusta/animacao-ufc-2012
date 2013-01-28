#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <QGLViewer/vec.h>
#include <QGLViewer/quaternion.h>
#include <GL/glu.h>
#include <map>

class ObjectAnimator;
class Joint;

class Object3D {
public:
    static Object3D* getObjectByID(int id);

    float length_;

    Object3D();
    Object3D(qglviewer::Vec pos);
    Object3D(qglviewer::Quaternion ori);
    Object3D(qglviewer::Vec pos, qglviewer::Quaternion ori);
    virtual ~Object3D();

    std::string                    label();
    void                           setLabel(std::string label);

    int                            id();
    inline void                    setDrawObject          (bool draw) { draw_object_ = draw; }
    inline void                    setDrawPositionParticle(bool draw) { draw_position_particle_ = draw; }
    inline void                    setDrawOrientationAxes (bool draw) { draw_orientation_axes_  = draw; }
    inline void                    setDrawBoundingBox     (bool draw) { draw_bounding_box_ = draw; }

    inline void                    setNewPosition(qglviewer::Vec position) { position_ = position; }
    inline void                    setNewOrientation(qglviewer::Quaternion orientation) { orientation_ = orientation; }
    inline qglviewer::Vec          position()    { return position_; }
    inline qglviewer::Quaternion   orientation() { return orientation_; }

    void                           draw(int depth);
    void                           glTransform();

    void                           setAnimator(ObjectAnimator* animator);
    ObjectAnimator*                getAnimator();
protected:

    void                           defaultInitialisation();
    void                           drawPositionParticle();
    void                           drawOrientationAxes();
    virtual void                   drawObject(int);
    virtual void                   drawBoundingBox();
    virtual void                   drawBoxObject();
    virtual void                   drawBone(int depth);
    friend class Joint;

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

    static std::map<int,Object3D*> object_reference_;
};



#endif // OBJECT3D_H
