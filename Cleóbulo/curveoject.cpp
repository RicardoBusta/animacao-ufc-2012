#include "curveoject.h"
#include "curve.h"

CurveOject::CurveOject(Curve* curve)
{
    curve_ = curve;
}

void CurveOject::DrawObject() {
    int steps = 25;
    double delta = (1.0)/((double)(steps-1.0));

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINE_STRIP);
    glColor3d(1,0,0);
    double current = 0;
    for(int i = 0 ; i < steps ; i++ ) {
        qglviewer::Vec pos = curve_->Evaluate(current);
        current += delta;
        glVertex3d(pos.x,pos.y,pos.z);
    }
    glEnd();

    glPointSize(3.0f);
    glBegin(GL_POINTS);
    glColor3d(0,1,0);
    current = 0;
    for(int i = 0 ; i < steps ; i++ ) {
        qglviewer::Vec pos = curve_->Evaluate(current);
        current += delta;
        glVertex3d(pos.x,pos.y,pos.z);
    }
    glEnd();

    glPopAttrib();
}
