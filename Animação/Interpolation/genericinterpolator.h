#ifndef GENERICINTERPOLATOR_H
#define GENERICINTERPOLATOR_H

enum SPEED_FUNCTION{SF_EASE_IN_OUT_SIN, SF_EASE_IN_POW, SF_EASE_OUT_ROOT, SF_NONE};

class GenericInterpolator
{
public:
    GenericInterpolator();

    SPEED_FUNCTION speed_function_;

    void setSpeedFunction(SPEED_FUNCTION value);

    double speedControl(double step);
};

#endif // GENERICINTERPOLATOR_H
