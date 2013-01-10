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

    void SetInterpolationType(InterpolationType type);
    void SetStartFrame(int start_frame);
    void SetLastFrame(int last_frame);

    qglviewer::Vec GetPositionAt(int frame, bool *valid = NULL);

    void LoadPoints(std::vector<PositionStep>& steps);
    void AddPoint(PositionStep new_step);

protected:
    virtual void GenerateMainCurve();
    void GenerateLinearMainCurve();
    void GenerateBezierMainCurve();
    void GenerateCatmullRoomMainCurve() ;
    void AddCurve(Curve* curve);

    std::vector<PositionStep> steps_;
    InterpolationType interpolation_type_;
private:
    void CleanCurvesAndLengths();
    int ChooseInterval(int frame, InterpolationPolicy policy = kFrameBased);

    int start_frame_, last_frame_;

    double total_length_;
    std::vector<double> curves_lengths_;                // Lengths of the curves in relation to the main curve
    std::vector<std::pair<Curve*,ArcLength*> > curves_; // Curves and their own lengths
};

#endif // POSINTERPOLATOR_H
