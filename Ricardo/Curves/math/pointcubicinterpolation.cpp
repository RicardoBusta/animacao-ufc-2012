#include "pointcubicinterpolation.h"

PointCubicInterpolation::PointCubicInterpolation()
{
}

void PointCubicInterpolation::setBezier()
{
    matrix[3][0] = -1;
    matrix[3][1] = 3;
    matrix[3][2] = -3;
    matrix[3][3] = 1;

    matrix[2][0] = 3;
    matrix[2][1] = -6;
    matrix[2][2] = 3;
    matrix[2][3] = 0;

    matrix[1][0] = -3;
    matrix[1][1] = 3;
    matrix[1][2] = 0;
    matrix[1][3] = 0;

    matrix[0][0] = 1;
    matrix[0][1] = 0;
    matrix[0][2] = 0;
    matrix[0][3] = 0;
}

void PointCubicInterpolation::setControlPoints(Vector3f p0, Vector3f p1, Vector3f p2, Vector3f p3)
{
    controlPoint[0][0] = p0.getX();
    controlPoint[0][1] = p0.getY();
    controlPoint[0][2] = p0.getZ();

    controlPoint[1][0] = p1.getX();
    controlPoint[1][1] = p1.getY();
    controlPoint[1][2] = p1.getZ();

    controlPoint[2][0] = p2.getX();
    controlPoint[2][1] = p2.getY();
    controlPoint[2][2] = p2.getZ();

    controlPoint[3][0] = p3.getX();
    controlPoint[3][1] = p3.getY();
    controlPoint[3][2] = p3.getZ();
}

//#ifdef DEBUG_MODE
#include <iostream>
using namespace std;
//#endif
Vector3f PointCubicInterpolation::getPoint(float t)
{
    float result[3];

    float tVector[] = {1, t, t*t, t*t*t};

    float partialresult[4][3];

    cout << "derp" << endl;

    for(int i=0;i<4;i++){ //row
        for(int j=0;j<3;j++){ //point coord
            partialresult[i][j] = 0;
            for(int k=0;k<4;k++){ //column
                partialresult[i][j] += matrix[i][k]*controlPoint[k][j];
            }
        }
    }

    cout << "derp2" << endl;

    for(int j=0;j<3;j++){
        result[j] = 0;
        for(int k=0;k<4;k++){
            result[j] += tVector[k]*partialresult[k][j];
        }
    }

    cout << "derp3" << endl;

    Vector3f res(result[0],result[1],result[2]);

    return res;
}
