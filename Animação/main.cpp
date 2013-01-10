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
    return a.exec();
}
