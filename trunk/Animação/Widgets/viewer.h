#ifndef VIEWER_H
#define VIEWER_H

#include <QGLViewer/qglviewer.h>

class BezierQuadratic;

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
public slots:
    void Play();
    void Pause();
    void Stop();

    virtual void animate();
    void SetCurrentFrame(int frame);

private:
    BezierQuadratic* nova_;

    float grid_size_;
    int grid_div_;

    void postDraw();
};

#endif // VIEWER_H
