#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Utils/scenecontainer.h"
#include "Interpolation/genericinterpolator.h"
#include "Objects3D/joint.h"

static QIcon play_icon;
static QIcon pause_icon;
static QIcon stop_icon;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    play_or_pause_ = true;
    selected_item_ = NULL;

    ui->setupUi(this);
    this->setWindowTitle(QString("Animation Studio"));
    connect( ui->button_play, SIGNAL(clicked()), ui->viewer, SLOT(Play()) );
    connect( ui->button_stop, SIGNAL(clicked()), ui->viewer, SLOT(Stop()));
    connect( ui->button_stop, SIGNAL(clicked()), this, SLOT(Stop()));

    connect(ui->button_play,SIGNAL(clicked()),this,SLOT(PlayPause()));

    connect(ui->viewer,SIGNAL(SignalUpdateObjects()),this,SLOT(UpdateObjects()));

    connect( ui->timebar, SIGNAL(SetSelectedFrame(int)), ui->viewer, SLOT(SetCurrentFrame(int)));
    connect( ui->timebar, SIGNAL(SetSelectedFrame(int)), this, SLOT(SelectedFramePause()) );
    connect( ui->viewer, SIGNAL(CurrentFrame(int)), ui->timebar, SLOT(SetCurrentFrame(int)));

    connect( ui->spin_frame_count, SIGNAL(valueChanged(int)), this, SLOT(UpdateFrameCount(int)));

    connect( ui->combo_velocity_control, SIGNAL(activated(int)), this, SLOT(UpdateSpeedControl(int)));

    connect( ui->combo_pos_interpolator, SIGNAL(activated(int)), this, SLOT(UpdatePositionInterpolation(int)));
    connect( ui->combo_ori_interpolator, SIGNAL(activated(int)), this, SLOT(UpdateOrientationInterpolation(int)));

    connect( ui->checkbox_freeze_pos, SIGNAL(clicked()), this, SLOT(UpdateFreeze()));
    connect( ui->checkbox_freeze_ori, SIGNAL(clicked()), this, SLOT(UpdateFreeze()));

    // Object 3D Manipulation

    connect( ui->line_edit_label, SIGNAL(textChanged(QString)), this, SLOT(UpdateSelectedLabel(QString)));

    connect( ui->add_keyframe_pos, SIGNAL(pressed()), this, SLOT(AddPositionKeyframe()));
    connect( ui->add_keyframe_ori, SIGNAL(pressed()), this, SLOT(AddOrientationKeyframe()));
    connect( ui->rem_keyframe_pos, SIGNAL(pressed()), this, SLOT(RemovePositionKeyframe()));
    connect( ui->rem_keyframe_ori, SIGNAL(pressed()), this, SLOT(RemoveOrientationKeyframe()));

    connect( ui->push_button_traj_pos, SIGNAL(toggled(bool)), this, SLOT(DisplayTrajectoryPosition(bool)));
    connect( ui->push_button_traj_ori, SIGNAL(toggled(bool)), this, SLOT(DisplayTrajectoryOrientation(bool)));



    //ui->button_play->setFixedSize(30,30);
    //ui->button_stop->setFixedSize(30,30);

    //ui->tool_box->setEnabled(false);

    this->showMaximized();

    play_icon = QIcon(QPixmap::fromImage(QImage(":/buttons/play.png")));
    pause_icon = QIcon(QPixmap::fromImage(QImage(":/buttons/pause.png")));
    stop_icon = QIcon(QPixmap::fromImage(QImage(":/buttons/stop.png")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PlayPause(){
    if(play_or_pause_){
        play_or_pause_ = false;
        ui->button_play->setIcon(pause_icon);
        ui->viewer->Play();
    }else{
        play_or_pause_ = true;
        ui->button_play->setIcon(play_icon);
        ui->viewer->Pause();
    }
}

void MainWindow::Stop() {
    if(!play_or_pause_) {
        play_or_pause_ = true;
        ui->button_play->setIcon(play_icon);
    }
}

void MainWindow::SelectedFramePause()
{
    play_or_pause_ = true;
    ui->viewer->Pause();
}

void MainWindow::UpdateObjects(){

    item_to_object_.clear();
    for( unsigned int i = 0 ; i < SceneContainer::HowManyObjects() ; i++ ) {
        Joint* object =  SceneContainer::ObjectAt(i);
        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(QString(object->label().c_str())));
        updateObjectsRecursive(item, object);
        ui->treeWidget->addTopLevelItem(item);
        item_to_object_[item] = object;
    }
    ui->treeWidget->expandAll();

    connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(UpdateCurrentSelected(QTreeWidgetItem*,int)));
    //ui->timebar->setKeyFrames((Object3D*)SceneContainer::ObjectAt(0));
    ui->timebar->update();    
}

