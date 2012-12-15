#include <QtGui/QApplication>
#include "mainwindow.h"

#include "Widgets/viewer.h"
#include "Widgets/timebar.h"
#include <QScrollArea>
#include <QFrame>
#include <QHBoxLayout>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

/*    Viewer v;
    v.show();

    QScrollArea scroll;
    TimeBar t;
    scroll.setWidget(&t);
    scroll.setFrameShape(QFrame::Panel);
    scroll.setFrameShadow(QFrame::Sunken);
    scroll.show();*/
    return a.exec();
}
