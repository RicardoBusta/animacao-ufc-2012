#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTreeWidgetItem>

namespace Ui {
class MainWindow;
}

class Joint;
class Object3D;
class QComboBox;

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

    std::map<QTreeWidgetItem*, Object3D*> item_to_object_;
    std::map<Object3D*, QTreeWidgetItem*> object_to_item_;

    std::map<int,int> index_id_;

public slots:
    void playPause();
    void stop();
    void selectedFramePause();
    void updateObjects();

private slots:
    void updateFrameCount(int new_total);
    void updateFPS(int new_fps);
    void updateSpeedControl(int new_speed_control);
    void updatePositionInterpolation(int new_speed_interpolation);
    void updateOrientationInterpolation(int new_orientation_interpolation);
    void updateFreeze();
    void updateCurrentSelected(QTreeWidgetItem *item, QTreeWidgetItem * other);
    void updateSelectedLabel(QString label);
    void updateCurrentPosition();
    void updateCurrentOrientation();
    void updateRenderBox(bool box);
    void updateRenderBones(bool bones);
    void updateCurrentScene(int scene);
    void displayTrajectoryPosition(bool display);
    void displayTrajectoryOrientation(bool display);
    void updateSelectedInfo(Object3D *object);
    void addPositionKeyframe();
    void addOrientationKeyframe();
    void removePositionKeyframe();
    void removeOrientationKeyframe();
    void setSelectedByID(int);
    void setInverse(int);
    void changeGoal();

    //IK
    void tabChanged(int tab);
    void fillStart();
    void fillEnd(int index);
    void fillComboBox(Joint *this_obj, QComboBox *combo, bool compensate=false, int compensation=0);
    void setIKTarget();
    void saveAngles();

    void changeCurrentFrame(int x);
};

#endif // MAINWINDOW_H
