#include "viewer.h"
#include <vector>

#include "arclength.h"
#include <GL/glu.h>
#include "posinterpolator.h"

qglviewer::Vec global_p[101];
PosInterpolator pos_interpolator;

void Viewer::draw() {
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINE_STRIP);
    int slices = 50;
    double slice_size = 1.0/((double)(slices-1));
    for(int i = 0 ; i < slices ; i++ )
    {
        qglviewer::Vec p = nova_->Evaluate(slice_size*((double)(i)));
        glVertex3d(p.x,p.y,p.z);
        i += 0.02;
    }
    glEnd();

    glPushMatrix();
    glTranslated(0,0,0);
    gluSphere(gluNewQuadric(),0.02,15,15);
    glPopMatrix();

    glPushMatrix();
    glTranslated(1.5,3.0,3.0);
    gluSphere(gluNewQuadric(),0.02,15,15);
    glPopMatrix();

    glPushMatrix();
    glTranslated(3,0,0);
    gluSphere(gluNewQuadric(),0.02,15,15);
    glPopMatrix();

    glColor3f(1.0,0.0,0.0);
    for(int i = 0 ; i < 101 ; i++ ) {
        glPushMatrix();
        glTranslated(global_p[i].x,global_p[i].y,global_p[i].z-0.004);
        gluSphere(gluNewQuadric(),0.02,15,15);
        glPopMatrix();
    }

    glColor3f(0.0,0.0,1.0);
    for(int i = 0 ; i < 11 ; i++ ) {
        glPushMatrix();
        qglviewer::Vec point = nova_->Evaluate(i*0.1);
        glTranslated(point.x,point.y,point.z+0.004);
        gluSphere(gluNewQuadric(),0.02,15,15);
        glPopMatrix();
    }

    glColor3f(0.0,1.0,1.0);
    glBegin(GL_LINE_STRIP);
    for(int i = 0 ; i < 11 ; i++ ) {
        glPushMatrix();
        qglviewer::Vec point;
        point = pos_interpolator.GetPositionAt(i*10);
        glVertex3f(point.x,point.y,point.z);
        //gluSphere(gluNewQuadric(),0.02,15,15);
        glPopMatrix();
    }
    glEnd();
}

void Viewer::init() {

    glDisable(GL_LIGHTING);

    nova_ = new BezierQuadratic(qglviewer::Vec(0,0,0),qglviewer::Vec(1.5,3.0,3.0),qglviewer::Vec(3,0,0));
    ArcLength arc(nova_);
    arc.AdaptativeGaussianPrecalculation();
    for(int i = 0 ; i < 101 ; i++ )
        global_p[i] = arc.GetByNormalizedS(i*0.01);


    pos_interpolator.SetStartFrame(0);
    pos_interpolator.SetLastFrame(100);


    std::vector<PositionStep> positions;
    for(int i = 0 ; i < 11 ; i++ ) {
        PositionStep p;
        p.position_ = nova_->Evaluate(i*0.1) + qglviewer::Vec(0,0,-1);
        int frame = 10*i;
        /*for(int j = 1 ; j < i+1 ; j++ )
            frame += 10*j;*/
        p.frame_ = frame;
        positions.push_back(p);
    }

    for(int i = 0 ; i < positions.size() ; i++ )
        std::cout << "Frame: " << positions.at(i).frame_ << " Position: " << std::endl;

    pos_interpolator.LoadPoints(positions);
    //for(int i = 0 ; i < 101 ; i++ )
    //    global_p[i] = pos_interpolator.GetPositionAt(i);
    setSceneRadius(10.0f);

}

QString Viewer::helpString() const {
    return QString();
}
