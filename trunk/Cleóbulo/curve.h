#ifndef CURVE_H
#define CURVE_H

#include <QGLViewer/vec.h>

class Curve {
public:
    virtual qglviewer::Vec Evaluate(double t) const = 0;
};

//! Some simple curve implementation examples -----------------------------------

class LinearCurve : public Curve {
public:
    LinearCurve(qglviewer::Vec a,qglviewer::Vec b)
        : p_a(a), p_b(b) {
    }

    qglviewer::Vec Evaluate(double t) const {
        return p_a*(1.0 - t) + p_b*(t);
    }


protected:
    qglviewer::Vec p_a,p_b;
};

class BezierQuadratic : public Curve {
public:
    BezierQuadratic(qglviewer::Vec a,qglviewer::Vec b, qglviewer::Vec c)
        : p_a(a), p_b(b), p_c(c) {
    }

    qglviewer::Vec Evaluate(double t) const {

        double c_a  = (1.0-t);
        return p_a*c_a*c_a + p_b*2.0*c_a*t +p_c*t*t;

    }

protected:
    qglviewer::Vec p_a,p_b,p_c;

};

class BezierCubic : public Curve {
public:
    BezierCubic(qglviewer::Vec a,qglviewer::Vec b, qglviewer::Vec c, qglviewer::Vec d)
        : p_a(a), p_b(b), p_c(c), p_d(d) {
    }

    qglviewer::Vec Evaluate(double t) const {

        double c_a  = (1.0-t);
        return p_a*c_a*c_a*c_a + p_b*3.0*c_a*c_a*t +p_c*3.0*c_a*t*t+p_d*t*t*t;

    }

protected:
    qglviewer::Vec p_a,p_b,p_c,p_d;

};

class CasteljauCurve : public Curve {
public:
    CasteljauCurve(qglviewer::Vec a,qglviewer::Vec b, qglviewer::Vec c, qglviewer::Vec d)
        : p_a(a), p_b(b), p_c(c), p_d(d) {
    }

    qglviewer::Vec Evaluate(double t) const {

        LinearCurve a(p_a,p_b);
        LinearCurve b(p_b,p_c);
        LinearCurve c(p_c,p_d);
        LinearCurve d(a.Evaluate(t),b.Evaluate(t));
        LinearCurve e(b.Evaluate(t),c.Evaluate(t));
        LinearCurve f(d.Evaluate(t),e.Evaluate(t));

        return f.Evaluate(t);
    }

protected:
    qglviewer::Vec p_a,p_b,p_c,p_d;

};

//! ---------------------------------------------------------------------------

#endif // CURVE_H
