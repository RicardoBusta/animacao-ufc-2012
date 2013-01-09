#include "genericinterpolator.h"

#include <cmath>

GenericInterpolator::GenericInterpolator()
{
    speed_function_ = SF_NONE;
}

void GenericInterpolator::setSpeedFunction(SPEED_FUNCTION value){
    speed_function_ = value;
}

double GenericInterpolator::speedControl(double step){
    switch(speed_function_){
    case SF_EASE_IN_OUT_SIN:
        return sin(step*M_PI_2);
        break;
    case SF_EASE_IN_POW:
        return step*step;
        break;
    case SF_EASE_OUT_ROOT:
        return sqrt(step);
        break;
    default:
        return step;
        break;
    }
}
