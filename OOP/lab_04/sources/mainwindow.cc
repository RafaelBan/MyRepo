#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTreeWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

/*    for (int i = 0; i < 30; i++)*/
        /*ui->treeWidget->addTopLevelItem(new QTreeWidgetItem);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

