#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scenecontainer.h"

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateAnimators() {
    SceneContainer::SetAnimated(ui->checkBox->isChecked(),ui->checkBox_2->isChecked());
}
