#ifndef ANIMATION_H
#define ANIMATION_H

#include <QVector>
#include <QVector3D>
#include <QTimer>
#include <QObject>

class MainWindow;

class Animation : public QObject
{
    Q_OBJECT
public:
    Animation(MainWindow *mainwindow);

    MainWindow *mainwindow;

    QTimer timer;

    bool playing;

    QVector<QVector3D> frame;
    int sizeFrames;
    int currentFrame;

public slots:
    void jumpFrame();
    void play();
    void stop();
};

#endif // ANIMATION_H
