#include "Utils/scenecontainer.h"
#include "Objects3D/joint.h"
#include "Objects3D/object3d.h"
#include "Interpolation/objectanimator.h"

#include "Curves/curve.h"
#include "Objects3D/curveobject.h"
#include "Interpolation/quaternioninterpolation.h"

#include "Objects3D/torus.h"

#include "Objects3D/fileobj.h"

#include <QQuaternion>
Viewer* SceneContainer::viewer_reference_ = NULL;

std::vector<Joint*> SceneContainer::objects_;
std::vector<Object3D*> SceneContainer::extras_;
std::vector<ObjectAnimator*> SceneContainer::animators_;

Object3D* SceneContainer::selected_object_ = NULL;

bool SceneContainer::animate_position_ = true;
bool SceneContainer::animate_orientation_ = true;

int SceneContainer::start_frame_ = 0;
int SceneContainer::end_frame_ = 100;
int SceneContainer::current_frame_ = 0;

bool SceneContainer::render_box_over_object_ = false;
bool SceneContainer::draw_bones_ = false;

unsigned int SceneContainer::render_options_ = 0;

SceneContainer::SceneContainer(){}

#include <iostream>
using namespace std;

void SceneContainer::DrawObjects() {
    for(uint i = 0; i < objects_.size();i++){
        Joint *object = objects_.at(i);
        render_options_ = RENDER_SHADER;
        object->Draw();
    }

    cout << "enum teste" << endl;
    cout << RENDER_NONE << endl;
    cout << RENDER_SHADER << endl;
    cout << RENDER_OPT2 << endl;
    cout << (RENDER_OPT2|RENDER_SHADER) << endl;
}

void SceneContainer::DrawExtras()
{
    for(int i = 0 ; i < extras_.size() ; i++ ) {
        Object3D* object = extras_.at(i);
        render_options_ = RENDER_NONE;
        object->Draw();
    }
}


Joint* SceneContainer::AddObject(QString label, QString objfile, QString texfile, QVector3D position, QQuaternion rotation, Joint* parent){
    FileObj *newobj = new FileObj();
    newobj->SetLabel( label.toStdString() );
    newobj->loadFile(objfile);
    newobj->loadTex(texfile);
    Joint *newjoint = new Joint(newobj);
    //newjoint->SetLabel( ( label+" Joint" ).toStdString());
    newjoint->SetNewPosition(qglviewer::Vec(position.x(),position.y(),position.z()));
    newjoint->SetNewOrientation(qglviewer::Quaternion(rotation.x(),rotation.y(),rotation.z(),rotation.scalar()));
    if(parent == NULL){
        SceneContainer::objects_.push_back(newjoint);
    }else{
        parent->AddChildJoint(newjoint);
    }
    ObjectAnimator *newanimator = new ObjectAnimator(newjoint);
    SceneContainer::animators_.push_back(newanimator);

    return newjoint;
}

