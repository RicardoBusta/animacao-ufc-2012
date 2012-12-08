#ifndef VIEWER_H
#define VIEWER_H

#include <QGLViewer/qglviewer.h>

class BezierQuadratic;

class Viewer : public QGLViewer
{
    Q_OBJECT
public:

protected :
  virtual void draw();
  virtual void init();
  virtual QString helpString() const;

signals:

public slots:

private:
    BezierQuadratic* nova_;

};

#endif // VIEWER_H
