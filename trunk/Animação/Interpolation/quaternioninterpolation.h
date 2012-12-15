#ifndef QUATERNIONINTERPOLATION_H
#define QUATERNIONINTERPOLATION_H

#include <QGLViewer/quaternion.h>

class QuaternionInterpolator {
public:
    virtual qglviewer::Quaternion Evaluate(double t) const = 0;
};

class SlerpQuaternion : public QuaternionInterpolator {
public:
    SlerpQuaternion(qglviewer::Quaternion a,qglviewer::Quaternion b)
        : p_a(a),p_b(b){

    }

    qglviewer::Quaternion Evaluate(double t) const {
        return qglviewer::Quaternion::slerp(p_a,p_b,t);
    }
protected:
    qglviewer::Quaternion p_a,p_b;

};

class CasteljauQuaternion : public QuaternionInterpolator  {
public:
    CasteljauQuaternion(qglviewer::Quaternion a,qglviewer::Quaternion b, qglviewer::Quaternion c, qglviewer::Quaternion d);

    qglviewer::Quaternion Evaluate(double t) const;

protected:
    qglviewer::Quaternion p_a,p_b,p_c,p_d;

};

#endif // QUATERNIONINTERPOLATION_H
