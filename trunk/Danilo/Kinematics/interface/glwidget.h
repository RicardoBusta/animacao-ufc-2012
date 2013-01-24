#ifndef GLWIDGET_H
#define GLWIDGET_H
#include "math/vec4.h"
#include <QGLWidget>
#include <QTimer>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public slots:
    void setGoal(Vec4 g);
    void setType(int t);
public:
    explicit GLWidget(QWidget *parent = 0);
    QTimer timer;
    Vec4 goal;
    int type;

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);


};

#endif // GLWIDGET_H
