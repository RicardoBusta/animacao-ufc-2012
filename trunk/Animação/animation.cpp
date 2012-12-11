#include "animation.h"

#include "mainwindow.h"

Animation::Animation(MainWindow *mainwindow)
{
    this->mainwindow = mainwindow;

    int currentFrame = 0;

    for(int i=0;i<100;i++){
        frame.push_back(QVector3D(0.01f*i,0.01f*i,0.01f*i));
    }

    connect(&timer,SIGNAL(timeout()),this,SLOT(jumpFrame()));
}

void Animation::jumpFrame()
{
    currentFrame ++;
    currentFrame = currentFrame%frame.size();
    mainwindow->updateFrame();
}

void Animation::play()
{
    timer.start(10);
}

void Animation::stop()
{
    timer.stop();
}
