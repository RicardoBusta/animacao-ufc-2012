#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Utils/scenecontainer.h"

#include <QButtonGroup>

QButtonGroup*group1 = new QButtonGroup;
QButtonGroup*group2 = new QButtonGroup;
QButtonGroup*group3 = new QButtonGroup;
QButtonGroup*group4 = new QButtonGroup;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("Animating"));
    connect( ui->button_play, SIGNAL(clicked()), ui->viewer, SLOT(Play()) );
    connect( ui->button_stop, SIGNAL(clicked()), ui->viewer, SLOT(Stop()));
    connect( ui->button_pause, SIGNAL(clicked()) , ui->viewer, SLOT(Pause()));
    connect( ui->timebar, SIGNAL(SetSelectedFrame(int)), ui->viewer, SLOT(SetCurrentFrame(int)));
    connect( ui->viewer, SIGNAL(CurrentFrame(int)), ui->timebar, SLOT(SetCurrentFrame(int)));

    connect (ui->checkBox, SIGNAL(toggled(bool)), this, SLOT(UpdateAnimators()));
    connect (ui->checkBox_2, SIGNAL(toggled(bool)), this, SLOT(UpdateAnimators()));

    group1->addButton(ui->rad_pos,0);
    group1->addButton(ui->rad_ori,1);
    group1->addButton(ui->radioButton_4,2);

    group2->addButton(ui->radioButton_2,0);
    group2->addButton(ui->radioButton_5,1);

    group3->addButton(ui->radioButton_6,0);
    group3->addButton(ui->radioButton_7,1);


    group4->addButton(ui->radioButton,0);
    group4->addButton(ui->radioButton_3,1);


    connect (group1, SIGNAL(buttonClicked(int)), this, SLOT(UpdateAnimators()));
    connect (group2, SIGNAL(buttonClicked(int)), this, SLOT(UpdateAnimators()));
    connect (group3, SIGNAL(buttonClicked(int)), this, SLOT(UpdateAnimators()));
    connect (group4, SIGNAL(buttonClicked(int)), this, SLOT(UpdateAnimators()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateAnimators() {
    //SceneContainer::SetAnimated(ui->checkBox->isChecked(),ui->checkBox_2->isChecked());
    SceneContainer::ToErase(ui->checkBox->isChecked(),ui->checkBox_2->isChecked(),group4->checkedId(),
                            group1->checkedId(), group2->checkedId(), group3->checkedId());
    ui->viewer->updateGL();
}