void MainWindow::updateObjectsRecursive(QTreeWidgetItem *item, Joint* parent){
    for(int i = 0 ; i < parent->HowManyChilds() ; i++ ) {
        Joint *child = parent->ChildAt(i);
        QTreeWidgetItem *childitem = new QTreeWidgetItem(item,QStringList(QString(child->label().c_str())));
        updateObjectsRecursive(childitem, child);
        item_to_object_[childitem] = child;
    }
    if(parent->ChildObject()!=NULL){
       new QTreeWidgetItem(item,QStringList(QString(parent->ChildObject()->label().c_str())));
    }
}

void MainWindow::UpdateCurrentSelected(QTreeWidgetItem *item, int column) {
    selected_item_ = item;
    if(item == NULL) return;
    if( item_to_object_.find(item) != item_to_object_.end() ) {
        Joint* object = item_to_object_[item];    
        UpdateSelectedInfo(object);
        ui->timebar->setKeyFrames(object);
        ui->timebar->repaint();
    }
}

void MainWindow::UpdateFrameCount(int new_total) {
    SceneContainer::SetFrameRange(0,new_total);
    ui->timebar->SetNumberOfFrames(new_total+1);
}

void MainWindow::UpdateFPS(int new_fps) {
}

void MainWindow::UpdateSpeedControl(int new_speed_control) {
    switch(new_speed_control) {
    case 0:
        GenericInterpolator::setSpeedFunction(GenericInterpolator::SF_CONSTANT);
        break;
    case 1:
        GenericInterpolator::setSpeedFunction(GenericInterpolator::SF_EASE_IN_OUT_SIN);
        break;
    case 2:
        GenericInterpolator::setSpeedFunction(GenericInterpolator::SF_EASE_IN_POW);
        break;
    default:
        GenericInterpolator::setSpeedFunction(GenericInterpolator::SF_EASE_OUT_ROOT);
        break;
    }
}

void MainWindow::UpdatePositionInterpolation(int new_speed_interpolation) {
    switch(new_speed_interpolation) {
    case 0:
        SceneContainer::SetPositionInterpolationType(PosInterpolator::kLinear);
        break;
    default:
        SceneContainer::SetPositionInterpolationType(PosInterpolator::kCatmullRoom);
        break;
    }
}

void MainWindow::UpdateOrientationInterpolation(int new_orientation_interpolation) {
    switch(new_orientation_interpolation) {
    case 0:
        SceneContainer::SetOrientationInterpolationType(OriInterpolator::kSlerp);
        break;
    default:
        SceneContainer::SetOrientationInterpolationType(OriInterpolator::kBezier);
        break;
    }
}

void MainWindow::UpdateFreeze() {
    SceneContainer::SetAnimated(!ui->checkbox_freeze_pos->isChecked(),!ui->checkbox_freeze_ori->isChecked());
}

