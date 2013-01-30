#include "ikdialog.h"
#include "ui_ikdialog.h"
#include "Objects3D/object3d.h"
#include "Objects3D/joint.h"
#include "Objects3D/iktarget.h"
#include "Utils/scenecontainer.h"

IKDialog::IKDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IKDialog)
{
    ui->setupUi(this);

    this->setWindowTitle(QString("IK Parameters"));

    QObject::connect(ui->button_ok, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(ui->button_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    FillBase();
}

IKDialog::~IKDialog()
{
    delete ui;
}

void IKDialog::FillBase() {
    QObject::disconnect(ui->combo_base,SIGNAL(currentIndexChanged(int)), this, SLOT(FillParent(int)));
    ui->combo_base->clear();
    ui->combo_base->addItem(QString("---"));
    index_id_.clear();
    for(int i = 0; i < SceneContainer::howManyObjects() ; i++){
        Joint* obj = dynamic_cast<Joint*>(SceneContainer::objectAt(i));
        if(obj!=NULL)
            FillComboBox(obj,ui->combo_base);
    }
    QObject::connect(ui->combo_base,SIGNAL(currentIndexChanged(int)), this, SLOT(FillParent(int)));
}

void IKDialog::FillComboBox(Joint* this_obj, QComboBox* combo, bool compensate, int compensation) {
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

        for(unsigned int i = 0 ; i < current->howManyChilds(); i++){
            std::pair<std::string,Joint*> new_element;
            new_element.first = spaces;
            new_element.second = current->childAt(i);
            stack.push_back(new_element);
        }
    }

}

void IKDialog::FillParent(int index){
    ui->combo_extreme->setEnabled(false);
    ui->label_extreme->setEnabled(false);
    ui->combo_extreme->clear();

    if(index==-1 or index==0){
        ui->button_ok->setEnabled(false);
        return;
    }
    ui->button_ok->setEnabled(true);
    int obj_id = index_id_[index];

    Joint* obj = dynamic_cast<Joint*>(Object3D::getObjectByID(obj_id));

    if(obj!=NULL) {
        if(obj->howManyChilds()>0) {
            for(int i = 0 ; i < obj->howManyChilds() ; i++ )
                FillComboBox(obj->childAt(i),ui->combo_extreme,true,ui->combo_base->count());
            ui->combo_extreme->setEnabled(true);
            ui->label_extreme->setEnabled(true);
        }
    }
}

IKTarget* IKDialog::getTarget() {
    IKTarget* target = new IKTarget(qglviewer::Vec());
    target->setLabel(ui->lineEdit->text().toStdString());
    int obj_id_extreme = index_id_[ui->combo_extreme->currentIndex()+ui->combo_base->count()];
    int obj_id_base = index_id_[ui->combo_base->currentIndex()];
    Joint* obj = dynamic_cast<Joint*>(Object3D::getObjectByID(obj_id_extreme));
    Joint* t_p = dynamic_cast<Joint*>(Object3D::getObjectByID(obj_id_base));
    target->setInverseUsable(ui->checkBox->isChecked());
    std::vector<Joint*> order;
    while((obj!=NULL) && (obj!=t_p)){
        order.push_back(obj);
        obj = obj->parent();
    }
    if(obj==t_p)
        order.push_back(obj);
    for(int i = order.size()-1; i >= 0 ; i--){
        target->AddChildBone(order.at(i));
    }
    return target;
}
