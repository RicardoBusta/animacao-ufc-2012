#ifndef ORIINTERPOLATOR_H
#define ORIINTERPOLATOR_H

#include <QGLViewer/quaternion.h>
#include "animation_step.h"

class OriInterpolator
{
public:
    OriInterpolator();

    void SetStartFrame(int start_frame);
    void SetLastFrame(int last_frame);

    qglviewer::Quaternion GetOrientationAt(int frame);

    void LoadOrientations(std::vector<OrientationStep>& steps);
    void AddOrientation(OrientationStep new_step);
private:
    int start_frame_, last_frame_;


};

#endif // ORIINTERPOLATOR_H
