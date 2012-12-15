#ifndef OBJECTANIMATOR_H
#define OBJECTANIMATOR_H

#include "Interpolation/oriinterpolator.h"
#include "Interpolation/posinterpolator.h"
#include "Objects3D/trajectoryobject.h"

class Object3D;


class ObjectAnimator
{
public:
    ObjectAnimator(Object3D* child);

    //! Frame Controls
    void SetFrameRange          (int start, int end);
    void SetCurrentFrame        (int frame);            //!  Animate the object

    //! Object acess information
    qglviewer::Vec PositionAt           (int frame);
    qglviewer::Quaternion OrientationAt (int frame);

    //! Animation steps controls
    void AddKeyPosition         (int frame, qglviewer::Vec pos);
    void AddKeyOrientation      (int frame, qglviewer::Quaternion pos);
    void RemoveKeyPosition      (int frame);
    void RemoveKeyOrientation   (int frame);

    //! Animation Controls
    void SetPosInterpolationType   (PosInterpolator::InterpolationType type);
    void SetOriInterpolationType   (OriInterpolator::InterpolationType type);

    //! Trajectory options
    Object3D* GetTrajectory     (TrajectoryObject::TrajectoryType type);

private:
    void PositionsUpdate();
    void OrientationsUpdate();

    bool update_positions_;
    bool update_orientations_;
    std::vector<PositionStep> key_positions_;
    std::vector<OrientationStep> key_orientations_;
    bool *pre_calculed_;

    Object3D* child_object_;
    OriInterpolator ori_interpolator_;
    PosInterpolator pos_interpolator_;

    qglviewer::Vec original_position_;
    qglviewer::Quaternion original_orientation_;
};

#endif // OBJECTANIMATOR_H
