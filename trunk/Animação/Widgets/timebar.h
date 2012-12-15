#ifndef TIMEBAR_H
#define TIMEBAR_H

#include <QWidget>

class TimeBar : public QWidget
{
    Q_OBJECT
public:
    explicit TimeBar(QWidget *parent = 0);
    
private:
    int step_width_;

    int number_of_frames_;
    int current_frame_;
    QVector<int> key_frames_;

protected:
    virtual void paintEvent(QPaintEvent* event);
    virtual void mousePressEvent ( QMouseEvent * event );
signals:
    void SetSelectedFrame(int frame);
public slots:
    void SetCurrentFrame(int frame);
};

#endif // TIMEBAR_H
