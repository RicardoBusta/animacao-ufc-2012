#include "animation.h"

#include "mainwindow.h"

Animation::Animation(MainWindow *mainwindow)
{
    this->mainwindow = mainwindow;

    currentFrame = 0;

    playing = false;

    for(int i=0;i<500;i++){
        frame.push_back(QVector3D(0.001f*i,0.001f*i,0.001f*i));
    }

    sizeFrames = frame.size();

    connect(&timer,SIGNAL(timeout()),this,SLOT(jumpFrame()));
}

void Animation::jumpFrame()
{
    currentFrame ++;
    currentFrame = currentFrame%sizeFrames;
    mainwindow->updateFrame();
}

void Animation::play()
{
    if(playing){
        playing = false;
        timer.stop();
    }else{
        playing = true;
        timer.start(1000.0/60.0);
    }
}

void Animation::stop()
{
    playing = false;
    timer.stop();
    currentFrame = 0;
    mainwindow->updateFrame();
}
