#include "Interpolation/objectanimator.h"
#include "Objects3D/object3d.h"
#include "Interpolation/animation_step.h"
#include "Objects3D/trajectoryobject.h"
#include "Utils/scenecontainer.h"

ObjectAnimator::ObjectAnimator(Object3D* child)
{
    child_object_ = child;
    child->setAnimator(this);
    original_position_    = child->position();
    original_orientation_ = child->orientation();
    update_positions_ = true;
    update_orientations_ = true;

    oriTrajectory = NULL;
}

void ObjectAnimator::setFrameRange(int start, int end) {
    pos_interpolator_.setStartFrame(start);
    pos_interpolator_.setLastFrame(end);
    ori_interpolator_.setStartFrame(start);
    ori_interpolator_.setLastFrame(end);
}

void ObjectAnimator::setCurrentFrame(int frame) {
    positionsUpdate();
    orientationsUpdate();

    if(SceneContainer::animatePosition()) {
        bool is_valid;
        qglviewer::Vec pos = pos_interpolator_.getPositionAt(frame,&is_valid);
        child_object_->setNewPosition(is_valid? pos : child_object_->position());
    }

    if(SceneContainer::animateOrientation()) {
        bool is_valid;
        qglviewer::Quaternion ori = ori_interpolator_.GetOrientationAt(frame,&is_valid);
        child_object_->setNewOrientation(is_valid? ori : child_object_->orientation());
    }

}

qglviewer::Vec ObjectAnimator::positionAt(int frame) {
    positionsUpdate();
    bool is_valid;
    qglviewer::Vec pos = pos_interpolator_.getPositionAt(frame,&is_valid);
    return is_valid && SceneContainer::animatePosition()? pos : child_object_->position();
}

qglviewer::Quaternion ObjectAnimator::orientationAt(int frame) {
    orientationsUpdate();
    bool is_valid;
    qglviewer::Quaternion ori = ori_interpolator_.GetOrientationAt(frame,&is_valid);
    return is_valid && SceneContainer::animatePosition()? ori : child_object_->orientation();
}

void ObjectAnimator::addKeyPosition(int frame, qglviewer::Vec pos) {
    PositionStep key_frame(pos,frame);

    bool new_step = true;
    for(unsigned int i = 0 ; i < key_positions_.size() ; i++ ) {
        if(key_positions_.at(i).frame_ == key_frame.frame_) {
            key_positions_.at(i).position_ = key_frame.position_;
            new_step = false;
        }
    }

    if(new_step){
        if(key_positions_.size() == 0)
            key_positions_.push_back(key_frame);
        else for(unsigned int i = 0 ; i < key_positions_.size() ; i++ ) {
            if(key_positions_.at(i).frame_ > key_frame.frame_ ) {
                key_positions_.insert(key_positions_.begin()+i,key_frame);
                break;
            }else if(i == key_positions_.size()-1){
                key_positions_.push_back(key_frame);
                break;
            }
        }
    }

    update_positions_ = true;
}

void ObjectAnimator::addKeyOrientation(int frame, qglviewer::Quaternion ori) {
    OrientationStep key_frame(ori,frame);

    bool new_step = true;
    for(unsigned int i = 0 ; i < key_orientations_.size() ; i++ ) {
        if(key_orientations_.at(i).frame_ == key_frame.frame_) {
            key_orientations_.at(i).orientation_ = key_frame.orientation_;
            new_step = false;
        }
    }

    if(new_step){
        if(key_orientations_.size() == 0)
            key_orientations_.push_back(key_frame);
        else for(unsigned int i = 0 ; i < key_orientations_.size() ; i++ ) {
            if(key_orientations_.at(i).frame_ > key_frame.frame_ ) {
                key_orientations_.insert(key_orientations_.begin()+i,key_frame);
                break;
            }else if(i == key_orientations_.size()-1){
                key_orientations_.push_back(key_frame);
                break;
            }
        }
    }

    update_orientations_ = true;
}

void ObjectAnimator::addKeyOrientation(int frame, float x, float y, float z)
{
    qglviewer::Quaternion qx = qglviewer::Quaternion( qglviewer::Vec(1,0,0), x );
    qglviewer::Quaternion qy = qglviewer::Quaternion( qglviewer::Vec(0,1,0), y );
    qglviewer::Quaternion qz = qglviewer::Quaternion( qglviewer::Vec(0,0,1), z );

    qglviewer::Quaternion qaux = (qy*qz);
    qglviewer::Quaternion q = (qx*qaux);

    addKeyOrientation( frame, q );
}

void ObjectAnimator::removeKeyPosition(int frame) {
    for(size_t i = 0 ; i < key_positions_.size() ; i++ ) {
        if(key_positions_.at(i).frame_ == frame) {
            key_positions_.erase(key_positions_.begin()+i);
            update_positions_ = true;
            return;
        }
    }
}

void ObjectAnimator::removeKeyOrientation(int frame) {
    for(size_t i = 0 ; i < key_orientations_.size() ; i++ ) {
        if(key_orientations_.at(i).frame_ == frame) {
            key_orientations_.erase(key_orientations_.begin()+i);
            update_orientations_ = true;
            return;
        }
    }
}

void ObjectAnimator::setPosInterpolationType(PosInterpolator::InterpolationType type) {
    pos_interpolator_.setInterpolationType(type);
    update_positions_ = true;
}

void ObjectAnimator::setOriInterpolationType(OriInterpolator::InterpolationType type) {
    ori_interpolator_.setInterpolationType(type);
    update_orientations_ = true;
}

void ObjectAnimator::calculateTrajectory(TrajectoryObject::TrajectoryType type) {
    oriTrajectory = new TrajectoryObject(this);
    oriTrajectory->setType(type);
    oriTrajectory->update();
}

Object3D* ObjectAnimator::getTrajectory(){
    return oriTrajectory;
}

void  ObjectAnimator::positionsUpdate() {
    if(update_positions_) {
        pos_interpolator_.loadPoints(key_positions_);
        update_positions_ = false;
    }
}

void  ObjectAnimator::orientationsUpdate() {
    if(update_orientations_) {
        ori_interpolator_.loadOrientations(key_orientations_);
        update_orientations_ = false;
    }
}

void ObjectAnimator::setParent(ObjectAnimator* parent) {
    parent_ = parent;
}

ObjectAnimator* ObjectAnimator::parent() {
    return parent_;
}

Object3D* ObjectAnimator::getChild()
{
    return child_object_;
}


void ObjectAnimator::deleteTrajectory()
{
    if(oriTrajectory!=NULL){
        delete oriTrajectory;
        oriTrajectory = NULL;
    }
}


std::vector<PositionStep> *ObjectAnimator::getKeyPositions()
{
    return &key_positions_;
}


std::vector<OrientationStep> *ObjectAnimator::getKeyOrientations()
{
    return &key_orientations_;
}
