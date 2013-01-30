#ifndef IKTARGET_H
#define IKTARGET_H

#include "object3d.h"
#include "QGLViewer/vec.h"

#include <vector>

class IKTarget : public Object3D
{
public:
    static IKTarget* GetIKTargetById(int id);
    IKTarget(qglviewer::Vec pos);

    void setInverseUsable(bool use_inverse);
    void AddChildBone(Joint* bone);
    void SetDrawProperties(bool draw_effector, bool draw_bones);

    void Solve();
    void SaveKeyframe();
    void DrawGlobal();

protected:
    void drawObject(int depth);

    qglviewer::Vec goal_position_;

    std::vector<Joint*> bones_;

    bool inverse_;

    bool draw_effector_;
    bool draw_bones_;

private:
    static std::map<int,IKTarget*> ik_targets_;
};

#endif // IKTARGET_H
