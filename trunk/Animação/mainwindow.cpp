#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    animation = new Animation(this);

    ui->setupUi(this);

    ui->glFrame->animation = animation;

    connect(ui->play,SIGNAL(clicked()),animation,SLOT(play()));
    connect(ui->stop,SIGNAL(clicked()),animation,SLOT(stop()));

    ui->glFrame->setAnimationPeriod(20);
    ui->glFrame->startAnimation();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateFrame()
{
    ui->horizontalSlider->setMaximum(animation->sizeFrames);
    ui->horizontalSlider->setValue(animation->currentFrame);
    //ui->glFrame->update();
}
