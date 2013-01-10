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

    std::vector<PositionStep> *GetKeyPositions          ();
    std::vector<OrientationStep> *GetKeyOrientations    ();

    //! Main Hierarchy
    void            SetParent(ObjectAnimator* parent);
    ObjectAnimator* Parent();
    Object3D*       GetChild();

    //! Animation steps controls
    void AddKeyPosition         (int frame, qglviewer::Vec pos);
    void AddKeyOrientation      (int frame, qglviewer::Quaternion pos);
    void AddKeyOrientation      (int frame, float x, float y, float z); //! Euler Angles / Z then Y then X
    void RemoveKeyPosition      (int frame);
    void RemoveKeyOrientation   (int frame);

    //! Animation Controls
    void SetPosInterpolationType   (PosInterpolator::InterpolationType type);
    void SetOriInterpolationType   (OriInterpolator::InterpolationType type);

    //! Trajectory options
    void CalculateTrajectory    (TrajectoryObject::TrajectoryType type);
    Object3D* GetTrajectory     ();

    void DeleteTrajectory();

private:
    void PositionsUpdate();
    void OrientationsUpdate();

    bool update_positions_;
    bool update_orientations_;
    std::vector<PositionStep> key_positions_;
    std::vector<OrientationStep> key_orientations_;
    bool *pre_calculed_;

    ObjectAnimator* parent_;
    Object3D* child_object_;
    OriInterpolator ori_interpolator_;
    PosInterpolator pos_interpolator_;

    qglviewer::Vec original_position_;
    qglviewer::Quaternion original_orientation_;

    TrajectoryObject *oriTrajectory;
};

#endif // OBJECTANIMATOR_H