void SceneContainer::CreateDefaultScene() {
    //Hand Scene
    Joint* arm_base = AddObject("Arm Base",":/models/arm_base.obj",":/textures/wooden.png",QVector3D(0,0.75,0), QQuaternion(1,0,0,0), NULL);
    Joint* arm_part1 = AddObject("Part 1",":/models/arm_part1.obj",":/textures/wooden.png",QVector3D(0,0.25,0),QQuaternion(1,0,0,0),arm_base);
    Joint* arm_part2 = AddObject("Part 2",":/models/arm_part2.obj",":/textures/wooden.png",QVector3D(0,3.7,0),QQuaternion(1,0,0,0),arm_part1);
    Joint* arm_hand = AddObject("Hand",":/models/arm_hand.obj",":/textures/wooden.png",QVector3D(0,4.7,0),QQuaternion(1,0,0,0),arm_part2);
    //    Joint* arm_hand = AddObject("Hand",":/models/face_eye.obj",":/textures/eye.png",QVector3D(0,4.7,0),QQuaternion(1,0,0,0),arm_part2);



    Joint* arm_finger_5_1 = AddObject("Finger 5 Part 1",":/models/arm_finger.obj",":/textures/wooden.png",QVector3D(0.5,1.4,0),QQuaternion(1,0,0,0),arm_hand);
    Joint* arm_finger_4_1 = AddObject("Finger 4 Part 1",":/models/arm_finger.obj",":/textures/wooden.png",QVector3D(0.2,1.5,0),QQuaternion(1,0,0,0),arm_hand);
    Joint* arm_finger_3_1 = AddObject("Finger 3 Part 1",":/models/arm_finger.obj",":/textures/wooden.png",QVector3D(-0.1,1.6,0),QQuaternion(1,0,0,0),arm_hand);
    Joint* arm_finger_2_1 = AddObject("Finger 2 Part 1",":/models/arm_finger.obj",":/textures/wooden.png",QVector3D(-0.4,1.5,0),QQuaternion(1,0,0,0),arm_hand);
    Joint* arm_finger_1_1 = AddObject("Finger 1 Part 1",":/models/arm_finger.obj",":/textures/wooden.png",QVector3D(-0.6,1,0),QQuaternion(1,0,0,0),arm_hand);

    Joint* arm_finger_5_2 = AddObject("Finger 5 Part 2",":/models/arm_finger.obj",":/textures/wooden.png",QVector3D(0,0.6,0),QQuaternion(1,0,0,0),arm_finger_5_1);
    Joint* arm_finger_4_2 = AddObject("Finger 4 Part 2",":/models/arm_finger.obj",":/textures/wooden.png",QVector3D(0,0.6,0),QQuaternion(1,0,0,0),arm_finger_4_1);
    Joint* arm_finger_3_2 = AddObject("Finger 3 Part 2",":/models/arm_finger.obj",":/textures/wooden.png",QVector3D(0,0.6,0),QQuaternion(1,0,0,0),arm_finger_3_1);
    Joint* arm_finger_2_2 = AddObject("Finger 2 Part 2",":/models/arm_finger.obj",":/textures/wooden.png",QVector3D(0,0.6,0),QQuaternion(1,0,0,0),arm_finger_2_1);
    Joint* arm_finger_1_2 = AddObject("Finger 1 Part 2",":/models/arm_finger.obj",":/textures/wooden.png",QVector3D(0,0.6,0),QQuaternion(1,0,0,0),arm_finger_1_1);

    ObjectAnimator *animate;

    animate = arm_base->GetAnimator();

    animate->AddKeyPosition(0,qglviewer::Vec(0,0,0));
    animate->AddKeyPosition(25,qglviewer::Vec(2,2,3));
    animate->AddKeyPosition(50,qglviewer::Vec(4,0,5));
    animate->AddKeyPosition(75,qglviewer::Vec(6,2,3));
    animate->AddKeyPosition(100,qglviewer::Vec(8,0,0));

    animate->AddKeyOrientation(0, 0,0,0);
    animate->AddKeyOrientation(25, 90,0,0);
    animate->AddKeyOrientation(50, 90,90,30);
    animate->AddKeyOrientation(75, 90,90,90);
    animate->AddKeyOrientation(100, 0,0,0);

    animate = arm_part1->GetAnimator();
    animate->AddKeyOrientation(0, 0,0,0);
    animate->AddKeyOrientation(25, 90,0,0);
    animate->AddKeyOrientation(50, 90,90,30);
    animate->AddKeyOrientation(75, 90,90,90);
    animate->AddKeyOrientation(100, 0,0,0);

    animate = arm_part2->GetAnimator();
    animate->AddKeyOrientation(0, 0,0,0);
    animate->AddKeyOrientation(25, 90,0,0);
    animate->AddKeyOrientation(50, 90,90,30);
    animate->AddKeyOrientation(75, 90,90,90);
    animate->AddKeyOrientation(100, 0,0,0);

    animate = arm_hand->GetAnimator();
    animate->AddKeyOrientation(0, 0,0,0);
    animate->AddKeyOrientation(25, 90,0,0);
    animate->AddKeyOrientation(50, 90,90,30);
    animate->AddKeyOrientation(75, 90,90,90);
    animate->AddKeyOrientation(100, 0,0,0);

    animate = arm_finger_1_1->GetAnimator();
    animate->AddKeyOrientation(0, 0,0,0);
    animate->AddKeyOrientation(25, 90,0,0);
    animate->AddKeyOrientation(50, 90,90,30);
    animate->AddKeyOrientation(75, 90,90,90);
    animate->AddKeyOrientation(100, 0,0,0);

    animate = arm_finger_2_1->GetAnimator();
    animate->AddKeyOrientation(0, 0,0,0);
    animate->AddKeyOrientation(25, 90,0,0);
    animate->AddKeyOrientation(50, 90,90,30);
    animate->AddKeyOrientation(75, 90,90,90);
    animate->AddKeyOrientation(100, 0,0,0);

    animate = arm_finger_3_1->GetAnimator();
    animate->AddKeyOrientation(0, 0,0,0);
    animate->AddKeyOrientation(25, 90,0,0);
    animate->AddKeyOrientation(50, 90,90,30);
    animate->AddKeyOrientation(75, 90,90,90);
    animate->AddKeyOrientation(100, 0,0,0);

    animate = arm_finger_4_1->GetAnimator();
    animate->AddKeyOrientation(0, 0,0,0);
    animate->AddKeyOrientation(25, 90,0,0);
    animate->AddKeyOrientation(50, 90,90,30);
    animate->AddKeyOrientation(75, 90,90,90);
    animate->AddKeyOrientation(100, 0,0,0);

    animate = arm_finger_5_1->GetAnimator();
    animate->AddKeyOrientation(0, 0,0,0);
    animate->AddKeyOrientation(25, 90,0,0);
    animate->AddKeyOrientation(50, 90,90,30);
    animate->AddKeyOrientation(75, 90,90,90);
    animate->AddKeyOrientation(100, 0,0,0);//*/

    //Face Scene
    Joint* face_head = AddObject("Head",":/models/face_head.obj","://textures/wooden.png",QVector3D(0,3,0), QQuaternion(1,0,0,0), arm_hand);
    //    Joint* face_head = AddObject("Head",":/models/face_head.obj","://textures/wooden.png",QVector3D(-5,3,0), QQuaternion(1,0,0,0), NULL);
    Joint* face_teeth_top = AddObject("Teeth Up",":/models/face_teeth_top.obj",":/textures/stache_teeth.png",QVector3D(0,-1.5,1), QQuaternion(1,0,0,0), face_head);
    Joint* face_teeth_bot = AddObject("Teeth Down",":/models/face_teeth_bot.obj",":/textures/stache_teeth.png",QVector3D(0,-1.5,1), QQuaternion(1,0,0,0), face_head);
    Joint* face_eye_lid_back_left = AddObject("Eye Lid Back Left",":/models/face_eye_lid_back.obj",":/textures/wooden.png",QVector3D(0.7,0.5,1.7), QQuaternion(1,0,0,0), face_head);
    Joint* face_eye_lid_back_right = AddObject("Eye Lid Back Right",":/models/face_eye_lid_back.obj",":/textures/wooden.png",QVector3D(-0.7,0.5,1.7), QQuaternion(1,0,0,0), face_head);
    Joint* face_eye_left = AddObject("Eye Left",":/models/face_eye.obj",":/textures/eye.png",QVector3D(0,0,0), QQuaternion(1,0,0,0), face_eye_lid_back_left);
    Joint* face_eye_right = AddObject("Eye Right",":/models/face_eye.obj",":/textures/eye.png",QVector3D(0,0,0), QQuaternion(1,0,0,0), face_eye_lid_back_right);
    Joint* face_eye_lid_top_left = AddObject("Eye Lid Top Left",":/models/face_eye_lid_front.obj",":/textures/wooden.png",QVector3D(0,0,0), QQuaternion(1,0,0,0), face_eye_lid_back_left);
    Joint* face_eye_lid_top_right = AddObject("Eye Lid Top Right",":/models/face_eye_lid_front.obj",":/textures/wooden.png",QVector3D(0,0,0), QQuaternion(1,0,0,0), face_eye_lid_back_right);
    Joint* face_eye_lid_bot_left = AddObject("Eye Lid Bot Left",":/models/face_eye_lid_front.obj",":/textures/wooden.png",QVector3D(0,0,0), QQuaternion(cos(M_PI_4),sin(M_PI_4),0,0), face_eye_lid_back_left);
    Joint* face_eye_lid_bot_right = AddObject("Eye Lid Bot Right",":/models/face_eye_lid_front.obj",":/textures/wooden.png",QVector3D(0,0,0), QQuaternion(cos(M_PI_4),sin(M_PI_4),0,0), face_eye_lid_back_right);
    Joint* face_brow_left = AddObject("Eye Brow Left",":/models/face_brow.obj",":/textures/wooden.png",QVector3D(0.3,1,0), QQuaternion(1,0,0,0), face_eye_lid_back_left);
    Joint* face_brow_right = AddObject("Eye Brow Right",":/models/face_brow.obj",":/textures/wooden.png",QVector3D(-0.3,1,0), QQuaternion(1,0,0,0), face_eye_lid_back_right);
    Joint* face_stache = AddObject("Stache",":/models/face_stache.obj",":/textures/stache_teeth.png",QVector3D(0,-0.5,2), QQuaternion(1,0,0,0), face_head);
    Joint* face_hat = AddObject("Hat",":/models/face_hat.obj",":/textures/wooden.png",QVector3D(0,1.4,0), QQuaternion(1,0,0,0), face_head);

    animate = face_teeth_bot->GetAnimator();
    animate->AddKeyOrientation(0, 0,0,0);
    animate->AddKeyOrientation(50, 0.5,0,0);
    animate->AddKeyOrientation(100, 0,0,0);

    animate = face_eye_lid_top_left->GetAnimator();
    animate->AddKeyOrientation(0, 0,0,0);
    animate->AddKeyOrientation(25, -0.5,0,0);
    animate->AddKeyOrientation(50, 0,0,0);
    animate->AddKeyOrientation(75, -0.5,0,0);
    animate->AddKeyOrientation(100, 0,0,0);

    animate = face_eye_lid_bot_left->GetAnimator();
    animate->AddKeyOrientation(0, 1.6,0,0);
    animate->AddKeyOrientation(25, 2.1,0,0);
    animate->AddKeyOrientation(50, 1.6,0,0);
    animate->AddKeyOrientation(75, 2.1,0,0);
    animate->AddKeyOrientation(100, 1.6,0,0);

    animate = face_eye_lid_top_right->GetAnimator();
    animate->AddKeyOrientation(0, 0,0,0);
    animate->AddKeyOrientation(25, -0.5,0,0);
    animate->AddKeyOrientation(50, 0,0,0);
    animate->AddKeyOrientation(75, -0.5,0,0);
    animate->AddKeyOrientation(100, 0,0,0);

    animate = face_eye_lid_bot_right->GetAnimator();
    animate->AddKeyOrientation(0, 1.6,0,0);
    animate->AddKeyOrientation(25, 2.1,0,0);
    animate->AddKeyOrientation(50, 1.6,0,0);
    animate->AddKeyOrientation(75, 2.1,0,0);
    animate->AddKeyOrientation(100, 1.6,0,0);

    /*   Torus* ss = new Torus(2,3,36,36);
    Joint* joint0 = new Joint(ss);

    Torus* ss2 = new Torus(2,3,36,36);
    Joint* joint_1 = new Joint(ss2);
    joint_1->AddChildJoint(joint0);
    //joint0->SetNewPosition(qglviewer::Vec(0,2,0));

    objects_.push_back(joint0);*/

    /*
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
    */

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
    //teste->SetRENDEROrientationAxes(true);

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

Object3D* SceneContainer::SelectedObject() {
    return selected_object_;
}

void SceneContainer::SetSelectedObject(Object3D* selected) {
    selected_object_ = selected;
}

void SceneContainer::SetSelectedPosition(qglviewer::Vec new_position) {
    if(selected_object_ == NULL) return;

    selected_object_->SetNewPosition(new_position);
}

void SceneContainer::SetSelectedOrientation(qglviewer::Quaternion new_orientation) {
    if(selected_object_ == NULL) return;

    selected_object_->SetNewOrientation(new_orientation);
}

void SceneContainer::DisplaySelectedPositionTrajectory(bool display) {
    if(selected_object_ == NULL) return;

    if(selected_object_->GetAnimator()!=NULL) {

        if(display) {
            selected_object_->GetAnimator()->CalculateTrajectory(TrajectoryObject::kPosition);
            extras_.push_back(selected_object_->GetAnimator()->GetTrajectory());
        }else{
            extras_.clear();
        }
    }
}

void SceneContainer::DisplaySelectedOrientationTrajectory(bool display) {
    if(selected_object_ == NULL) return;

    if(selected_object_->GetAnimator()!=NULL) {
        if(display) {
            selected_object_->GetAnimator()->CalculateTrajectory(TrajectoryObject::kOrientation);
            extras_.push_back(selected_object_->GetAnimator()->GetTrajectory());
        }else{
            extras_.clear();
        }
    }
}

void SceneContainer::AddCurrentPositionKeyframe() {
    if(selected_object_ == NULL) return;

    if(selected_object_->GetAnimator()==NULL) {
        ObjectAnimator* new_animator = new ObjectAnimator(selected_object_);
        animators_.push_back(new_animator);
    }
    selected_object_->GetAnimator()->AddKeyPosition(current_frame_,selected_object_->position());

}

void SceneContainer::AddCurrentOrientationKeyframe() {
    if(selected_object_ == NULL) return;

    if(selected_object_->GetAnimator()==NULL) {
        ObjectAnimator* new_animator = new ObjectAnimator(selected_object_);
        animators_.push_back(new_animator);
    }
    selected_object_->GetAnimator()->AddKeyOrientation(current_frame_,selected_object_->orientation());
}

void SceneContainer::RemoveCurrentPositionKeyframe() {
    if(selected_object_ == NULL) return;

    if(selected_object_->GetAnimator()!=NULL) {
        selected_object_->GetAnimator()->RemoveKeyPosition(current_frame_);
    }
}

void SceneContainer::RemoveCurrentOrientationKeyframe() {
    if(selected_object_ == NULL) return;

    if(selected_object_->GetAnimator()!=NULL) {
        selected_object_->GetAnimator()->RemoveKeyOrientation(current_frame_);
    }
}

bool SceneContainer::RenderBox()
{
    return render_box_over_object_;
}

void SceneContainer::SetRenderBox(bool box){
    render_box_over_object_ = box;
}

bool SceneContainer::DrawBones()
{
    return draw_bones_;
}

void SceneContainer::SetDrawBones(bool bones)
{
    draw_bones_ = bones;
}

bool SceneContainer::RenderOptions(int options_mask)
{
    if( (options_mask & render_options_) > 0 )
        return true;
    else
        return false;
}
