#ifndef IKTARGET_H
#define IKTARGET_H

#include "object3d.h"
#include "QGLViewer/vec.h"

#include <vector>

class IKTarget : public Object3D
{
public:
    //static IKTarget* GetIKTargetById(int id);
    //IKTarget(qglviewer::Vec pos = qglviewer::Vec(0,0,0));
    IKTarget();

    //void setInverseUsable(bool use_inverse);
    void clear();
    void addChildBone(Joint* bone);
    //void SetDrawProperties(bool draw_effector, bool draw_bones);

    void solve();
    //void SaveKeyframe();
    void drawGlobal();

    bool goalReached();

protected:
    void drawObject(int depth);

    qglviewer::Vec goal_position_;

    std::vector<Joint*> bones_;

public:
    int inverse_;

    //bool draw_effector_;
    //bool draw_bones_;

private:
    //static std::map<int,IKTarget*> ik_targets_;
};

#endif // IKTARGET_H
