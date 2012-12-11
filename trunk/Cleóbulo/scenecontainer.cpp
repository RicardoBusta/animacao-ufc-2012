#include "scenecontainer.h"
#include "joint.h"
#include "object3d.h"
#include "objectanimator.h"

#include "curve.h"
#include "curveoject.h"
#include "quaternioninterpolation.h"

#include "spaceshipobject.h"

std::vector<Joint*> SceneContainer::objects_;
std::vector<ObjectAnimator*> SceneContainer::animators_;

bool SceneContainer::animate_position_ = true;
bool SceneContainer::animate_orientation_ = true;

int SceneContainer::start_frame_ = 0;
int SceneContainer::end_frame_ = 100;
int SceneContainer::current_frame_ = 0;

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

SceneContainer::SceneContainer()
{
}

void SceneContainer::CreateDefaultScene() {
    //Object3D* default_object = new Object3D();
    Object3D* default_object = new SpaceShipObject();
    default_object->SetDrawOrientationAxes(true);
    default_object->SetDrawPositionParticle(true);
    Joint* basic = new Joint(default_object);
    objects_.push_back(basic);

    //ObjectAnimator* animator = new ObjectAnimator(default_object);

     ObjectAnimator* animator = new ObjectAnimator(basic);
    animator->SetFrameRange(start_frame_,end_frame_);

    animator->AddKeyPosition(0,qglviewer::Vec(0,0,0));
    animator->AddKeyPosition(25,qglviewer::Vec(2,2,0));
    animator->AddKeyPosition(50,qglviewer::Vec(4,0,0));
    animator->AddKeyPosition(75,qglviewer::Vec(6,3,0));
    animator->AddKeyPosition(100,qglviewer::Vec(8,0,0));

    animator->AddKeyOrientation(0,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(0,1,0)));
    animator->AddKeyOrientation(25,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(-1,0,0)));
    animator->AddKeyOrientation(50,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(1,0,0)));
    animator->AddKeyOrientation(75,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(0,0,1)));
    animator->AddKeyOrientation(100,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(0,1,0)));


    Object3D *ori1 = new Object3D();
    Object3D *ori2 = new Object3D();
    Object3D *ori3 = new Object3D();
    Object3D *ori4 = new Object3D();
    Object3D *ori5 = new Object3D();
    ori1->SetDrawOrientationAxes(true);
    ori2->SetDrawOrientationAxes(true);
    ori3->SetDrawOrientationAxes(true);
    ori4->SetDrawOrientationAxes(true);
    ori5->SetDrawOrientationAxes(true);


    ori1->SetNewPosition(qglviewer::Vec(0,0,0));
    ori2->SetNewPosition(qglviewer::Vec(2,2,0));
    ori3->SetNewPosition(qglviewer::Vec(4,0,0));
    ori4->SetNewPosition(qglviewer::Vec(6,3,0));
    ori5->SetNewPosition(qglviewer::Vec(8,0,0));

    ori1->SetNewOrientation(qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(0,1,0)));
    ori2->SetNewOrientation(qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(-1,0,0)));
    ori3->SetNewOrientation(qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(1,0,0)));
    ori4->SetNewOrientation(qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(0,0,1)));
    ori5->SetNewOrientation(qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(0,1,0)));

    Joint* joint1 = new Joint(ori1);
    Joint* joint2 = new Joint(ori2);
    Joint* joint3 = new Joint(ori3);
    Joint* joint4 = new Joint(ori4);
    Joint* joint5 = new Joint(ori5);
    objects_.push_back(joint1);
    objects_.push_back(joint2);
    objects_.push_back(joint3);
    objects_.push_back(joint4);
    objects_.push_back(joint5);


    animator->SetPosInterpolationType(PosInterpolator::kBezier);


    Object3D* trajectory = animator->GetTrajectory();


    Joint* basic2 = new Joint(trajectory);
    objects_.push_back(basic2);
    animators_.push_back(animator);

    /*
    qglviewer::Vec a,b,c,d;
    a.setValue(0,0,0);
    b.setValue(0.75,2,0);
    c.setValue(2.25,2,0);
    d.setValue(3,0,0);

    Curve* bezier = new BezierCubic(a,b,c,d);
    CurveOject* curve_object = new CurveOject(bezier);
    Joint* basic3 = new Joint(curve_object);
    objects_.push_back(basic3);*/
    /*
    std::vector<qglviewer::Vec> points;
    points.push_back(qglviewer::Vec(0,0,0));
    points.push_back(qglviewer::Vec(2,2,0));
    points.push_back(qglviewer::Vec(4,0,0));
    points.push_back(qglviewer::Vec(6,3,0));
    points.push_back(qglviewer::Vec(8,0,0));

    std::vector<Curve*> curves;
    InterpolatePoints(curves,points);
    std::cout << "Curves: " << curves.size() << std::endl;
    for(size_t i = 0 ; i < curves.size() ; i++ ) {
        CurveOject* curve_object = new CurveOject(curves.at(i));
        Joint* basic_curve = new Joint(curve_object);
        objects_.push_back(basic_curve);
    }*/

    /*CasteljauCurve* curve = new CasteljauCurve(qglviewer::Vec(0,0,0),qglviewer::Vec(3,4,0),qglviewer::Vec(6,4,0),qglviewer::Vec(8,0,0));
    Object3D* curve_obj = new CurveOject(curve);
    Joint* basic3 = new Joint(curve_obj);
    objects_.push_back(basic3);*/
