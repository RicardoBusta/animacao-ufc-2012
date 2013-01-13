#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTreeWidgetItem>

namespace Ui {
    class MainWindow;
}

class Joint;
class Object3D;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    bool play_or_pause_;

    QTreeWidgetItem* selected_item_;

    void updateObjectsRecursive(QTreeWidgetItem *item, Joint* parent);

    std::map<QTreeWidgetItem*, Joint*> item_to_object_;

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
    void UpdateCurrentSelected(QTreeWidgetItem *item, int column);
    void UpdateSelectedLabel(QString label);
    void UpdateCurrentPosition();
    void UpdateCurrentOrientation();
    void UpdateRenderBox(bool box);
    void DisplayTrajectoryPosition(bool display);
    void DisplayTrajectoryOrientation(bool display);
    void UpdateSelectedInfo(Object3D *object);
    void AddPositionKeyframe();
    void AddOrientationKeyframe();
    void RemovePositionKeyframe();
    void RemoveOrientationKeyframe();
};

#endif // MAINWINDOW_H
