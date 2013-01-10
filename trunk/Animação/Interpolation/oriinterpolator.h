#ifndef ORIINTERPOLATOR_H
#define ORIINTERPOLATOR_H

#include <QGLViewer/quaternion.h>
#include "quaternioninterpolation.h"
#include "animation_step.h"
#include "genericinterpolator.h"

class OriInterpolator : public GenericInterpolator
{
public:
    enum InterpolationType {kSlerp,kBezier};
    OriInterpolator();

    void SetStartFrame(int start_frame);
    void SetLastFrame(int last_frame);

    qglviewer::Quaternion GetOrientationAt(int frame, bool *valid = NULL);

    void LoadOrientations(std::vector<OrientationStep>& steps);
    void AddOrientation(OrientationStep new_step);

    void SetInterpolationType(InterpolationType type);
protected:
    void GenerateMainCurve();
    void GenerateLinearCurve();
    void GenerateBezierCurve();
    void ClearAll();

    int ChooseInterval(int frame);

    qglviewer::Quaternion Bisect(qglviewer::Quaternion a, qglviewer::Quaternion b);
    qglviewer::Quaternion Double(qglviewer::Quaternion a, qglviewer::Quaternion b);


private:
    int start_frame_, last_frame_;
    InterpolationType type_;
    std::vector<OrientationStep> steps_;
    std::vector<QuaternionInterpolator*> quaternions_curves_;


};

#endif // ORIINTERPOLATOR_H
