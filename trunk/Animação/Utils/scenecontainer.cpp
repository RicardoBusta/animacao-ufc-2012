#include "Utils/scenecontainer.h"
#include "Objects3D/joint.h"
#include "Objects3D/object3d.h"
#include "Interpolation/objectanimator.h"

#include "Curves/curve.h"
#include "Objects3D/curveobject.h"
#include "Interpolation/quaternioninterpolation.h"

#include "Objects3D/spaceshipobject.h"

std::vector<Joint*> SceneContainer::objects_;
std::vector<ObjectAnimator*> SceneContainer::animators_;

Object3D* spaceship = new SpaceShipObject();
ObjectAnimator* animator = new ObjectAnimator(spaceship);
Object3D* trajectory = NULL;


bool SceneContainer::animate_position_ = true;
bool SceneContainer::animate_orientation_ = true;

int SceneContainer::start_frame_ = 0;
int SceneContainer::end_frame_ = 100;
int SceneContainer::current_frame_ = 0;

SceneContainer::SceneContainer()
{

}

void SceneContainer::ToErase(bool positions, bool orientations, int scene, int traject, int ori_int, int pos_int) {
    animate_position_ = positions;
    animate_orientation_ = orientations;

    if(scene == 0) {
        spaceship->SetDrawObject(true);
    }else{
        spaceship->SetDrawObject(false);
    }

    switch(ori_int){
    case 0:
        animator->SetOriInterpolationType(OriInterpolator::kSlerp);
        break;
    case 1:
        animator->SetOriInterpolationType(OriInterpolator::kBezier);
        break;
    default:
        break;
    }


    switch(pos_int){
    case 0:
        animator->SetPosInterpolationType(PosInterpolator::kLinear);
        break;
    case 1:
        animator->SetPosInterpolationType(PosInterpolator::kCatmullRoom);
        break;
    default:
        break;
    }


    switch(traject){
    case 0:
        trajectory = animator->GetTrajectory(TrajectoryObject::kPosition);
        break;
    case 1:
        trajectory = animator->GetTrajectory(TrajectoryObject::kOrientation);
        break;
    default:
        if(trajectory!=NULL) delete trajectory;
        trajectory = NULL;
    }

}

void SceneContainer::FakeDraw() {
    spaceship->Draw(animate_position_,animate_orientation_);
    if(trajectory!=NULL)
        trajectory->Draw(animate_position_,animate_orientation_);
}

void SceneContainer::CreateDefaultScene() {
    animator->AddKeyPosition(0,qglviewer::Vec(0,0,0));
    animator->AddKeyPosition(25,qglviewer::Vec(2,2,3));
    animator->AddKeyPosition(50,qglviewer::Vec(4,0,5));
    animator->AddKeyPosition(75,qglviewer::Vec(6,2,3));
    animator->AddKeyPosition(100,qglviewer::Vec(8,0,0));

    animator->AddKeyOrientation(0,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(0,1,0)));
        animator->AddKeyOrientation(25,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(1,0,1)));
        animator->AddKeyOrientation(50,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(-1,0,1)));
        animator->AddKeyOrientation(75,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(0,1,0)));
        animator->AddKeyOrientation(100,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(1,0,0)));


    /*animator->AddKeyOrientation(0,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(0,1,0)));
    animator->AddKeyOrientation(25,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(0,0,1)));
    animator->AddKeyOrientation(50,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(1,0,0)));
    animator->AddKeyOrientation(75,qglviewer::Quaternion(qglviewer::Vec(0,0,1),90));
    animator->AddKeyOrientation(100,qglviewer::Quaternion(qglviewer::Vec(0,0,1),0));*/
    animator->SetPosInterpolationType(PosInterpolator::kCatmullRoom);
    animators_.push_back(animator);
    spaceship->SetDrawOrientationAxes(true);
/*    //Object3D* default_object = new Object3D();
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
    animator->AddKeyPosition(75,qglviewer::Vec(6,2,0));
    animator->AddKeyPosition(100,qglviewer::Vec(8,0,0));
    animator->SetPosInterpolationType(PosInterpolator::kCatmullRoom);

    animator->AddKeyOrientation(0,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(-1,1,0)));
    animator->AddKeyOrientation(25,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(0,1,0)));
    animator->AddKeyOrientation(50,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(1,1,0)));
    animator->AddKeyOrientation(75,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(-1,1,0)));
    animator->AddKeyOrientation(100,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(1,0,0)));
    animator->SetOriInterpolationType(OriInterpolator::kBezier);


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

    Object3D* trajectory = animator->GetTrajectory(TrajectoryObject::kPosition);


    Joint* basic2 = new Joint(trajectory);
    objects_.push_back(basic2);
    animators_.push_back(animator);
*/
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
    animator_quat->AddKeyOrientation(33,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(-1,0,1)));
    animator_quat->AddKeyOrientation(66,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(1,0,1)));
    animator_quat->AddKeyOrientation(100,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(0,1,0)));

    animator_quat->SetPosInterpolationType(PosInterpolator::kLinear);
    animator_quat->SetOriInterpolationType(OriInterpolator::kSlerp);

    objects_.push_back(quatern1);
    objects_.push_back(quatern2);
    objects_.push_back(quatern3);
    objects_.push_back(quatern4);

    objects_.push_back(quatern5);

    Object3D* quat_ori = animator_quat->GetTrajectory(TrajectoryObject::kOrientation);
    Joint* quat_joint = new Joint(quat_ori);
    objects_.push_back(quat_joint);*/
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

int SceneContainer::HowManyObjects() {
    return objects_.size();
}

Joint* SceneContainer::ObjectAt(int i) {
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
