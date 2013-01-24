#ifndef SIMPLEDRAW_H
#define SIMPLEDRAW_H
#include "skeleton/skeleton.h"

class SimpleDraw
{
public:
    Link* link[4];
    Joint* joint[4];
public:
    SimpleDraw();
    static void drawAxis(double len);
    void structure();
    void solveIK(Vec4 goal,Joint *joint,int type=0);
};

#endif // SIMPLEDRAW_H
