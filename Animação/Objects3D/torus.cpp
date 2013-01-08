#include "torus.h"
using namespace qglviewer;

Slice::Slice(double radius, qglviewer::Vec original_point, qglviewer::Vec axis, int steps) :
    radius_(radius), original_point_(original_point), axis_(axis), steps_(steps)
{
    CreateSlice();
}

qglviewer::Vec Slice::Step(int index)
{
    return slice_.at(index);
}

void Slice::CreateSlice()
{
    double PI =  3.14159265;
    double angle = (2.0*PI)/((double)(steps_-1));
    Quaternion rotation(axis_,angle);
    Vec new_point = Vec(0.0,1.0,0.0)*radius_;
    for(int i = 0; i<steps_ ; i++ ) {
        slice_.push_back(new_point + original_point_);
        new_point = rotation.rotate(new_point);
    }
}

Torus::Torus(double inner_radius, double outer_radius, int slices, int steps) :
    inner_radius_(inner_radius), outer_radius_(outer_radius), slices_(slices), steps_(steps)
{
    CreateSlices();
}

void Torus::CreateSlices()
{
    if(inner_radius_ > outer_radius_) {
        double tmp = outer_radius_;
        outer_radius_ = inner_radius_;
        inner_radius_ = tmp;
    }

    double PI =  3.14159265;
    double slice_radius = (outer_radius_ - inner_radius_)/2.0;
    double real_radius = slice_radius + inner_radius_;

    double angle = (2.0*PI)/((double)(slices_-1));
    for(int i = 0; i<slices_ ; i++ ) {
        Vec center(real_radius*cos(angle*((double)(i))),0.0,real_radius*sin(angle*((double)(i))));
        Vec axis(-sin(angle*((double)(i))),0.0,cos(angle*((double)(i))));
        torus_slices_.push_back(Slice(slice_radius,center,axis,steps_));
    }
}

void Torus::DrawObject() {
    for(int i = 0 ; i < torus_slices_.size()-1 ; i++ ) {
        glBegin(GL_TRIANGLE_STRIP);
        for(int j = 0 ; j < steps_ ; j++ ) {
            Vec first, second;
            first = torus_slices_.at(i).Step(j);
            second = torus_slices_.at(i+1).Step(j);
            glVertex3d(first.x,first.y,first.z);
            glVertex3d(second.x,second.y,second.z);
        }
        glEnd();
    }
}
