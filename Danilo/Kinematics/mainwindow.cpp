#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math/vec4.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPositionGoal()
{
    Vec4 goal;
    goal.setVec4(ui->dPosX->value(),ui->dPosY->value(),ui->dPosZ->value());
    ui->widget->setGoal(goal);

}
