#include "quaternioninterpolation.h"

using namespace qglviewer;

CasteljauQuaternion::CasteljauQuaternion(qglviewer::Quaternion a,qglviewer::Quaternion b, qglviewer::Quaternion c, qglviewer::Quaternion d)
    : p_a(a), p_b(b), p_c(c), p_d(d) {
}

Quaternion CasteljauQuaternion::evaluate(double t) const {

    Quaternion ab = Quaternion::slerp(p_a,p_b,t);
    Quaternion bc = Quaternion::slerp(p_b,p_c,t);
    Quaternion cd = Quaternion::slerp(p_c,p_d,t);

    Quaternion abc = Quaternion::slerp(ab,bc,t);
    Quaternion bcd = Quaternion::slerp(bc,cd,t);

    return Quaternion::slerp(abc,bcd,t);
    //return Quaternion::squad(p_a,p_b,p_c,p_d,t);
}
