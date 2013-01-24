#ifndef VIEWER_H
#define VIEWER_H

#include <QGLViewer/qglviewer.h>

#include <QGLShaderProgram>

class BezierQuadratic;
class Object3D;

class Viewer : public QGLViewer
{
    Q_OBJECT
public:
    explicit Viewer(QWidget* parent = 0);

    int current_shader_;

protected :
    virtual void draw();
    virtual void drawWithNames();
    virtual void init();
    virtual QString helpString() const;

    virtual void postSelection(const QPoint &point);

signals:
    void currentFrame(int frame);
    void signalUpdateObjects();

    void updateSelected(int);
public slots:
    void play();
    void pause();
    void stop();

    virtual void animate();
    void setCurrentFrame(int frame);

    void setCurrentShader(int shader);
    void releaseShader();
    void bindShader();

//    virtual void mousePressEvent(QMouseEvent *event);
private:
    BezierQuadratic* nova_;

    float grid_size_;
    int grid_div_;

    bool shader_enabled_;

    void postDraw();

    QGLShaderProgram shaderProgram;
};

#endif // VIEWER_H
