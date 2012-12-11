#ifndef GLVIEWER_H
#define GLVIEWER_H

#include <qglviewer.h>

class Animation;

class GLViewer : public QGLViewer
{
    Q_OBJECT
public:
    explicit GLViewer(QWidget *parent = 0);

    Animation *animation;
private:
    void draw();
    void init();

    void postDraw();

    bool ortho;
signals:
    
public slots:
    
};

#endif // GLVIEWER_H
