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

    for( int i = 0 ; i < SceneContainer::HowManyObjects() ; i++ ) {
        Joint* object =  SceneContainer::ObjectAt(i);
        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(QString(object->label().c_str())));
        updateObjectsRecursive(item, object);
        ui->treeWidget->addTopLevelItem(item);
    }
    ui->treeWidget->expandAll();

    ui->timebar->setKeyFrames((Object3D*)SceneContainer::ObjectAt(0));
    ui->timebar->update();    
}

void MainWindow::updateObjectsRecursive(QTreeWidgetItem *item, Joint* parent){
    for(int i = 0 ; i < parent->HowManyChilds() ; i++ ) {
        Joint *child = parent->ChildAt(i);
        QTreeWidgetItem *childitem = new QTreeWidgetItem(item,QStringList(QString(child->label().c_str())));
        updateObjectsRecursive(childitem, child);
    }
    if(parent->ChildObject()!=NULL){
       new QTreeWidgetItem(item,QStringList(QString(parent->ChildObject()->label().c_str())));
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
