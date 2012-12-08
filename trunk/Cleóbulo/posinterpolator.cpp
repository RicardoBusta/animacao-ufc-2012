#include "posinterpolator.h"
#include "arclength.h"

PosInterpolator::PosInterpolator() :
    total_length_(0), start_frame_(0), last_frame_(0)
{
}

void PosInterpolator::SetStartFrame(int start_frame) {
    start_frame_ = start_frame;
}

void PosInterpolator::SetLastFrame(int last_frame) {
    last_frame_ = last_frame;
}

qglviewer::Vec PosInterpolator::GetPositionAt(int frame) {

    if(frame<start_frame_ or frame>last_frame_) return qglviewer::Vec();

    int interval = ChooseInterval(frame,PosInterpolator::kFrameBased);
    if(interval==-1 or interval==0)return qglviewer::Vec();

    int interval_start_frame = steps_.at(interval -1).frame_;
    int interval_end_frame = steps_.at(interval).frame_;
    double current_step = (((double)(frame)) - ((double)(interval_start_frame)))/((double)(interval_end_frame - interval_start_frame));
    if(current_step>1.0) current_step = 1.0;

    std::pair<Curve*,ArcLength*> curve_and_length = curves_.at(interval-1);
    return curve_and_length.second->GetByNormalizedS(current_step);
}

int PosInterpolator::ChooseInterval(int frame, InterpolationPolicy policy ) {
    if(PosInterpolator::kConstantSpeed == policy) {
        double length = (((double)(frame)) - ((double)(start_frame_)))/((double)(last_frame_ - start_frame_));
        double real_length = length * total_length_;

        int interval = -1;
        for( size_t i = 0 ; i < curves_lengths_.size() ; i++ ) {
            interval = i;
            if(curves_lengths_.at(i) > real_length) {
                return i;
            }
        }
        return interval;
    }else if(PosInterpolator::kFrameBased == policy){
        for(size_t i = 1 ; i < steps_.size() ; i++ ){
            if(steps_.at(i).frame_ > frame)
                return i;
        }
        return steps_.size()-1;
    }

    return -1; // Unhandled case

}

void PosInterpolator::LoadPoints(std::vector<PositionStep>& steps) {
    steps_.clear();
    for(size_t i = 0 ; i < steps.size() ; i++ )
        steps_.push_back(steps.at(i));

    CleanCurvesAndLengths();
    GenerateMainCurve();
}

void PosInterpolator::AddPoint(PositionStep new_step) {
    bool recreate = false;
    for(size_t i = 0 ; i < steps_.size() ; i++ ) {
        if(steps_.at(i).frame_ > new_step.frame_) {
            steps_.insert(steps_.begin() + i, new_step);
            recreate = true;
            break;
        }else if(steps_.at(i).frame_ == new_step.frame_)
            break;
    }

    if(recreate) {
        CleanCurvesAndLengths();
        GenerateMainCurve();
    }
}

void PosInterpolator::GenerateMainCurve() {
    for(size_t i = 1 ; i < steps_.size() ; i++ ) {
        Curve* curve = new LinearCurve(steps_.at(i-1).position_,steps_.at(i).position_);
        AddCurve(curve);
    }
}

void PosInterpolator::AddCurve(Curve* curve) {
    std::pair<Curve*,ArcLength*> curve_and_length;
    ArcLength* arc_length = new ArcLength(curve);

    arc_length->AdaptativeGaussianPrecalculation();

    curve_and_length.first = curve;
    curve_and_length.second = arc_length;

    curves_.push_back(curve_and_length);

    double total_length = arc_length->GetTotalLength();
    total_length_ += total_length;

    if(curves_lengths_.size() > 0)
        total_length += curves_lengths_.at(curves_lengths_.size()-1);

    curves_lengths_.push_back(total_length);
}

void PosInterpolator::CleanCurvesAndLengths() {
    for(size_t i = 0 ; i < curves_.size() ; i++ ) {
        std::pair<Curve*,ArcLength*> curve_and_length = curves_.at(i);
        delete curve_and_length.first;
        delete curve_and_length.second;
    }
    curves_.clear();
    curves_lengths_.clear();
    total_length_ = 0.0;
}
