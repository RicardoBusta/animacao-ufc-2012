#ifndef ARCLENGTH_H
#define ARCLENGTH_H

#include <QGLViewer/vec.h>
#include <map>
#include <vector>
#include <utility>

#include "curve.h"

class LengthInterval {
public:
    LengthInterval() : start_length_(0.0), length_(0.0), u_start_(0.0),u_end_(0.0), error_(0.0) {}
    double start_length_;
    double length_;
    double u_start_;
    double u_end_;
    double error_;
};

class ULength {
public:
    ULength() : length_(0.0),u_(0.0) {}
    double length_;
    double u_;
};

class ArcLength
{
public:
    ArcLength(Curve* to_parameterize);

    void AdaptativeGaussianPrecalculation(); // Must be called before anything else

    qglviewer::Vec GetByS(double s) const; /* belongs to [0;total_length_]*/
    qglviewer::Vec GetByNormalizedS(double s) const; /* belongs to [0;1]*/

    double GetLength(double t) const;
    double GetTotalLength() const;

protected:

    double GaussianLegendreToInterval(double a, double b, std::vector<double>& points, std::vector<double>& weights) const;
    double FunctionToGetRoot(double x, double constant_length) const;
    double NumericalDerivative(double x, double constant_length) const;
    qglviewer::Vec NumericalVectorDerivative(double x) const;

    Curve* curve_;
    double acceptable_error_;
    bool precomputed_;

    double total_length_;
    std::vector<ULength> precalculated_length_;
    static std::vector<double> points_;
    static std::vector<double> weights_;

};

#endif // ARCLENGTH_H
