#include "Interpolation/objectanimator.h"
#include "Objects3D/object3d.h"
#include "Interpolation/animation_step.h"
#include "Objects3D/trajectoryobject.h"
#include "Utils/scenecontainer.h"

ObjectAnimator::ObjectAnimator(Object3D* child)
{
    child_object_ = child;
    child->SetAnimator(this);
    original_position_    = child->position();
    original_orientation_ = child->orientation();
    update_positions_ = true;
    update_orientations_ = true;

    oriTrajectory = NULL;
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

    if(SceneContainer::AnimatePosition()) {
        bool is_valid;
        qglviewer::Vec pos = pos_interpolator_.GetPositionAt(frame,&is_valid);
        child_object_->SetNewPosition(is_valid? pos : child_object_->position());
    }

    if(SceneContainer::AnimateOrientation()) {
        bool is_valid;
        qglviewer::Quaternion ori = ori_interpolator_.GetOrientationAt(frame,&is_valid);
        child_object_->SetNewOrientation(is_valid? ori : child_object_->orientation());
    }

}

qglviewer::Vec ObjectAnimator::PositionAt(int i) {
    PositionsUpdate();
    bool is_valid;
    qglviewer::Vec pos = pos_interpolator_.GetPositionAt(i,&is_valid);
    return is_valid? pos : child_object_->position();
}

qglviewer::Quaternion ObjectAnimator::OrientationAt(int i) {
    OrientationsUpdate();
    bool is_valid;
    qglviewer::Quaternion ori = ori_interpolator_.GetOrientationAt(i,&is_valid);
    return is_valid? ori : child_object_->orientation();
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
    qglviewer::Quaternion q = (qx*qaux);

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
    oriTrajectory = new TrajectoryObject(this);
    oriTrajectory->SetType(type);
    oriTrajectory->Update();
}

Object3D* ObjectAnimator::GetTrajectory(){
    return oriTrajectory;
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

void ObjectAnimator::SetParent(ObjectAnimator* parent) {
    parent_ = parent;
}

ObjectAnimator* ObjectAnimator::Parent() {
    return parent_;
}

Object3D* ObjectAnimator::GetChild()
{
    return child_object_;
}


void ObjectAnimator::DeleteTrajectory()
{
    if(oriTrajectory!=NULL){
        delete oriTrajectory;
        oriTrajectory = NULL;
    }
}


std::vector<PositionStep> *ObjectAnimator::GetKeyPositions()
{
    return &key_positions_;
}


std::vector<OrientationStep> *ObjectAnimator::GetKeyOrientations()
{
    return &key_orientations_;
}
