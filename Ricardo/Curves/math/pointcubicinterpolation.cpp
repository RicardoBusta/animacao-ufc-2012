#include "pointcubicinterpolation.h"

PointCubicInterpolation::PointCubicInterpolation()
{

    //BEZIER
    M_Bezier[0][0] = -1;
    M_Bezier[0][1] = 3;
    M_Bezier[0][2] = -3;
    M_Bezier[0][3] = 1;

    M_Bezier[1][0] = 3;
    M_Bezier[1][1] = -6;
    M_Bezier[1][2] = 3;
    M_Bezier[1][3] = 0;

    M_Bezier[2][0] = -3;
    M_Bezier[2][1] = 3;
    M_Bezier[2][2] = 0;
    M_Bezier[2][3] = 0;

    M_Bezier[3][0] = 1;
    M_Bezier[3][1] = 0;
    M_Bezier[3][2] = 0;
    M_Bezier[3][3] = 0;

    //HERMITE
    M_Hermite[0][0] = 2;
    M_Hermite[0][1] = -2;
    M_Hermite[0][2] = 1;
    M_Hermite[0][3] = 1;

    M_Hermite[1][0] = -3;
    M_Hermite[1][1] = 3;
    M_Hermite[1][2] = -2;
    M_Hermite[1][3] = -1;

    M_Hermite[2][0] = 0;
    M_Hermite[2][1] = 0;
    M_Hermite[2][2] = 1;
    M_Hermite[2][3] = 0;

    M_Hermite[3][0] = 1;
    M_Hermite[3][1] = 0;
    M_Hermite[3][2] = 0;
    M_Hermite[3][3] = 0;
}

void PointCubicInterpolation::setControlPoints(Vector3f p0, Vector3f p1, Vector3f p2, Vector3f p3)
{
    C[0][0] = p0.getX();
    C[0][1] = p0.getY();
    C[0][2] = p0.getZ();

    C[1][0] = p1.getX();
    C[1][1] = p1.getY();
    C[1][2] = p1.getZ();

    C[2][0] = p2.getX();
    C[2][1] = p2.getY();
    C[2][2] = p2.getZ();

    C[3][0] = p3.getX();
    C[3][1] = p3.getY();
    C[3][2] = p3.getZ();
}

Vector3f PointCubicInterpolation::getPoint(float t)
{
    // R = T * M * C

    //Cubic Parameter Vector
    float T[] = {t*t*t, t*t, t, 1};
    //Partial Result
    float PR[4][3];
    //Result
    float R[3];

    // PR = M * C

    for(int i=0;i<4;i++){ //row
        for(int j=0;j<3;j++){ //point coord
            PR[i][j] = 0;
            for(int k=0;k<4;k++){ //column
                PR[i][j] += M_Hermite[i][k]*C[k][j];
            }
        }
    }

    // ( T * PR )

    for(int j=0;j<3;j++){
        R[j] = 0;
        for(int k=0;k<4;k++){
            R[j] += T[k]*PR[k][j];
        }
    }

    Vector3f res(R[0],R[1],R[2]);

    return res;
}
