#include "timebar.h"
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include "Objects3D/object3d.h"
#include "Interpolation/objectanimator.h"
#include "Interpolation/animation_step.h"

TimeBar::TimeBar(QWidget *parent) :
    QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    number_of_frames_ = 101;
    current_frame_ = 0;
    step_width_ = 7;

    SetNumberOfFrames(number_of_frames_);
}
void TimeBar::SetNumberOfFrames(int total) {
    number_of_frames_ = total;

    int const_height = 30;
    //this->setGeometry(0,0,(number_of_frames_)*(step_width_-1)+1,const_height);
    this->setFixedSize((number_of_frames_)*(step_width_-1)+1,const_height);
    this->setMinimumWidth((number_of_frames_)*(step_width_-1)+1);
    if(current_frame_ >= number_of_frames_) {
        SetCurrentFrame(number_of_frames_ -1);
        emit SetSelectedFrame(current_frame_);
    }

}

void TimeBar::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    //painter.setRenderHint(QPainter::Antialiasing);

    QColor frame_base_color(255,255,255);
    QColor frame_alternate_color(230,230,230);
    QColor frame_border_color(200,200,200);

    QColor keyframe_pos_color(0,200,255);
    QColor keyframe_pos_border_color(0,150,200);
    QColor keyframe_ori_color(255,150,150);
    QColor keyframe_ori_border_color(205,100,100);

    QColor selection_color(0,0,0);

    //double step_width = ((double)this->width()) / ((double)number_of_frames_);
    //step_width_ =
    //step_width_ = step_width_ > 1 ? step_width_ : 1;
    int box_width = step_width_;
    int h_step = box_width-1;
    int v_step = height()-2;

    painter.setPen(Qt::SolidLine);
    painter.setPen(frame_border_color);

    painter.setBrush(frame_base_color);
    for(int i = 0 ; i < number_of_frames_ ; i+=2 ){
        painter.drawRect((h_step)*i,0,h_step,(v_step/2));
        painter.drawRect((h_step)*i,(v_step/2),h_step,(v_step/2));
    }
    painter.setBrush(frame_alternate_color);
    for(int i = 1 ; i < number_of_frames_ ; i+=2 ){
        painter.drawRect((h_step)*i,0,h_step,(v_step/2));
        painter.drawRect((h_step)*i,(v_step/2),h_step,(v_step/2));
    }

    painter.setPen(keyframe_pos_border_color);
    painter.setBrush(keyframe_pos_color);
    for(int i=0;i<pos_key_frames_.size();i++){
        painter.drawRect((h_step)*pos_key_frames_.at(i),0,h_step,(v_step/2));
    }
    painter.setPen(keyframe_ori_border_color);
    painter.setBrush(keyframe_ori_color);
    for(int i=0;i<ori_key_frames_.size();i++){
        painter.drawRect((h_step)*pos_key_frames_.at(i),(v_step/2),h_step,(v_step/2));
    }

    int extreme_right = (number_of_frames_*(box_width-1));

    //    painter.drawLine(0,0,0,height());
    //    painter.drawLine(0,0,extreme_right,0);
    //    painter.drawLine(0,height()-1,extreme_right,height()-1);
    //    painter.drawLine(extreme_right,0,extreme_right,height());

    painter.setBrush(Qt::NoBrush);
    painter.setPen(selection_color);
    painter.drawRect(0,0,extreme_right,v_step);

    painter.setBrush(Qt::BDiagPattern);
    painter.setPen(selection_color);
    painter.drawRect((h_step)*current_frame_,0,h_step,v_step);
    painter.end();
}

void TimeBar::mousePressEvent ( QMouseEvent * event ) {
    if(rect().contains(event->pos())) {
        int select = event->pos().x() / (step_width_-1);
        if(select < number_of_frames_) {
            current_frame_ = select;
            update();
            emit SetSelectedFrame(current_frame_);
        }
    }
}

void TimeBar::SetCurrentFrame(int frame) {
    current_frame_ = frame < number_of_frames_ ? frame : number_of_frames_-1;
    update();
}


void TimeBar::setKeyFrames(Object3D *object)
{
    this->pos_key_frames_.clear();
    this->ori_key_frames_.clear();

    //std::vector<OrientationStep> *orivec = &object->GetAnimator()->GetKeyOrientations();
    //std::vector<PositionStep> *posvec = &object->GetAnimator()->GetKeyPositions();

    for(int i=0;i<object->GetAnimator()->GetKeyOrientations()->size();i++){
        ori_key_frames_.push_back(object->GetAnimator()->GetKeyOrientations()->at(i).frame_);
    }
    for(int i=0;i<object->GetAnimator()->GetKeyPositions()->size();i++){
        pos_key_frames_.push_back(object->GetAnimator()->GetKeyPositions()->at(i).frame_);
    }
}
