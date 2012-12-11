#include "oriinterpolator.h"

OriInterpolator::OriInterpolator()
{
    type_ = kSlerp;
}

void OriInterpolator::SetStartFrame(int start_frame) {
    start_frame_ = start_frame;
}

void OriInterpolator::SetLastFrame(int last_frame) {
    last_frame_ = last_frame;
}

qglviewer::Quaternion OriInterpolator::GetOrientationAt(int frame) {

    int interval = ChooseInterval(frame);

    if((interval == -1) or (interval==steps_.size()-1)) return qglviewer::Quaternion();
    QuaternionInterpolator* interpolator = quaternions_curves_.at(interval);

    double t = ((double)(frame - steps_.at(interval).frame_))/((double)(steps_.at(interval+1).frame_ - steps_.at(interval).frame_));

    return interpolator->Evaluate(t);
}

int OriInterpolator::ChooseInterval(int frame) {
    int current = -1;
    for(size_t i = 0 ; i < steps_.size() ; i++ ) {
        if( steps_.at(i).frame_ <= frame)
            current = i;
        else
            break;
    }
    return current;
}

void OriInterpolator::SetInterpolationType(InterpolationType type) {
    type_ = type;
}

void OriInterpolator::GenerateMainCurve() {
    switch(type_) {
    case kBezier:
        GenerateBezierCurve();
        break;
    default:
        GenerateLinearCurve();
        break;
    }
}


void OriInterpolator::GenerateLinearCurve() {
    if(steps_.size() <= 1) return;

    for(size_t i = 0 ; i < steps_.size()-1 ; i++ ) {
        QuaternionInterpolator* interpolator = new SlerpQuaternion(steps_.at(i).orientation_,steps_.at(i+1).orientation_);
        quaternions_curves_.push_back(interpolator);
    }
}

void OriInterpolator::GenerateBezierCurve() {

}

void OriInterpolator::ClearAll() {
    steps_.clear();
    for(size_t i = 0 ; i < quaternions_curves_.size() ; i++ )
        delete quaternions_curves_.at(i);
    quaternions_curves_.clear();
}

void OriInterpolator::LoadOrientations(std::vector<OrientationStep>& steps) {
    ClearAll();

    for(size_t i = 0 ; i < steps.size() ; i++ )
        steps_.push_back(steps.at(i));

    GenerateMainCurve();
}

void OriInterpolator::AddOrientation(OrientationStep new_step) {

}
