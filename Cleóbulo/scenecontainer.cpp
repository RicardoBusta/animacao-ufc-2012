#include "scenecontainer.h"
#include "joint.h"
#include "object3d.h"
#include "objectanimator.h"

#include "curve.h"
#include "curveoject.h"

std::vector<Joint*> SceneContainer::objects_;
std::vector<ObjectAnimator*> SceneContainer::animators_;

void InterpolatePoints(std::vector<Curve*>& curves, std::vector<qglviewer::Vec>& points) {

    if(points.size() < 2)
        return;

    if(points.size() == 2) {
        curves.push_back(new LinearCurve(points.at(0),points.at(1)));
        return;
    }

    qglviewer::Vec a,b,pa;
    qglviewer::Vec delta;
    for(size_t i = 0 ; i < points.size() ; i++) {
        if( i == 0 ) {
            delta = points.at(1) - points.at(2);
            pa = points.at(1) + delta;
        } else if( i ==  points.size() - 1 ) {
            delta = points.at(i-1) - points.at(i-2);
            b = points.at(i-1) + delta;
            //curves.push_back(new BezierCubic(points.at(i-1),pa,b,points.at(i)));
            curves.push_back(new BezierQuadratic(points.at(i-1),pa,points.at(i)));
        }else {
            delta = points.at(i) - points.at(i-1);
            a = points.at(i) + delta;
            a = (a + points.at(i+1))/2.0;
            delta = points.at(i) - a;
            b = points.at(i) + delta;
            if( i == 1) {
                curves.push_back(new BezierQuadratic(points.at(i-1),b,points.at(i)));
            }else{
                curves.push_back(new BezierCubic(points.at(i-1),pa,b,points.at(i)));
            }
            pa = a;

        }
    }


}

int SceneContainer::start_frame_ = 0;
int SceneContainer::end_frame_ = 100;
int SceneContainer::current_frame_ = 0;

SceneContainer::SceneContainer()
{
}

void SceneContainer::CreateDefaultScene() {
    Object3D* default_object = new Object3D();
    default_object->SetDrawOrientationAxes(true);
    default_object->SetDrawPositionParticle(true);
    ObjectAnimator* animator = new ObjectAnimator(default_object);
    animator->SetFrameRange(start_frame_,end_frame_);

    /*animator->AddKeyPosition(0,qglviewer::Vec(0,0,0));
    animator->AddKeyPosition(50,qglviewer::Vec(1.5,2,0));
    animator->AddKeyPosition(100,qglviewer::Vec(3,0,0));*/
    animator->AddKeyPosition(0,qglviewer::Vec(0,0,0));
    animator->AddKeyPosition(25,qglviewer::Vec(2,2,0));
    animator->AddKeyPosition(50,qglviewer::Vec(4,0,0));
    animator->AddKeyPosition(75,qglviewer::Vec(6,3,0));
    animator->AddKeyPosition(100,qglviewer::Vec(8,0,0));
    animator->SetPosInterpolationType(PosInterpolator::kBezier);

    Object3D* trajectory = animator->GetTrajectory();

    Joint* basic = new Joint(default_object);
    Joint* basic2 = new Joint(trajectory);
    objects_.push_back(basic);
    objects_.push_back(basic2);
    animators_.push_back(animator);

    qglviewer::Vec a,b,c,d;
    a.setValue(0,0,0);
    b.setValue(0.75,2,0);
    c.setValue(2.25,2,0);
    d.setValue(3,0,0);
    /*
    Curve* bezier = new BezierCubic(a,b,c,d);
    CurveOject* curve_object = new CurveOject(bezier);
    Joint* basic3 = new Joint(curve_object);
    objects_.push_back(basic3);*/
    std::vector<qglviewer::Vec> points;
    /*points.push_back(a);
    points.push_back(b);
    points.push_back(c);
    points.push_back(d);*/
    points.push_back(qglviewer::Vec(0,0,0));
    points.push_back(qglviewer::Vec(2,2,0));
    points.push_back(qglviewer::Vec(4,0,0));
    points.push_back(qglviewer::Vec(6,3,0));
    points.push_back(qglviewer::Vec(8,0,0));

    std::vector<Curve*> curves;
    //InterpolatePoints(curves,points);
    std::cout << "Curves: " << curves.size() << std::endl;
    for(size_t i = 0 ; i < curves.size() ; i++ ) {
        CurveOject* curve_object = new CurveOject(curves.at(i));
        Joint* basic_curve = new Joint(curve_object);
        objects_.push_back(basic_curve);
    }
}

int SceneContainer::start_frame() {
    return start_frame_;
}

int SceneContainer::end_frame() {
    return end_frame_;
}

int SceneContainer::current_frame() {
    return current_frame_;
}

void SceneContainer::GoToNextFrame() {
    int frame = current_frame_;
    int next_frame = (frame+1)%(end_frame_+1);
    SceneContainer::SetCurrentFrame(next_frame);
}

void SceneContainer::SetFrameRange(int start, int end) {
    start_frame_    = start;
    end_frame_      = end;
    for(size_t i = 0 ; i < animators_.size() ; i++ ) {
        ObjectAnimator* animator = animators_.at(i);
        animator->SetFrameRange(start,end);
    }
}

void SceneContainer::SetCurrentFrame(int frame) {
    current_frame_ = frame;
    for(size_t i = 0 ; i < animators_.size() ; i++ ) {
        ObjectAnimator* animator = animators_.at(i);
        animator->SetCurrentFrame(current_frame_);
    }
}

size_t SceneContainer::HowManyObjects() {
    return objects_.size();
}

Joint* SceneContainer::ObjectAt(size_t i) {
    return objects_.at(i);
}
