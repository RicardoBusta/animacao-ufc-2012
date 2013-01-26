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
    ui->setupUi(this);

    play_or_pause_ = true;
    selected_item_ = NULL;
    SceneContainer::viewer_reference_ = ui->viewer;

    this->setWindowTitle(QString("Animation Studio"));
    connect( ui->button_play, SIGNAL(clicked()), ui->viewer, SLOT(play()) );
    connect( ui->button_stop, SIGNAL(clicked()), ui->viewer, SLOT(stop()));
    connect( ui->button_stop, SIGNAL(clicked()), this, SLOT(stop()));

    connect(ui->button_play,SIGNAL(clicked()),this,SLOT(playPause()));

    connect(ui->viewer,SIGNAL(signalUpdateObjects()),this,SLOT(updateObjects()));

    connect( ui->timebar, SIGNAL(setSelectedFrame(int)), ui->viewer, SLOT(setCurrentFrame(int)));
    connect( ui->timebar, SIGNAL(setSelectedFrame(int)), this, SLOT(selectedFramePause()) );
    connect( ui->viewer, SIGNAL(currentFrame(int)), ui->timebar, SLOT(setCurrentFrame(int)));

    connect( ui->spin_frame_count, SIGNAL(valueChanged(int)), this, SLOT(updateFrameCount(int)));

    connect( ui->combo_velocity_control, SIGNAL(activated(int)), this, SLOT(updateSpeedControl(int)));

    connect( ui->combo_pos_interpolator, SIGNAL(activated(int)), this, SLOT(updatePositionInterpolation(int)));
    connect( ui->combo_ori_interpolator, SIGNAL(activated(int)), this, SLOT(updateOrientationInterpolation(int)));

    connect( ui->checkbox_freeze_pos, SIGNAL(clicked()), this, SLOT(updateFreeze()));
    connect( ui->checkbox_freeze_ori, SIGNAL(clicked()), this, SLOT(updateFreeze()));

    // Object 3D Manipulation

    connect( ui->line_edit_label, SIGNAL(textChanged(QString)), this, SLOT(updateSelectedLabel(QString)));

    connect( ui->add_keyframe_pos, SIGNAL(pressed()), this, SLOT(addPositionKeyframe()));
    connect( ui->add_keyframe_ori, SIGNAL(pressed()), this, SLOT(addOrientationKeyframe()));
    connect( ui->rem_keyframe_pos, SIGNAL(pressed()), this, SLOT(removePositionKeyframe()));
    connect( ui->rem_keyframe_ori, SIGNAL(pressed()), this, SLOT(removeOrientationKeyframe()));

    connect( ui->push_button_traj_pos, SIGNAL(toggled(bool)), this, SLOT(displayTrajectoryPosition(bool)));
    connect( ui->push_button_traj_ori, SIGNAL(toggled(bool)), this, SLOT(displayTrajectoryOrientation(bool)));

    //render
    connect( ui->checkbox_render_box, SIGNAL(toggled(bool)), this, SLOT(updateRenderBox(bool)) );
    connect( ui->checkBox_render_bones, SIGNAL(toggled(bool)), this, SLOT(updateRenderBones(bool)) );

    connect( ui->comboBox_shader, SIGNAL(currentIndexChanged(int)), ui->viewer, SLOT(setCurrentShader(int)) );

    //scene
    connect( ui->comboBox_scene, SIGNAL(currentIndexChanged(int)), this, SLOT(updateCurrentScene(int)) );

    connect( ui->viewer, SIGNAL(updateSelected(int)), this, SLOT(setSelectedByID(int)) );


    // interface
    this->showMaximized();

    play_icon = QIcon(QPixmap::fromImage(QImage(":/buttons/play.png")));
    pause_icon = QIcon(QPixmap::fromImage(QImage(":/buttons/pause.png")));
    stop_icon = QIcon(QPixmap::fromImage(QImage(":/buttons/stop.png")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playPause(){
    if(play_or_pause_){
        play_or_pause_ = false;
        ui->button_play->setIcon(pause_icon);
        ui->viewer->play();
    }else{
        play_or_pause_ = true;
        ui->button_play->setIcon(play_icon);
        ui->viewer->pause();
    }
}

void MainWindow::stop() {
    if(!play_or_pause_) {
        play_or_pause_ = true;
        ui->button_play->setIcon(play_icon);
    }
}

void MainWindow::selectedFramePause()
{
    play_or_pause_ = true;
    ui->viewer->pause();
}

void MainWindow::updateObjects(){
    ui->treeWidget->clear();
    item_to_object_.clear();
    for( unsigned int i = 0 ; i < SceneContainer::howManyObjects() ; i++ ) {
        Joint* object =  SceneContainer::objectAt(i);
        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(QString(object->label().c_str())));
        updateObjectsRecursive(item, object);
        ui->treeWidget->addTopLevelItem(item);
        item_to_object_[item] = object;
        object_to_item_[object]  = item;
    }
    ui->treeWidget->expandAll();

    connect(ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(updateCurrentSelected(QTreeWidgetItem*,QTreeWidgetItem*)));
    //ui->timebar->setKeyFrames((Object3D*)SceneContainer::ObjectAt(0));
    ui->timebar->update();
}

void MainWindow::updateObjectsRecursive(QTreeWidgetItem *item, Joint* parent){
    for(int i = 0 ; i < parent->howManyChilds() ; i++ ) {
        Joint *child = parent->childAt(i);
        QTreeWidgetItem *childitem = new QTreeWidgetItem(item,QStringList(QString(child->label().c_str())));
        updateObjectsRecursive(childitem, child);
        item_to_object_[childitem] = child;
        object_to_item_[child]  = childitem;
    }
    //    if(parent->ChildObject()!=NULL){
    //       new QTreeWidgetItem(item,QStringList(QString(parent->ChildObject()->label().c_str())));
    //    }
}

void MainWindow::updateCurrentSelected(QTreeWidgetItem *item, QTreeWidgetItem* other) {
    selected_item_ = item;
    if(item == NULL) return;
    if( item_to_object_.find(item) != item_to_object_.end() ) {
        Object3D* object = item_to_object_[item];
        updateSelectedInfo(object);
        ui->timebar->setKeyFrames(object);
    }
}

void MainWindow::updateFrameCount(int new_total) {
    SceneContainer::setFrameRange(0,new_total);
    ui->timebar->setNumberOfFrames(new_total+1);
    ui->timebar->repaint();
}

void MainWindow::updateFPS(int new_fps) {
}

void MainWindow::updateSpeedControl(int new_speed_control) {
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

void MainWindow::updatePositionInterpolation(int new_speed_interpolation) {
    switch(new_speed_interpolation) {
    case 0:
        SceneContainer::setPositionInterpolationType(PosInterpolator::kLinear);
        break;
    default:
        SceneContainer::setPositionInterpolationType(PosInterpolator::kCatmullRoom);
        break;
    }
}

void MainWindow::updateOrientationInterpolation(int new_orientation_interpolation) {
    switch(new_orientation_interpolation) {
    case 0:
        SceneContainer::setOrientationInterpolationType(OriInterpolator::kSlerp);
        break;
    default:
        SceneContainer::setOrientationInterpolationType(OriInterpolator::kBezier);
        break;
    }
}

void MainWindow::updateFreeze() {
    SceneContainer::setAnimated(!ui->checkbox_freeze_pos->isChecked(),!ui->checkbox_freeze_ori->isChecked());
}

void MainWindow::updateSelectedInfo(Object3D* object) {
    if(SceneContainer::selectedObject()!=NULL){
        SceneContainer::selectedObject()->setDrawBoundingBox(false);
        SceneContainer::selectedObject()->setDrawOrientationAxes(false);
    }
    SceneContainer::setSelectedObject(object);

    if(object==NULL) {
        ui->tab_object->setEnabled(false);
        return;
    }
    ui->tab_object->setEnabled(false);
    SceneContainer::selectedObject()->setDrawBoundingBox(true);
    SceneContainer::selectedObject()->setDrawOrientationAxes(true);

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

    ui->spin_ori_x->setValue((angle_rx*180.0)/(M_PI));
    ui->spin_ori_y->setValue((angle_ry*180.0)/(M_PI));
    ui->spin_ori_z->setValue((angle_rz*180.0)/(M_PI));

    connect( ui->spin_pos_x, SIGNAL(valueChanged(double)), this, SLOT(updateCurrentPosition()));
    connect( ui->spin_pos_y, SIGNAL(valueChanged(double)), this, SLOT(updateCurrentPosition()));
    connect( ui->spin_pos_z, SIGNAL(valueChanged(double)), this, SLOT(updateCurrentPosition()));

    connect( ui->spin_ori_x, SIGNAL(valueChanged(double)), this, SLOT(updateCurrentOrientation()));
    connect( ui->spin_ori_y, SIGNAL(valueChanged(double)), this, SLOT(updateCurrentOrientation()));
    connect( ui->spin_ori_z, SIGNAL(valueChanged(double)), this, SLOT(updateCurrentOrientation()));

    ui->tab_object->setEnabled(true);
    ui->viewer->updateGL();
}

void MainWindow::updateSelectedLabel(QString label){
    if(selected_item_ !=NULL) {
        selected_item_->setText(0,label);
    }
    if(SceneContainer::selectedObject()!=NULL)
        SceneContainer::selectedObject()->setLabel(label.toStdString().c_str());

}

void MainWindow::updateCurrentPosition() {
    qglviewer::Vec current_p(ui->spin_pos_x->value(),ui->spin_pos_y->value(),ui->spin_pos_z->value());
    SceneContainer::setSelectedPosition(current_p);
    ui->viewer->updateGL();
}

void MainWindow::updateCurrentOrientation() {
    qglviewer::Quaternion a,b,c,d;
    a.setAxisAngle(qglviewer::Vec(1,0,0),(ui->spin_ori_x->value()*(M_PI/180.0)));
    b.setAxisAngle(qglviewer::Vec(0,1,0),(ui->spin_ori_y->value()*(M_PI/180.0)));
    c.setAxisAngle(qglviewer::Vec(0,0,1),(ui->spin_ori_z->value()*(M_PI/180.0)));
    d = a*b*c;
    d.normalize();
    SceneContainer::setSelectedOrientation(d);
    ui->viewer->updateGL();
}

void MainWindow::displayTrajectoryPosition(bool display) {
    SceneContainer::displaySelectedPositionTrajectory(display);
    ui->viewer->updateGL();
}

void MainWindow::displayTrajectoryOrientation(bool display) {
    SceneContainer::displaySelectedOrientationTrajectory(display);
    ui->viewer->updateGL();
}

void  MainWindow::addPositionKeyframe() {
    SceneContainer::addCurrentPositionKeyframe();
    ui->timebar->setKeyFrames(SceneContainer::selectedObject());
}

void  MainWindow::addOrientationKeyframe() {
    SceneContainer::addCurrentOrientationKeyframe();
    ui->timebar->setKeyFrames(SceneContainer::selectedObject());
}

void  MainWindow::removePositionKeyframe() {
    SceneContainer::removeCurrentPositionKeyframe();
    ui->timebar->setKeyFrames(SceneContainer::selectedObject());
}

void  MainWindow::removeOrientationKeyframe() {
    SceneContainer::removeCurrentOrientationKeyframe();
    ui->timebar->setKeyFrames(SceneContainer::selectedObject());
}

void MainWindow::updateRenderBox(bool box)
{
    SceneContainer::setRenderBox(box);
    ui->viewer->repaint();
}

void MainWindow::updateRenderBones(bool bones)
{
    SceneContainer::setDrawBones(bones);
    ui->viewer->repaint();
}

void MainWindow::updateCurrentScene(int scene){
    SceneContainer::updateCurrentScene(scene);
    updateObjects();
    updateSelectedInfo(NULL);
    ui->timebar->setKeyFrames(NULL);

    SceneContainer::setFrameRange(0,100);
    SceneContainer::setCurrentFrame(0);
    ui->viewer->repaint();
}


void MainWindow::setSelectedByID(int id)
{
    Object3D *obj;
    if(id >= 0){
        obj = Object3D::getObjectByID(id);
        selected_item_ = object_to_item_[obj];
    }else{
        obj = NULL;
        selected_item_ = NULL;
        updateSelectedInfo(NULL);
        ui->timebar->setKeyFrames(NULL);
    }
//    updateSelectedInfo(obj);

    ui->treeWidget->setCurrentItem(selected_item_);
}

