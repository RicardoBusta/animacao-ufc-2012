#include "trajectoryobject.h"
#include "objectanimator.h"
#include "scenecontainer.h"

TrajectoryObject::TrajectoryObject(ObjectAnimator* animator)
{
    animator_ = animator;
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

    for(int i = start_frame ; i <= end_frame ; i++ ) {
        positions_.push_back(animator_->PositionAt(i));
    }
}

void TrajectoryObject::DrawObject() {
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
