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

    qglviewer::Vec GetOrientationAt(int frame);

    void LoadOrientations(std::vector<OrientationStep>& steps);
    void AddOrientation(OrientationStep new_step);

};

#endif // ORIINTERPOLATOR_H
