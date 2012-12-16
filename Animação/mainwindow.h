#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTreeWidgetItem>
#include "Objects3D/objectinfotree.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    bool play_or_pause_;

    void updateObjectsRecursive(QTreeWidgetItem *item, ObjectInfoTree *node);
public slots:
    void UpdateAnimators();
    void PlayPause();
    void SelectedFramePause();
    void UpdateObjects();
};

#endif // MAINWINDOW_H