/*
    Object3D* quat1 = new Object3D();
    Object3D* quat2 = new Object3D();
    Object3D* quat3 = new Object3D();
    Object3D* quat4 = new Object3D();

    quat1->SetDrawOrientationAxes(true);
    quat2->SetDrawOrientationAxes(true);
    quat3->SetDrawOrientationAxes(true);
    quat4->SetDrawOrientationAxes(true);

    quat1->SetNewPosition(qglviewer::Vec(0,0,1));
    quat2->SetNewPosition(qglviewer::Vec(0,4,1));
    quat3->SetNewPosition(qglviewer::Vec(4,4,1));
    quat4->SetNewPosition(qglviewer::Vec(4,0,1));

    quat1->SetNewOrientation(qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(0,1,0)));
    quat2->SetNewOrientation(qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(-1,0,0)));
    quat3->SetNewOrientation(qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(1,0,0)));
    quat4->SetNewOrientation(qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(0,1,0)));

    Joint* quatern1 = new Joint(quat1);
    Joint* quatern2 = new Joint(quat2);
    Joint* quatern3 = new Joint(quat3);
    Joint* quatern4 = new Joint(quat4);

    Object3D* quat5 = new Object3D();
    quat5->SetDrawOrientationAxes(true);
    //ObjectAnimator* animator_quat = new ObjectAnimator(quat5);
    Joint* quatern5 = new Joint(quat5);
    ObjectAnimator* animator_quat = new ObjectAnimator(quatern5);
    animator->SetFrameRange(start_frame_,end_frame_);
    animators_.push_back(animator_quat);

    animator_quat->AddKeyPosition(0,qglviewer::Vec(0,0,1));
    animator_quat->AddKeyPosition(33,qglviewer::Vec(0,4,1));
    animator_quat->AddKeyPosition(66,qglviewer::Vec(4,4,1));
    animator_quat->AddKeyPosition(100,qglviewer::Vec(4,0,1));

    animator_quat->AddKeyOrientation(0,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(0,1,0)));
    animator_quat->AddKeyOrientation(33,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(-1,0,0)));
    animator_quat->AddKeyOrientation(66,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(1,0,0)));
    animator_quat->AddKeyOrientation(100,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(0,1,0)));

    animator_quat->SetPosInterpolationType(PosInterpolator::kLinear);

    objects_.push_back(quatern1);
    objects_.push_back(quatern2);
    objects_.push_back(quatern3);
    objects_.push_back(quatern4);


    objects_.push_back(quatern5);*/
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

void SceneContainer::SetAnimated(bool animate_position, bool animate_orientation) {
    animate_position_       = animate_position;
    animate_orientation_    = animate_orientation;
}

bool SceneContainer::AnimatePosition() {
    return animate_position_;
}

bool SceneContainer::AnimateOrientation() {
    return animate_orientation_;
}
