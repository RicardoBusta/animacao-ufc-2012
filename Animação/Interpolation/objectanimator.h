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
    void setFrameRange          (int start, int end);
    void setCurrentFrame        (int frame);            //!  Animate the object

    //! Object acess information
    qglviewer::Vec positionAt           (int frame);
    qglviewer::Quaternion orientationAt (int frame);

    std::vector<PositionStep> *getKeyPositions          ();
    std::vector<OrientationStep> *getKeyOrientations    ();

    //! Main Hierarchy
    void            setParent(ObjectAnimator* parent);
    ObjectAnimator* parent();
    Object3D*       getChild();

    //! Animation steps controls
    void addKeyPosition         (int frame, qglviewer::Vec pos);
    void addKeyOrientation      (int frame, qglviewer::Quaternion pos);
    void addKeyOrientation      (int frame, float x, float y, float z); //! Euler Angles / Z then Y then X
    void removeKeyPosition      (int frame);
    void removeKeyOrientation   (int frame);

    //! Animation Controls
    void setPosInterpolationType   (PosInterpolator::InterpolationType type);
    void setOriInterpolationType   (OriInterpolator::InterpolationType type);

    //! Trajectory options
    void calculateTrajectory    (TrajectoryObject::TrajectoryType type);
    Object3D* getTrajectory     ();

    void deleteTrajectory();

private:
    void positionsUpdate();
    void orientationsUpdate();

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
