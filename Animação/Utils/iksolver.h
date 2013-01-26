#ifndef IKSOLVER_H
#define IKSOLVER_H

#include <Objects3D/joint.h>

class IKSolver
{
public:
    IKSolver();

    void solve(Joint *effector, QVector4D targetPosition, int type);
    void jacobian(Joint *effector);
    void pseudoJacobian(Joint *effector, int type);
};

#endif // IKSOLVER_H
