#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    animation = new Animation(this);
    ui->glFrame->animation = animation;

    connect(ui->play,SIGNAL(clicked()),animation,SLOT(play()));
    connect(ui->stop,SIGNAL(clicked()),animation,SLOT(stop()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateFrame()
{
    ui->horizontalSlider->setMaximum(animation->frame.size());
    ui->horizontalSlider->setValue(animation->currentFrame);
    ui->glFrame->update();
}
