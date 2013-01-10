#include "posinterpolator.h"
#include "Curves/arclength.h"

PosInterpolator::PosInterpolator() : GenericInterpolator(),
    total_length_(0), start_frame_(0), last_frame_(0)
{
    interpolation_type_ = kLinear;
}

void PosInterpolator::SetInterpolationType(InterpolationType type) {
    interpolation_type_ = type;
}

void PosInterpolator::SetStartFrame(int start_frame) {
    start_frame_ = start_frame;
}

void PosInterpolator::SetLastFrame(int last_frame) {
    last_frame_ = last_frame;
}

qglviewer::Vec PosInterpolator::GetPositionAt(int frame, bool* valid) {

    if(frame<start_frame_ or frame>last_frame_){
        if(valid!=NULL) *valid = false;
        return qglviewer::Vec();
    }

    int interval = ChooseInterval(frame,PosInterpolator::kFrameBased);
    if(interval==-1 or interval==0){
        if(valid!=NULL) *valid = false;
        return qglviewer::Vec();
    }

    int interval_start_frame = steps_.at(interval -1).frame_;
    int interval_end_frame = steps_.at(interval).frame_;
    double current_step = (((double)(frame)) - ((double)(interval_start_frame)))/((double)(interval_end_frame - interval_start_frame));
    if(current_step>1.0) current_step = 1.0;

    current_step = speedControl(current_step);

    std::pair<Curve*,ArcLength*> curve_and_length = curves_.at(interval-1);
    if(valid!=NULL) *valid = true;
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
    switch(interpolation_type_) {
    case kBezier:
        GenerateBezierMainCurve();
        break;
    case kCatmullRoom:
        GenerateCatmullRoomMainCurve();
        break;
    default:
        GenerateLinearMainCurve();
    }

}

void PosInterpolator::GenerateCatmullRoomMainCurve() {
    if(steps_.size() <= 2) {
        GenerateLinearMainCurve();
        return;
    }

    qglviewer::Vec ta,tb,aux;
    qglviewer::Vec delta;
    for(size_t i = 0 ; i < steps_.size() ; i++) {
        if( i == 0 ) {
            ta = (steps_.at(2).position_*2.0 - steps_.at(1).position_  - steps_.at(0).position_)*(0.5);

        } else if( i ==  steps_.size() - 1 ) {
            /*delta = steps_.at(i-2).position_ - steps_.at(i-1).position_;
            aux = steps_.at(i-1).position_ + delta;
            tb = (aux - steps_.at(i-1).position_)*(0.5);*/
            tb = (steps_.at(i-1).position_*2.0 - steps_.at(i-2).position_ - steps_.at(i).position_)*(0.5);
            AddCurve(new Hermite(steps_.at(i-1).position_,ta,steps_.at(i).position_,tb));
        }else {
            tb = (steps_.at(i+1).position_ - steps_.at(i-1).position_)*(0.5);
            AddCurve(new Hermite(steps_.at(i-1).position_,ta,steps_.at(i).position_,tb));
            ta = tb;

        }
    }
}

void PosInterpolator::GenerateBezierMainCurve() {
    if(steps_.size() <= 2) {
        GenerateLinearMainCurve();
        return;
    }
    qglviewer::Vec a,b,pa;
    qglviewer::Vec delta;
    for(size_t i = 0 ; i < steps_.size() ; i++) {
        if( i == 0 ) {
            delta = steps_.at(1).position_ - steps_.at(2).position_;
            pa = steps_.at(1).position_ + delta;
        } else if( i ==  steps_.size() - 1 ) {
            delta = steps_.at(i-1).position_ - steps_.at(i-2).position_;
            b = steps_.at(i-1).position_ + delta;
            //curves.push_back(new BezierCubic(points.at(i-1),pa,b,points.at(i)));
            AddCurve(new BezierQuadratic(steps_.at(i-1).position_,pa,steps_.at(i).position_));
        }else {
            delta = steps_.at(i).position_ - steps_.at(i-1).position_;
            a = steps_.at(i).position_ + delta;
            a = (a + steps_.at(i+1).position_)/2.0;
            delta = steps_.at(i).position_ - a;
            b = steps_.at(i).position_ + delta;
            if( i == 1) {
                AddCurve(new BezierQuadratic(steps_.at(i-1).position_,b,steps_.at(i).position_));
            }else{
                AddCurve(new BezierCubic(steps_.at(i-1).position_,pa,b,steps_.at(i).position_));
            }
            pa = a;

        }
    }
}

void PosInterpolator::GenerateLinearMainCurve() {
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
