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

protected :
  virtual void draw();
  virtual void init();
  virtual QString helpString() const;

signals:
    void CurrentFrame(int frame);
    void SignalUpdateObjects();
public slots:
    void Play();
    void Pause();
    void Stop();

    virtual void animate();
    void SetCurrentFrame(int frame);

    void SetCurrentShader(int shader);
    void ReleaseShader();
    void BindShader();

private:
    BezierQuadratic* nova_;

    float grid_size_;
    int grid_div_;

    bool shader_enabled_;

    void postDraw();

    QGLShaderProgram shaderProgram;
};

#endif // VIEWER_H
