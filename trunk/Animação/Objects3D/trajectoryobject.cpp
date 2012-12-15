#include "trajectoryobject.h"
#include "Interpolation/objectanimator.h"
#include "Utils/scenecontainer.h"

TrajectoryObject::TrajectoryObject(ObjectAnimator* animator)
{
    animator_   = animator;
    quadric_    = NULL;
    radius_     = 1.0;
}

void TrajectoryObject::SetType(TrajectoryType type) {
    type_ = type;
    if(type_ == kOrientation){
        if(quadric_ == NULL)
            quadric_ = gluNewQuadric();
    }else if(quadric_!=NULL) {
        gluDeleteQuadric(quadric_);
        quadric_ = NULL;
    }
}

void TrajectoryObject::Update() {
    Update(SceneContainer::start_frame(), SceneContainer::end_frame());
}

void TrajectoryObject::Update(int start_frame, int end_frame) {
    positions_.clear();
    if( end_frame < start_frame ) {
        int aux = end_frame;
        end_frame = start_frame;
        start_frame = aux;
    }

    if(type_ == kPosition){
        for(int i = start_frame ; i <= end_frame ; i++ ) {
            positions_.push_back(animator_->PositionAt(i));
        }
    }else{
        qglviewer::Vec over(0,radius_,0);
        for(int i = start_frame ; i <= end_frame ; i++ ) {

            qglviewer::Quaternion ori = animator_->OrientationAt(i);
            qglviewer::Vec pos = ori.rotate(over);
            std::cout <<" OVER ROTATED i:" << i <<"(" <<pos.x << ", "<< pos.y << ", " << pos.z << ")" << std::endl;
            std::cout <<" ORI i:" << i <<"(" << ori[0] << ", "<< ori[1] << ", " <<ori[2] << ", " <<ori[3] << ")" << std::endl;
            positions_.push_back(ori.rotate(over));
        }
    }
}

void TrajectoryObject::DrawObject() {
    glPushMatrix();

    if(type_ == kOrientation){
        if(SceneContainer::AnimatePosition()) {
            qglviewer::Vec pos = animator_->PositionAt(SceneContainer::current_frame());
            glTranslated(pos.x,pos.y,pos.z);
        }
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glColor4d(1.0,1.0,1.0,0.5);
        gluSphere(quadric_,radius_-0.01,40,40);
        glPopAttrib();

    }
    DrawPositionsCurve();
    glPopMatrix();
}

void TrajectoryObject::DrawPositionsCurve() {
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_LIGHTING);

    glBegin(GL_LINE_STRIP);
    glColor3d(1,0,0);
    for(size_t i = 0 ; i < positions_.size() ; i++ ) {
        qglviewer::Vec pos = positions_.at(i);
        glVertex3d(pos.x,pos.y,pos.z);
    }
    glEnd();

    glPointSize(3.0f);
    glBegin(GL_POINTS);
    glColor3d(0,1,0);

    for(size_t i = 0 ; i < positions_.size() ; i++ ) {
        qglviewer::Vec pos = positions_.at(i);
        glVertex3d(pos.x,pos.y,pos.z);
    }
    glEnd();

    glPopAttrib();
}
