#ifndef GENERICINTERPOLATOR_H
#define GENERICINTERPOLATOR_H

class GenericInterpolator
{
public:
    enum SpeedFunction {SF_EASE_IN_OUT_SIN, SF_EASE_IN_POW, SF_EASE_OUT_ROOT, SF_CONSTANT};

    GenericInterpolator();

    static void setSpeedFunction(SpeedFunction value);

    double speedControl(double step);

private:
    static SpeedFunction speed_function_;
};

#endif // GENERICINTERPOLATOR_H
