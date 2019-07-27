#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QThread>
#include <QTest>

using namespace std;

int readInt(QLineEdit *entry, bool *isOK = nullptr)
{
    return entry->text().toInt(isOK);
}

double readDouble(QLineEdit *entry, bool *isOK = nullptr)
{
    return entry->text().toDouble(isOK);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),

    mouseMoveMessage(""),
    repaintMessage("")
{
    ui->setupUi(this);

    this->setMouseTracking(true);
    this->centralWidget()->setMouseTracking(true);
    ui->canvas->setMouseTracking(true);

    ui->bgColorBtn->setColor(ui->canvas->backGroundColor());
    ui->cutColorBtn->setColor(ui->canvas->cutColor());
    ui->cutterColorBtn->setColor(ui->canvas->cutterColor());
    ui->cuttingColorBtn->setColor(ui->canvas->foreGroundColor());

    this->connectAll();

    ui->cutterFlagButton->click();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateStatusMessage()
{
    QString message = "";

    if (repaintMessage.simplified() != "")
    {
        message += repaintMessage + " ";
    }

    if (mouseMoveMessage.simplified() != "")
    {
        message += mouseMoveMessage + " ";
    }

    ui->statusBar->showMessage(message);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QMainWindow::mouseMoveEvent(event);

    QString newStatusMessage = "";

    int x = int(round(event->localPos().x()));
    int y = int(round(event->localPos().y()));

    x -= ui->canvas->pos().x();
    y -= ui->canvas->pos().y();

    if (x >= 0 && y >= 0 && x < ui->canvas->width() && y < ui->canvas->height())
    {
        newStatusMessage = "Позиция курсора: " + QString::number(x) + ", " + QString::number(y);
    }

    mouseMoveMessage = newStatusMessage;
    updateStatusMessage();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);

    int width, height;

    width = ui->canvas->width();
    height = ui->canvas->height();

    QString newStatusMessage = "Размеры холста: " +
                               QString::number(width) +
                               "x" +
                               QString::number(height);

    if (ui->statusBar->currentMessage() != newStatusMessage)
    {
        repaintMessage = newStatusMessage;
        updateStatusMessage();
    }
}

void MainWindow::connectAll()
{
    connect(ui->bgColorBtn, SIGNAL(clicked()), this, SLOT(setBGColor()));
    connect(ui->cutColorBtn, SIGNAL(clicked()), this, SLOT(setCutColor()));
    connect(ui->cutterColorBtn, SIGNAL(clicked()), this, SLOT(setCutterColor()));
    connect(ui->cuttingColorBtn, SIGNAL(clicked()), this, SLOT(setCuttingColor()));

    connect(ui->cutterFlagButton, SIGNAL(clicked()), this, SLOT(setCutterEntering()));
    connect(ui->lineFlagBtn, SIGNAL(clicked()), this, SLOT(setLineEntering()));

    connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(addPoint()));

    connect(ui->clearBtn, SIGNAL(clicked()), this, SLOT(clear()));
}

void MainWindow::setBGColor()
{
    ColorButton *btn = qobject_cast<ColorButton *>(sender());

    QColorDialog colorDialog(this);

    colorDialog.setCurrentColor(btn->getColor());

    if (colorDialog.exec() == QColorDialog::Accepted)
    {
        btn->setColor(colorDialog.currentColor());

        ui->canvas->setBackGroundColor(btn->getColor());
    }
}

void MainWindow::setCutColor()
{
    ColorButton *btn = qobject_cast<ColorButton *>(sender());

    QColorDialog colorDialog(this);

    colorDialog.setCurrentColor(btn->getColor());

    if (colorDialog.exec() == QColorDialog::Accepted)
    {
        btn->setColor(colorDialog.currentColor());

        ui->canvas->setCutColor(btn->getColor());
    }
}

void MainWindow::setCutterColor()
{
    ColorButton *btn = qobject_cast<ColorButton *>(sender());

    QColorDialog colorDialog(this);

    colorDialog.setCurrentColor(btn->getColor());

    if (colorDialog.exec() == QColorDialog::Accepted)
    {
        btn->setColor(colorDialog.currentColor());

        ui->canvas->setCutterColor(btn->getColor());
    }
}

void MainWindow::setCuttingColor()
{
    ColorButton *btn = qobject_cast<ColorButton *>(sender());

    QColorDialog colorDialog(this);

    colorDialog.setCurrentColor(btn->getColor());

    if (colorDialog.exec() == QColorDialog::Accepted)
    {
        btn->setColor(colorDialog.currentColor());

        ui->canvas->setForeGroundColor(btn->getColor());
    }
}

void MainWindow::clear()
{
    ui->canvas->clear();
}

void MainWindow::addPoint()
{
    bool isOK;
    QString errorTitle = "Ошибка";

    isOK = entryCheckIntProcess(ui->xEntry, errorTitle,
                                 "Координата x точки не задана",
                                 "Координата x точки не является "
                                 "целым числом");
    if (!isOK)
    {
        return;
    }

    isOK = entryCheckIntProcess(ui->yEntry, errorTitle,
                                 "Координата y точки не задана",
                                 "Координата y точки не является "
                                 "целым числом");
    if (!isOK)
    {
        return;
    }

    ui->canvas->touchPoint(ui->xEntry->text().toInt(), ui->yEntry->text().toInt());
}

bool MainWindow::entryCheckIntProcess(QLineEdit *entry, QString errorTitle,
                                      QString errorTextEmpty, QString errorTextNReal)
{
    bool isOK;
    QString temp;

    temp = entry->text().simplified();
    if (temp == "")
    {
        QMessageBox::critical(this, errorTitle, errorTextEmpty);
        return false;
    }

    (void) readInt(entry, &isOK);
    if (isOK == false)
    {
        QMessageBox::critical(this, errorTitle, errorTextNReal);
        return false;
    }

    return true;
}

bool MainWindow::entryCheckRealProcess(QLineEdit *entry, QString errorTitle,
                                       QString errorTextEmpty, QString errorTextNReal)
{
    bool isOK;
    QString temp;

    temp = entry->text().simplified();
    if (temp == "")
    {
        QMessageBox::critical(this, errorTitle, errorTextEmpty);
        return false;
    }

    (void) readDouble(entry, &isOK);
    if (isOK == false)
    {
        QMessageBox::critical(this, errorTitle, errorTextNReal);
        return false;
    }

    return true;
}

void MainWindow::setCutterEntering()
{
    ui->canvas->setType(Canvas::InputType::Cutter);
}

void MainWindow::setLineEntering()
{
    ui->canvas->setType(Canvas::InputType::Line);
}
