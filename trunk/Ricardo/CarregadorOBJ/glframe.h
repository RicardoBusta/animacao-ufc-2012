#ifndef GLFRAME_H
#define GLFRAME_H

#include <QWidget>
#include <glwidget.h>

class GLFrame : public QWidget
{
    Q_OBJECT
public:
    explicit GLFrame(QWidget *parent = 0);
    ~GLFrame();
    
    GLWidget *glwidget;
private:
    void resizeEvent(QResizeEvent *);


signals:
    
public slots:
    
};

#endif // GLFRAME_H
