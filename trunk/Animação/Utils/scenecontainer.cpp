#include "Utils/scenecontainer.h"
#include "Objects3D/joint.h"
#include "Objects3D/object3d.h"
#include "Interpolation/objectanimator.h"

#include "Curves/curve.h"
#include "Objects3D/curveobject.h"
#include "Interpolation/quaternioninterpolation.h"

#include "Objects3D/torus.h"

#include "Objects3D/fileobj.h"

std::vector<Joint*> SceneContainer::objects_;
std::vector<Object3D*> SceneContainer::extras_;
std::vector<ObjectAnimator*> SceneContainer::animators_;

int SceneContainer::selected_object_ = -1;

bool SceneContainer::animate_position_ = true;
bool SceneContainer::animate_orientation_ = true;

int SceneContainer::start_frame_ = 0;
int SceneContainer::end_frame_ = 100;
int SceneContainer::current_frame_ = 0;

SceneContainer::SceneContainer(){}

void SceneContainer::DrawObjects() {
    for(uint i = 0; i < objects_.size();i++){
        Joint *object = objects_.at(i);
        object->Draw();
    }
}

void SceneContainer::CreateDefaultScene() {

 /*   Torus* ss = new Torus(2,3,36,36);
    Joint* joint0 = new Joint(ss);

    Torus* ss2 = new Torus(2,3,36,36);
    Joint* joint_1 = new Joint(ss2);
    joint_1->AddChildJoint(joint0);
    //joint0->SetNewPosition(qglviewer::Vec(0,2,0));

    objects_.push_back(joint0);*/

    FileObj* obj = new FileObj();
    Object3D *teste = obj;
    obj->loadFile(":/models/ship.obj");
    obj->loadTex(":/textures/ship.png");
    Joint *joint = new Joint(teste);
    joint->SetNewPosition(qglviewer::Vec(-1,0,0));


    ObjectAnimator *animteste = new ObjectAnimator(joint);


    FileObj* obj2 = new FileObj();
    obj2->loadFile(":/models/ship.obj");
    obj2->loadTex(":/textures/ship.png");
    Object3D *teste2 = obj2;
    Joint *joint2 = new Joint(teste2);
    joint2->SetNewPosition(qglviewer::Vec(1,2,0));
    joint->AddChildJoint(joint2);

    ObjectAnimator *animteste2 = new ObjectAnimator(joint2);

    SceneContainer::objects_.push_back(joint);
    SceneContainer::animators_.push_back(animteste);
    SceneContainer::animators_.push_back(animteste2);

    animteste->AddKeyPosition(0,qglviewer::Vec(0,0,0));
    animteste->AddKeyPosition(25,qglviewer::Vec(2,2,3));
    animteste->AddKeyPosition(50,qglviewer::Vec(4,0,5));
    animteste->AddKeyPosition(75,qglviewer::Vec(6,2,3));
    animteste->AddKeyPosition(100,qglviewer::Vec(8,0,0));

    animteste->AddKeyOrientation(0, 0,0,0);
    animteste->AddKeyOrientation(25, 90,0,0);
    animteste->AddKeyOrientation(50, 90,90,30);
    animteste->AddKeyOrientation(75, 90,90,90);
    animteste->AddKeyOrientation(100, 0,0,0);

   /*animteste2->AddKeyPosition(0,qglviewer::Vec(0,0,0));
    animteste2->AddKeyPosition(25,qglviewer::Vec(2,2,3));
    animteste2->AddKeyPosition(50,qglviewer::Vec(4,0,5));
    animteste2->AddKeyPosition(75,qglviewer::Vec(6,2,3));
    animteste2->AddKeyPosition(100,qglviewer::Vec(8,0,0));*/

    /*animteste2->AddKeyOrientation(0, 0,0,0);
    animteste2->AddKeyOrientation(25, 90,0,0);
    animteste2->AddKeyOrientation(50, 90,90,30);
    animteste2->AddKeyOrientation(75, 90,90,90);
    animteste2->AddKeyOrientation(100, 0,0,0);*/

//    animteste->AddKeyOrientation(0,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(0,1,0)));
//    animteste->AddKeyOrientation(25,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(1,0,1)));
//    animteste->AddKeyOrientation(50,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(-1,0,1)));
//    animteste->AddKeyOrientation(75,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(0,1,0)));
//    animteste->AddKeyOrientation(100,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(1,0,0)));


    /*animator->AddKeyOrientation(0,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(0,1,0)));
    animator->AddKeyOrientation(25,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(0,0,1)));
    animator->AddKeyOrientation(50,qglviewer::Quaternion(qglviewer::Vec(0,1,0),qglviewer::Vec(1,0,0)));
    animator->AddKeyOrientation(75,qglviewer::Quaternion(qglviewer::Vec(0,0,1),90));
    animator->AddKeyOrientation(100,qglviewer::Quaternion(qglviewer::Vec(0,0,1),0));*/
    //animteste->SetPosInterpolationType(PosInterpolator::kCatmullRoom);
    //teste->SetDrawOrientationAxes(true);

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
    for(size_t i = 0 ; i < SceneContainer::animators_.size() ; i++ ) {
        ObjectAnimator* animator = SceneContainer::animators_.at(i);
        animator->SetFrameRange(start,end);
    }
}

void SceneContainer::SetCurrentFrame(int frame) {
    current_frame_ = frame;
    for(size_t i = 0 ; i < SceneContainer::animators_.size() ; i++ ) {
        ObjectAnimator* animator = SceneContainer::animators_.at(i);
        animator->SetCurrentFrame(current_frame_);
    }
}

unsigned int SceneContainer::HowManyObjects() {
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

void SceneContainer::SetPositionInterpolationType(PosInterpolator::InterpolationType type) {
    for(size_t i = 0 ; i < SceneContainer::animators_.size() ; i++ ) {
        ObjectAnimator* animator = SceneContainer::animators_.at(i);
        animator->SetPosInterpolationType(type);
    }
}

void SceneContainer::SetOrientationInterpolationType(OriInterpolator::InterpolationType type) {
    for(size_t i = 0 ; i < SceneContainer::animators_.size() ; i++ ) {
        ObjectAnimator* animator = SceneContainer::animators_.at(i);
        animator->SetOriInterpolationType(type);
    }
}

int SceneContainer::SelectedObject() {
    return selected_object_;
}