void MainWindow::UpdateSelectedInfo(Joint* object) {
    if(SceneContainer::SelectedObject()!=NULL){
       SceneContainer::SelectedObject()->SetDrawBoundingBox(false);
       SceneContainer::SelectedObject()->SetDrawOrientationAxes(false);
    }
    SceneContainer::SetSelectedObject(object);

    if(object==NULL) {
        ui->tool_box->setEnabled(false);
        return;
    }
    ui->tool_box->setEnabled(false);
    SceneContainer::SelectedObject()->SetDrawBoundingBox(true);
    SceneContainer::SelectedObject()->SetDrawOrientationAxes(true);


    disconnect( ui->spin_pos_x, 0, this, 0);
    disconnect( ui->spin_pos_y, 0, this, 0);
    disconnect( ui->spin_pos_z, 0, this, 0);

    disconnect( ui->spin_ori_x, 0, this, 0);
    disconnect( ui->spin_ori_y, 0, this, 0);
    disconnect( ui->spin_ori_z, 0, this, 0);

    ui->line_edit_label->setText(QString(object->label().c_str()));
    ui->spin_pos_x->setValue(object->position().x);
    ui->spin_pos_y->setValue(object->position().y);
    ui->spin_pos_z->setValue(object->position().z);

    qglviewer::Quaternion q = object->orientation();
    double angle_rx = atan2(2.0*(q[3]*q[0] + q[1]*q[2]),1.0-2.0*(q[0]*q[0] + q[1]*q[1]));
    double angle_ry = asin(2.0*(q[3]*q[1] - q[2]*q[0]));
    double angle_rz = atan2(2.0*(q[3]*q[2] + q[0]*q[1]),1.0-2.0*(q[1]*q[1] + q[2]*q[2]));

    ui->spin_ori_x->setValue((angle_rx*180.0)/(6.28));
    ui->spin_ori_y->setValue((angle_ry*180.0)/(6.28));
    ui->spin_ori_z->setValue((angle_rz*180.0)/(6.28));

    connect( ui->spin_pos_x, SIGNAL(valueChanged(double)), this, SLOT(UpdateCurrentPosition()));
    connect( ui->spin_pos_y, SIGNAL(valueChanged(double)), this, SLOT(UpdateCurrentPosition()));
    connect( ui->spin_pos_z, SIGNAL(valueChanged(double)), this, SLOT(UpdateCurrentPosition()));

    connect( ui->spin_ori_x, SIGNAL(valueChanged(double)), this, SLOT(UpdateCurrentOrientation()));
    connect( ui->spin_ori_y, SIGNAL(valueChanged(double)), this, SLOT(UpdateCurrentOrientation()));
    connect( ui->spin_ori_z, SIGNAL(valueChanged(double)), this, SLOT(UpdateCurrentOrientation()));

    ui->tool_box->setEnabled(true);
    ui->viewer->updateGL();
}

void MainWindow::UpdateSelectedLabel(QString label){
    if(selected_item_ !=NULL) {
        selected_item_->setText(0,label);
    }
    if(SceneContainer::SelectedObject()!=NULL)
        SceneContainer::SelectedObject()->SetLabel(label.toStdString().c_str());

}

void MainWindow::UpdateCurrentPosition() {
    qglviewer::Vec current_p(ui->spin_pos_x->value(),ui->spin_pos_y->value(),ui->spin_pos_z->value());
    SceneContainer::SetSelectedPosition(current_p);
    ui->viewer->updateGL();
}

void MainWindow::UpdateCurrentOrientation() {
    qglviewer::Quaternion a,b,c,d;
    a.setAxisAngle(qglviewer::Vec(1,0,0),ui->spin_ori_x->value());
    b.setAxisAngle(qglviewer::Vec(0,1,0),ui->spin_ori_y->value());
    c.setAxisAngle(qglviewer::Vec(0,0,1),ui->spin_ori_y->value());
    d = a*b*c;
    d.normalize();
    SceneContainer::SetSelectedOrientation(d);
    ui->viewer->updateGL();
}

void MainWindow::DisplayTrajectoryPosition(bool display) {
    SceneContainer::DisplaySelectedPositionTrajectory(display);
    ui->viewer->updateGL();
}

void MainWindow::DisplayTrajectoryOrientation(bool display) {
    SceneContainer::DisplaySelectedOrientationTrajectory(display);
    ui->viewer->updateGL();
}

void  MainWindow::AddPositionKeyframe() {
    SceneContainer::AddCurrentPositionKeyframe();
    ui->timebar->setKeyFrames(SceneContainer::SelectedObject());
    ui->timebar->repaint();
}

void  MainWindow::AddOrientationKeyframe() {
    SceneContainer::AddCurrentOrientationKeyframe();
    ui->timebar->setKeyFrames(SceneContainer::SelectedObject());
    ui->timebar->repaint();
}

void  MainWindow::RemovePositionKeyframe() {
    SceneContainer::RemoveCurrentPositionKeyframe();
    ui->timebar->setKeyFrames(SceneContainer::SelectedObject());
    ui->timebar->repaint();
}

void  MainWindow::RemoveOrientationKeyframe() {
    SceneContainer::RemoveCurrentOrientationKeyframe();
    ui->timebar->setKeyFrames(SceneContainer::SelectedObject());
    ui->timebar->repaint();
}
