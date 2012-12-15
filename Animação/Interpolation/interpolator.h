#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include "posinterpolator.h"
#include "oriinterpolator.h"

class Object3D;

class Interpolator
{
public:
    Interpolator();

    PosInterpolator pos_interpolator_;
    OriInterpolator ori_interpolator_;
    Object3D* object_;
};

#endif // INTERPOLATOR_H
