#ifndef CURVE_H
#define CURVE_H

#include <QGLViewer/vec.h>

class Curve {
public:
    virtual qglviewer::Vec evaluate(double t) const = 0;
};

//! Some simple curve implementation examples -----------------------------------

class LinearCurve : public Curve {
public:
    LinearCurve(qglviewer::Vec a,qglviewer::Vec b)
        : p_a(a), p_b(b) {
    }

    qglviewer::Vec evaluate(double t) const {
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

    qglviewer::Vec evaluate(double t) const {

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

    qglviewer::Vec evaluate(double t) const {

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

    qglviewer::Vec evaluate(double t) const {

        LinearCurve a(p_a,p_b);
        LinearCurve b(p_b,p_c);
        LinearCurve c(p_c,p_d);
        LinearCurve d(a.evaluate(t),b.evaluate(t));
        LinearCurve e(b.evaluate(t),c.evaluate(t));
        LinearCurve f(d.evaluate(t),e.evaluate(t));

        return f.evaluate(t);
    }

protected:
    qglviewer::Vec p_a,p_b,p_c,p_d;

};


class Hermite : public Curve {
public:
    Hermite(qglviewer::Vec a,qglviewer::Vec ta, qglviewer::Vec b, qglviewer::Vec tb)
        : p_a(a), p_b(b), t_a(ta), t_b(tb) {
    }

    qglviewer::Vec evaluate(double t) const {
        double t_square = t*t;
        double t_cubic = t_square*t;
        return p_a*(2.0*t_cubic - 3.0*t_square + 1.0) + t_a*(t_cubic - 2.0*t_square + t) +
                p_b*(-2.0*t_cubic + 3.0*t_square) + t_b*(t_cubic - t_square);
    }

private:
    qglviewer::Vec p_a,p_b,t_a,t_b;
};

//! ---------------------------------------------------------------------------

#endif // CURVE_H
