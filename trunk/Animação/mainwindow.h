#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTreeWidgetItem>

namespace Ui {
    class MainWindow;
}

class Joint;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    bool play_or_pause_;

    void updateObjectsRecursive(QTreeWidgetItem *item, Joint* parent);
public slots:
    void PlayPause();
    void Stop();
    void SelectedFramePause();
    void UpdateObjects();

private slots:
    void UpdateFrameCount(int new_total);
    void UpdateFPS(int new_fps);
    void UpdateSpeedControl(int new_speed_control);
    void UpdatePositionInterpolation(int new_speed_interpolation);
    void UpdateOrientationInterpolation(int new_orientation_interpolation);
    void UpdateFreeze();
};

#endif // MAINWINDOW_H
