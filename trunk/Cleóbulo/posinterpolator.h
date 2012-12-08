#ifndef POSINTERPOLATOR_H
#define POSINTERPOLATOR_H

#include <QGLViewer/vec.h>
#include "animation_step.h"

#include <vector>

class Curve;
class ArcLength;

class PosInterpolator
{
public:
    enum InterpolationPolicy {kFrameBased,kConstantSpeed};

    PosInterpolator();

    void SetStartFrame(int start_frame);
    void SetLastFrame(int last_frame);

    qglviewer::Vec GetPositionAt(int frame);

    void LoadPoints(std::vector<PositionStep>& steps);
    void AddPoint(PositionStep new_step);

protected:
    virtual void GenerateMainCurve();
    void AddCurve(Curve* curve);

    std::vector<PositionStep> steps_;

private:
    void CleanCurvesAndLengths();
    int ChooseInterval(int frame, InterpolationPolicy policy = kFrameBased);

    int start_frame_, last_frame_;

    double total_length_;
    std::vector<double> curves_lengths_;                // Lengths of the curves in relation to the main curve
    std::vector<std::pair<Curve*,ArcLength*> > curves_; // Curves and their own lengths
};

#endif // POSINTERPOLATOR_H
