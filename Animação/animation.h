#ifndef ANIMATION_H
#define ANIMATION_H

#include <QVector>
#include <QVector3D>
#include <QTimer>

class Animation
{
    //Q_OBJECT
public:
    Animation();

    QTimer timer;

    QVector<QVector3D> frame;

    int currentFrame;
    void play();
    void pause();
    void stop();
};

#endif // ANIMATION_H
