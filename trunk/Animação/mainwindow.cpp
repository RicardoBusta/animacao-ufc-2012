#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Utils/scenecontainer.h"
#include "Interpolation/genericinterpolator.h"
#include "Objects3D/joint.h"
#include "ikdialog.h"
#include "Objects3D/iktarget.h"

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

    connect( ui->push_ikmode, SIGNAL(toggled(bool)), this, SLOT(setIKMode(bool)) );

    connect( ui->inverse, SIGNAL(currentIndexChanged(int)), this, SLOT(setInverse(int)) );

    connect(ui->tab_widget, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));

    connect(ui->combo_end, SIGNAL(currentIndexChanged(int)), this, SLOT(setIKTarget()) );

    connect(ui->spinx, SIGNAL(valueChanged(double)), this, SLOT(changeGoal()) );
    connect(ui->spiny, SIGNAL(valueChanged(double)), this, SLOT(changeGoal()) );
    connect(ui->spinz, SIGNAL(valueChanged(double)), this, SLOT(changeGoal()) );


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

    /*connect( ui->spinx, SIGNAL(valueChanged(double)), this, SLOT(changeGoal()) );
    connect( ui->spiny, SIGNAL(valueChanged(double)), this, SLOT(changeGoal()) );
    connect( ui->spinz, SIGNAL(valueChanged(double)), this, SLOT(changeGoal()) );*/

    ui->tab_object->setEnabled(true);

    ui->timebar->setKeyFrames(object);
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
    //IKTarget* target = IKTarget::GetIKTargetById(SceneContainer::selectedObject()->id());
    //    if(target!=NULL){
    //        target->Solve();
    //    }
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
    SceneContainer::setCurrentFrame(1);
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


void MainWindow::setIKMode(bool ik)
{
    /*
    IKDialog ik_dialog;

    if(ik_dialog.exec() == QDialog::Accepted){
        IKTarget* new_object = ik_dialog.getTarget();
        QTreeWidgetItem *childitem = new QTreeWidgetItem(ui->treeWidget,QStringList(QString(new_object->label().c_str())));
        item_to_object_[childitem] = new_object;
        object_to_item_[new_object]  = childitem;
        SceneContainer::AddIKTarget(new_object);
    }*/

    if(!play_or_pause_){
        play_or_pause_ = true;
        ui->button_play->setIcon(play_icon);
        ui->viewer->pause();
    }
    if(ik){
        ui->viewer->ikStart();
    }else{
        ui->viewer->ikStop();
    }
    ui->tab_widget->setEnabled(!ik);
    ui->timebar->setEnabled(!ik);
    ui->button_play->setEnabled(!ik);
    ui->button_stop->setEnabled(!ik);
    SceneContainer::setIKMode(ik);
}


void MainWindow::setInverse(int inverse)
{
    SceneContainer::ikTarget.inverse_ = 1;
}


void MainWindow::changeGoal()
{
    SceneContainer::ikTarget.setNewPosition( qglviewer::Vec(ui->spinx->value(), ui->spiny->value(), ui->spinz->value()) );
    ui->viewer->repaint();
}


void MainWindow::tabChanged(int tab)
{
    if(tab == 3){
        if(!play_or_pause_){
            play_or_pause_ = true;
            ui->button_play->setIcon(play_icon);
            ui->viewer->pause();
        }
        ui->timebar->setEnabled(false);
        ui->button_play->setEnabled(false);
        ui->button_stop->setEnabled(false);
        SceneContainer::setIKMode(true);
        ui->viewer->ikStart();

        fillStart();
    }else{
        ui->timebar->setEnabled(true);
        ui->button_play->setEnabled(true);
        ui->button_stop->setEnabled(true);
        SceneContainer::setIKMode(false);
        ui->viewer->ikStop();
    }
}


void MainWindow::fillStart()
{
    disconnect(ui->combo_start, SIGNAL(currentIndexChanged(int)), this, SLOT(fillEnd(int)) );
    ui->combo_start->clear();
    ui->combo_start->addItem(QString("---"));
    index_id_.clear();
    for(int i = 0; i < SceneContainer::howManyObjects() ; i++){
        Joint* obj = dynamic_cast<Joint*>(SceneContainer::objectAt(i));
        if(obj!=NULL)
            fillComboBox(obj,ui->combo_start);
    }
    connect(ui->combo_start, SIGNAL(currentIndexChanged(int)), this, SLOT(fillEnd(int)) );
}


void MainWindow::fillEnd(int index)
{
    ui->combo_end->setEnabled(false);
    ui->label_end->setEnabled(false);
    ui->combo_end->clear();
    ui->combo_end->addItem(QString("---"));

    if(index==-1 or index==0){
        ui->save_orientations->setEnabled(false);
        return;
    }
    ui->save_orientations->setEnabled(true);
    int obj_id = index_id_[index];

    Joint* obj = dynamic_cast<Joint*>(Object3D::getObjectByID(obj_id));

    if(obj!=NULL) {
        if(obj->howManyChilds()>0) {
            for(int i = 0 ; i < obj->howManyChilds() ; i++ )
                fillComboBox(obj->childAt(i),ui->combo_end,true,ui->combo_start->count());
            ui->combo_end->setEnabled(true);
            ui->label_end->setEnabled(true);
        }
    }
}


void MainWindow::fillComboBox(Joint *this_obj, QComboBox *combo, bool compensate, int compensation)
{
    Joint* obj = this_obj;
    if(obj==NULL) return;
    std::string spaces;
    std::string label;

    std::vector<std::pair<std::string,Joint*> > stack;
    std::pair<std::string,Joint*> first_element;
    first_element.first = "";
    first_element.second = obj;
    stack.push_back(first_element);

    while(!stack.empty()) {

        Joint* current = stack.at(stack.size()-1).second;
        spaces =  stack.at(stack.size()-1).first + "  ";
        stack.erase(stack.begin()+(stack.size()-1));

        label = current->label();
        QString object_label = QString(spaces.c_str()) + QString(label.c_str());
        index_id_[compensate? combo->count() + compensation : combo->count()]=current->id();
        combo->addItem(object_label);

        for(int i = 0 ; i < current->howManyChilds(); i++){
            std::pair<std::string,Joint*> new_element;
            new_element.first = spaces;
            new_element.second = current->childAt(i);
            stack.push_back(new_element);
        }
    }
}


void MainWindow::setIKTarget()
{
    SceneContainer::ikTarget.clear();

    if( ui->combo_end->currentIndex() == -1 or ui->combo_end->currentIndex()== 0 ) return;

    std::cout << "derp" << std::endl;

    //IKTarget* target = new IKTarget(qglviewer::Vec());
    //target->setLabel(ui->lineEdit->text().toStdString());
    int obj_id_end = index_id_[ui->combo_end->currentIndex()+ui->combo_start->count()];
    int obj_id_start = index_id_[ui->combo_start->currentIndex()];
    Joint* obj = dynamic_cast<Joint*>(Object3D::getObjectByID(obj_id_end));
    Joint* obj_root = dynamic_cast<Joint*>(Object3D::getObjectByID(obj_id_start));
    //SceneContainer::target.setInverseUsable(ui->checkBox->isChecked());
    std::vector<Joint*> order;
    while((obj!=NULL) && (obj!=obj_root)){
        order.push_back(obj);
        obj = obj->parent();
    }
    if(obj==obj_root)
        order.push_back(obj);
    for(int i = order.size()-1; i >= 0 ; i--){
        SceneContainer::ikTarget.addChildBone(order.at(i));
    }
    ui->viewer->repaint();

    //return target;
}
