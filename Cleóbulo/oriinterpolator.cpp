#include "oriinterpolator.h"

OriInterpolator::OriInterpolator()
{
}

void OriInterpolator::SetStartFrame(int start_frame) {
    start_frame_ = start_frame;
}

void OriInterpolator::SetLastFrame(int last_frame) {
    last_frame_ = last_frame;
}

qglviewer::Quaternion OriInterpolator::GetOrientationAt(int frame) {
    return qglviewer::Quaternion();
}

void OriInterpolator::LoadOrientations(std::vector<OrientationStep>& steps) {

}

void OriInterpolator::AddOrientation(OrientationStep new_step) {

}
