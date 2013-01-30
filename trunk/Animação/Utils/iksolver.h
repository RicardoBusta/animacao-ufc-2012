#ifndef IKSOLVER_H
#define IKSOLVER_H

#include <Objects3D/joint.h>

class GenericMatrix;

class IKSolver
{
public:
    IKSolver();

    static void solve(std::vector<Joint*> *bones, qglviewer::Vec goal, int type);
    static GenericMatrix jacobian(std::vector<Joint*> *bones);
    static GenericMatrix pseudoJacobian(std::vector<Joint*> *bones, int type);
};

#endif // IKSOLVER_H
