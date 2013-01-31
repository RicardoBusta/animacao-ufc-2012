#ifndef IKSOLVER_H
#define IKSOLVER_H

#include <Objects3D/joint.h>

#define GOAL_DISTANCE_ERROR 0.001
#define D 0.5;
#define MAX_DISTANCE_FRAME 0.01

class GenericMatrix;

class IKSolver
{
public:
    IKSolver();

    static void solve(std::vector<Joint*> *bones, qglviewer::Vec goal, int type);
    static GenericMatrix jacobian(std::vector<Joint*> *bones, int type);
    static GenericMatrix pseudoJacobian(std::vector<Joint*> *bones, int type);
};

#endif // IKSOLVER_H
