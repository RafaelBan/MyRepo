#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),

    floorsCount (10),
    elevator (new Elevator(floorsCount))
{
    ui->setupUi(this);

    ui->elevatorControl->setUp(floorsCount);

    for (int i = 0; i < ui->elevatorControl->getButtonsCount(); i++)
    {
        connect(ui->elevatorControl->getButton(i), SIGNAL(clicked()), this, SLOT(target()));
    }

    connect(elevator, SIGNAL(reached()), this, SLOT(updateIndicator()));
    connect(elevator, SIGNAL(came()), this, SLOT(updateIndicator()));
    connect(elevator, SIGNAL(stopped()), this, SLOT(updateIndicator()));
    connect(elevator, SIGNAL(started()), this, SLOT(updateIndicator()));

    connect(elevator, SIGNAL(reached()), this, SLOT(updateDisplay()));
    connect(elevator, SIGNAL(came()), this, SLOT(updateDisplay()));
    connect(elevator, SIGNAL(keptMoving()), this, SLOT(updateDisplay()));

    connect(ui->elevatorControl->upBtn, SIGNAL(clicked()), this, SLOT(callup()));
    connect(ui->elevatorControl->downBtn, SIGNAL(clicked()), this, SLOT(calldown()));
}

MainWindow::~MainWindow()
{
    delete ui;

    delete elevator;
}

void MainWindow::target()
{
    auto btn = qobject_cast<GButton *>(sender());

    elevator->target(btn->getNumber());
}

void MainWindow::callup()
{
    int floor = ui->elevatorControl->floorsList->currentText().toInt();

    elevator->callUp(floor);
}

void MainWindow::calldown()
{
    int floor = ui->elevatorControl->floorsList->currentText().toInt();

    elevator->callDown(floor);
}

void MainWindow::updateDisplay()
{
    ui->elevatorControl->floorDisplay->display(elevator->position());
}

void MainWindow::updateIndicator()
{
    ui->elevatorControl->indicator->setDirection(elevator->direction());
}
