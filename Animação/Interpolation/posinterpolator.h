#ifndef POSINTERPOLATOR_H
#define POSINTERPOLATOR_H

#include <QGLViewer/vec.h>
#include "animation_step.h"
#include "genericinterpolator.h"

#include <vector>

class Curve;
class ArcLength;

class PosInterpolator : public GenericInterpolator
{
public:
    enum InterpolationPolicy {kFrameBased,kConstantSpeed};
    enum InterpolationType  {kLinear,kBezier,kCatmullRoom};

    PosInterpolator();

    void setInterpolationType(InterpolationType type);
    void setStartFrame(int start_frame);
    void setLastFrame(int last_frame);

    qglviewer::Vec getPositionAt(int frame, bool *valid = NULL);

    void loadPoints(std::vector<PositionStep>& steps);
    void addPoint(PositionStep new_step);

protected:
    virtual void generateMainCurve();
    void generateLinearMainCurve();
    void generateBezierMainCurve();
    void generateCatmullRoomMainCurve() ;
    void addCurve(Curve* curve);

    std::vector<PositionStep> steps_;
    InterpolationType interpolation_type_;
private:
    void cleanCurvesAndLengths();
    int chooseInterval(int frame, InterpolationPolicy policy = kFrameBased);

    int start_frame_, last_frame_;

    double total_length_;
    std::vector<double> curves_lengths_;                // Lengths of the curves in relation to the main curve
    std::vector<std::pair<Curve*,ArcLength*> > curves_; // Curves and their own lengths
};

#endif // POSINTERPOLATOR_H
