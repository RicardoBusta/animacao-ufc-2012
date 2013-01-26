#ifndef IKSOLVER_H
#define IKSOLVER_H

#include <Objects3D/joint.h>

class GenericMatrix;

class IKSolver
{
public:
    IKSolver();

    static void solve(Joint *effector, qglviewer::Vec goal, int type);
    static GenericMatrix jacobian(Joint *effector);
    static GenericMatrix pseudoJacobian(Joint *effector, int type);
};

#endif // IKSOLVER_H
