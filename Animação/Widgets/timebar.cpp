#include "timebar.h"
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>

TimeBar::TimeBar(QWidget *parent) :
    QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    number_of_frames_ = 101;
    current_frame_ = 0;

    int const_height = 50;
    step_width_ = 7;
    //this->setMinimumHeight(const_height);
    //this->setMaximumHeight(const_height);
    this->setGeometry(0,0,100*(step_width_-1)+1,const_height);
    this->setMinimumWidth(100*(step_width_-1)+1);
}
#include <iostream>
void TimeBar::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    //painter.setRenderHint(QPainter::Antialiasing);

    QColor base_color(255,255,255);
    QColor keyframe_color(0,200,255);
    QColor alternate_color(200,200,200);
    QColor selection_color(255,255,255);

    //double step_width = ((double)this->width()) / ((double)number_of_frames_);
    //step_width_ =
    //step_width_ = step_width_ > 1 ? step_width_ : 1;
    int box_width = step_width_;
    int h_step = box_width-1;
    int v_step = height()-2;

    for(int i = 0 ; i < number_of_frames_ ; i++ ){

        painter.setPen(Qt::NoPen);
        // testing purpose only. change i = keyframe later.
        if(i%5 == 0) {
            painter.setBrush(keyframe_color);
        }else

        /*if(i%2 == 0) */painter.setBrush(alternate_color);
        /*else         painter.setBrush(alternate_color);*/


        /*double current = step_width*i;
        double next = current + step_width;
        painter.drawRect(1 + current,1,step_width-1,v_step);
        painter.setPen(Qt::SolidLine);
        painter.drawLine(next,1,next,height()-1);*/

        painter.drawRect(1 + (h_step)*i,1,h_step-1,v_step);
        painter.setPen(Qt::SolidLine);
        painter.drawLine((h_step)*(i+1),1,(h_step)*(i+1),height()-1);

    }

    int extreme_right = (number_of_frames_*(box_width-1));

    painter.drawLine(0,0,0,height());
    painter.drawLine(0,0,extreme_right,0);
    painter.drawLine(0,height()-1,extreme_right,height()-1);
    painter.drawLine(extreme_right,0,extreme_right,height());

    painter.setBrush(Qt::NoBrush);
    painter.setPen(selection_color);
    painter.drawRect((box_width-1)*current_frame_,0,box_width-1,height()-1);
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
