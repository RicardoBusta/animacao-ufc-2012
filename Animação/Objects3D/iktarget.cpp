#include "iktarget.h"
#include "object3d.h"
#include "joint.h"

#include "Interpolation/objectanimator.h"
#include "Utils/scenecontainer.h"

#include "Utils/iksolver.h"

std::map<int,IKTarget*> IKTarget::ik_targets_;

IKTarget* IKTarget::GetIKTargetById(int id) {
    if(ik_targets_.find(id)!=ik_targets_.end())
        return ik_targets_[id];
    return NULL;
}

IKTarget::IKTarget(qglviewer::Vec pos) {
    Object3D::setNewPosition(pos);
    ik_targets_[id()] = this;
    draw_effector_ = true;
    draw_bones_ = true;
    inverse_ = true;
}

void IKTarget::setInverseUsable(bool use_inverse) {
    inverse_ = use_inverse;
}

void IKTarget::AddChildBone(Joint* bone) {
    bones_.push_back(bone);
}

void IKTarget::SetDrawProperties(bool draw_effector, bool draw_bones) {
    draw_effector_ = draw_effector;
    draw_bones_ = draw_bones;
}

void IKTarget::Solve() {
    IKSolver solver;
    solver.solve(&bones_,position(),inverse_?1:0);
}

void IKTarget::SaveKeyframe() {
    for(int i = 0 ; i < bones_.size() ; i++){
        Joint* bone = bones_.at(i);
        if(bone->getAnimator()!=NULL){
            ObjectAnimator* animator = bone->getAnimator();
            animator->addKeyPosition(SceneContainer::current_frame(),bone->position());
            animator->addKeyOrientation(SceneContainer::current_frame(),bone->orientation());
        }
    }
}

void IKTarget::drawObject(int depth) {

    qglviewer::Vec goal = position();

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glPointSize(10);
    glBegin(GL_POINTS);

    glColor3f(0,1,0);
    //glVertex3f(goal.x,goal.y,goal.z);
    glVertex3f(0,0,0);
    glEnd();

    glPopAttrib();
}

void IKTarget::DrawGlobal(){
    qglviewer::Vec effector = bones_.at(bones_.size()-1)->globalPosition();

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(1,0,0);
    glVertex3f(effector.x,effector.y, effector.z);
    glEnd();

    glPointSize(2);
    glBegin(GL_LINE_STRIP);
    glColor3f(1,1,0);

    for(int i = 0 ; i < bones_.size()-1; i++) {
        qglviewer::Vec begin;
        begin = bones_.at(i)->globalPosition();
        glVertex3f(begin.x,begin.y,begin.z);
    }
    glVertex3f(effector.x,effector.y, effector.z);
    glEnd();

    glPopAttrib();
}
