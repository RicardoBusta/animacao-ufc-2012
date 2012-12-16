#include "Interpolation/objectanimator.h"
#include "Objects3D/object3d.h"
#include "Interpolation/animation_step.h"
#include "Objects3D/trajectoryobject.h"

ObjectAnimator::ObjectAnimator(Object3D* child)
{
    child_object_ = child;
    original_position_    = child->position();
    original_orientation_ = child->orientation();
    update_positions_ = true;
    update_orientations_ = true;

    trajectory = NULL;
}

void ObjectAnimator::SetFrameRange(int start, int end) {
    pos_interpolator_.SetStartFrame(start);
    pos_interpolator_.SetLastFrame(end);
    ori_interpolator_.SetStartFrame(start);
    ori_interpolator_.SetLastFrame(end);
}

void ObjectAnimator::SetCurrentFrame(int frame) {
    PositionsUpdate();
    OrientationsUpdate();

    child_object_->SetNewPosition(pos_interpolator_.GetPositionAt(frame));
    child_object_->SetNewOrientation(ori_interpolator_.GetOrientationAt(frame));

}

qglviewer::Vec ObjectAnimator::PositionAt(int i) {
    PositionsUpdate();
    return pos_interpolator_.GetPositionAt(i);
}

qglviewer::Quaternion ObjectAnimator::OrientationAt(int i) {
    OrientationsUpdate();
    return ori_interpolator_.GetOrientationAt(i);
}

void ObjectAnimator::AddKeyPosition(int frame, qglviewer::Vec pos) {
    PositionStep key_frame(pos,frame);

    bool new_step = true;
    for(size_t i = 0 ; i < key_positions_.size() ; i++ ) {
        if(key_positions_.at(i).frame_ == key_frame.frame_) {
            key_positions_.at(i).position_ = key_frame.position_;
            new_step = false;
        }
    }

    if(new_step) key_positions_.push_back(key_frame);

    update_positions_ = true;
}

void ObjectAnimator::AddKeyOrientation(int frame, qglviewer::Quaternion ori) {
    OrientationStep key_frame(ori,frame);

    bool new_step = true;
    for(size_t i = 0 ; i < key_orientations_.size() ; i++ ) {
        if(key_orientations_.at(i).frame_ == key_frame.frame_) {
            key_orientations_.at(i).orientation_ = key_frame.orientation_;
            new_step = false;
        }
    }

    if(new_step) key_orientations_.push_back(key_frame);

    update_orientations_ = true;
}

void ObjectAnimator::AddKeyOrientation(int frame, float x, float y, float z)
{
    qglviewer::Quaternion qx = qglviewer::Quaternion( qglviewer::Vec(1,0,0), x );
    qglviewer::Quaternion qy = qglviewer::Quaternion( qglviewer::Vec(0,1,0), y );
    qglviewer::Quaternion qz = qglviewer::Quaternion( qglviewer::Vec(0,0,1), z );

    qglviewer::Quaternion qaux = (qy*qz);
    qglviewer::Quaternion q = (qx*q1);

    AddKeyOrientation( frame, q );
}

void ObjectAnimator::RemoveKeyPosition(int frame) {
    for(size_t i = 0 ; i < key_positions_.size() ; i++ ) {
        if(key_positions_.at(i).frame_ == frame) {
            key_positions_.erase(key_positions_.begin()+i);
            update_positions_ = true;
            return;
        }
    }
}

void ObjectAnimator::RemoveKeyOrientation(int frame) {
    for(size_t i = 0 ; i < key_orientations_.size() ; i++ ) {
        if(key_orientations_.at(i).frame_ == frame) {
            key_orientations_.erase(key_orientations_.begin()+i);
            update_orientations_ = true;
            return;
        }
    }
}

void ObjectAnimator::SetPosInterpolationType(PosInterpolator::InterpolationType type) {
    pos_interpolator_.SetInterpolationType(type);
    update_positions_ = true;
}

void ObjectAnimator::SetOriInterpolationType(OriInterpolator::InterpolationType type) {
    ori_interpolator_.SetInterpolationType(type);
    update_orientations_ = true;
}

void ObjectAnimator::CalculateTrajectory(TrajectoryObject::TrajectoryType type) {
    trajectory = new TrajectoryObject(this);
    trajectory->SetType(type);
    trajectory->Update();
}

Object3D* ObjectAnimator::GetTrajectory(){
    return trajectory;
}

void  ObjectAnimator::PositionsUpdate() {
    if(update_positions_) {
        pos_interpolator_.LoadPoints(key_positions_);
        update_positions_ = false;
    }
}

void  ObjectAnimator::OrientationsUpdate() {
    if(update_orientations_) {
        ori_interpolator_.LoadOrientations(key_orientations_);
        update_orientations_ = false;
    }
}


Object3D *ObjectAnimator::GetChild()
{
    return child_object_;
}


void ObjectAnimator::DeleteTrajectory()
{
    if(trajectory!=NULL){
        delete trajectory;
        trajectory = NULL;
    }
}
