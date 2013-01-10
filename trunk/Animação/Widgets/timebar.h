#ifndef TIMEBAR_H
#define TIMEBAR_H

#include <QWidget>

class Object3D;

class TimeBar : public QWidget
{
    Q_OBJECT
public:
    explicit TimeBar(QWidget *parent = 0);
    
    void SetNumberOfFrames(int total);
    void setKeyFrames(Object3D* object);
private:
    int step_width_;

    int number_of_frames_;
    int current_frame_;
    QVector<int> pos_key_frames_;
    QVector<int> ori_key_frames_;

protected:
    virtual void paintEvent(QPaintEvent* event);
    virtual void mousePressEvent ( QMouseEvent * event );
signals:
    void SetSelectedFrame(int frame);
public slots:
    void SetCurrentFrame(int frame);
};

#endif // TIMEBAR_H
