#include "animation.h"

Animation::Animation()
{
    int currentFrame = 0;

    for(int i=0;i<100;i++){
        frame.push_back(QVector3D(0.1f*i,0.1f*i,0.1f*i));
    }

    //connect()
}


void Animation::play()
{
}
