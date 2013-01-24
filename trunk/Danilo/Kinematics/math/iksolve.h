#ifndef IKSOLVE_H
#define IKSOLVE_H
#include "skeleton/skeleton.h"
#include <Eigen/Eigen>
#include <Eigen/Jacobi>
using namespace Eigen;
class IKSolve
{
public:
    IKSolve();
    static void IKSolveKinematicsInverse(Joint* effector,Vec4 goal,int type);
    static MatrixXd jacobian(Joint* effector);
    static MatrixXd pseudo_jacobian(Joint* effector,int type);
    //static void initializeJacobian(double *vet[][],int size);
};

#endif // IKSOLVE_H
