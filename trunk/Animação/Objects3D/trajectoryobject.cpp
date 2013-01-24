#include "trajectoryobject.h"
#include "Interpolation/objectanimator.h"
#include "Utils/scenecontainer.h"

TrajectoryObject::TrajectoryObject(ObjectAnimator* animator)
{
    animator_   = animator;
    quadric_    = NULL;
    radius_     = 3.0;
}

TrajectoryObject::~TrajectoryObject(){

}

void TrajectoryObject::setType(TrajectoryType type) {
    type_ = type;
    if(type_ == kOrientation){
        if(quadric_ == NULL)
            quadric_ = gluNewQuadric();
    }else if(quadric_!=NULL) {
        gluDeleteQuadric(quadric_);
        quadric_ = NULL;
    }
}

void TrajectoryObject::update() {
    update(SceneContainer::start_frame(), SceneContainer::end_frame());
}

void TrajectoryObject::update(int start_frame, int end_frame) {
    keyframes_.clear();

    positions_.clear();
    if( end_frame < start_frame ) {
        int aux = end_frame;
        end_frame = start_frame;
        start_frame = aux;
    }

    if(type_ == kPosition){
        for(int i = start_frame ; i <= end_frame ; i++ ) {
            positions_.push_back(animator_->globalPositionAt(i));
        }
        for(uint i=0; i < animator_->getKeyPositions()->size(); i++){
            PositionStep pos = animator_->getKeyPositions()->at(i);
            keyframes_.push_back( pos.position_ );
        }
    }else{
        qglviewer::Vec over(0,radius_,0);
        for(int current_frame = start_frame ; current_frame <= end_frame ; current_frame++ ) {
            //std::cout <<" CURRENT_FRAME: " << current_frame << " of " << end_frame << std::endl;
            qglviewer::Quaternion ori = animator_->globalOrientationAt(current_frame);
            qglviewer::Vec pos = ori.rotate(over);
#ifdef DEBUG_TEXT
            std::cout <<" OVER ROTATED i:" << i <<"(" <<pos.x << ", "<< pos.y << ", " << pos.z << ")" << std::endl;
            std::cout <<" ORI i:" << i <<"(" << ori[0] << ", "<< ori[1] << ", " <<ori[2] << ", " <<ori[3] << ")" << std::endl;
#endif
            positions_.push_back( pos );
        }
        for(uint i=0; i < animator_->getKeyOrientations()->size(); i++){
            OrientationStep ori = animator_->getKeyOrientations()->at(i);
            qglviewer::Vec pos = ori.orientation_.rotate(over);
            keyframes_.push_back( pos );
        }
    }
}

void TrajectoryObject::drawObject(int) {
    glPushMatrix();

    if(type_ == kOrientation){
        qglviewer::Vec pos = animator_->globalPositionAt(SceneContainer::current_frame());
        glTranslated(pos.x,pos.y,pos.z);
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glColor4d(1.0,1.0,1.0,0.5);
        gluSphere(quadric_,radius_-0.01,40,40);
        glPopAttrib();

    }
    drawPositionsCurve();
    glPopMatrix();
}

void TrajectoryObject::drawPositionsCurve() {
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_LIGHTING);

    glBegin(GL_LINE_STRIP);
    if(type_ == kOrientation){
        glColor3d(0.9,0.5,0);
    }else{
        glColor3d(0,0.5,0.8);
    }
    for(size_t i = 0 ; i < positions_.size() ; i++ ) {
        qglviewer::Vec pos = positions_.at(i);
        glVertex3d(pos.x,pos.y,pos.z);
    }
    glEnd();

    glPointSize(3.0f);
    glBegin(GL_POINTS);

    if(type_ == kOrientation){
        glColor3d(1,0.7,0);
    }else{
        glColor3d(0,1,1);
    }

    for(size_t i = 0 ; i < positions_.size() ; i++ ) {
        qglviewer::Vec pos = positions_.at(i);
        glVertex3d(pos.x,pos.y,pos.z);
    }
    glEnd();

    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glColor3d(1,1,1);

    for(uint i = 0 ; i < keyframes_.size() ; i++ ) {
        qglviewer::Vec pos = keyframes_.at(i);
        glVertex3d(pos.x,pos.y,pos.z);
    }
    glEnd();

    glPopAttrib();
}
