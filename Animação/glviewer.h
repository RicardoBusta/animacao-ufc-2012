#ifndef GLVIEWER_H
#define GLVIEWER_H

#include <qglviewer.h>

class GLViewer : public QGLViewer
{
    Q_OBJECT
public:
    explicit GLViewer(QWidget *parent = 0);

private:
    void postDraw();

    void draw();
    void init();
signals:
    
public slots:
    
};

#endif // GLVIEWER_H
