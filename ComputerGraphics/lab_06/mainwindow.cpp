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

    ui->paintColorBtn->setColor(ui->canvas->paintColor());
    ui->bgColorBtn->setColor(ui->canvas->backGroundColor());
    ui->borderColorBtn->setColor(ui->canvas->foreGroundColor());

    this->connectAll();

    ui->pointsFlagBtn->click();

    this->setMouseTracking(true);
    centralWidget()->setMouseTracking(true);
    ui->canvas->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCanvasPoint()
{
    ui->canvas->setState(Canvas::State::POINT);
}

void MainWindow::setCanvasLine()
{
    ui->canvas->setState(Canvas::State::LINE);
}

void MainWindow::setCanvasSeed()
{
    ui->canvas->setState(Canvas::State::SEED);
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
    ui->canvas->update();
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
    connect(ui->paintColorBtn, SIGNAL(clicked()), this, SLOT(setPaintColor()));
    connect(ui->borderColorBtn, SIGNAL(clicked()), this, SLOT(setBorderColor()));

    connect(ui->pointAddBtn, SIGNAL(clicked()), this, SLOT(addPoint()));
    connect(ui->lineCloseBtn, SIGNAL(clicked()), this, SLOT(closeLine()));

    connect(ui->paintBtn, SIGNAL(clicked()), this, SLOT(doPaint()));
    connect(ui->clearBtn, SIGNAL(clicked()), this, SLOT(clear()));

    connect(ui->pointsFlagBtn, SIGNAL(clicked()), this, SLOT(setCanvasPoint()));
    connect(ui->linesFlagBtn, SIGNAL(clicked()), this, SLOT(setCanvasLine()));
    connect(ui->seedFlagBtn, SIGNAL(clicked()), this, SLOT(setCanvasSeed()));

    connect(ui->delayCheckBox, SIGNAL(clicked()), this, SLOT(setDelay()));
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

void MainWindow::setPaintColor()
{
    ColorButton *btn = qobject_cast<ColorButton *>(sender());

    QColorDialog colorDialog(this);

    colorDialog.setCurrentColor(btn->getColor());

    if (colorDialog.exec() == QColorDialog::Accepted)
    {
        btn->setColor(colorDialog.currentColor());

        ui->canvas->setPaintColor(btn->getColor());
    }
}

void MainWindow::setBorderColor()
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

void MainWindow::closeLine()
{
    ui->canvas->lock();
}

void MainWindow::setDelay()
{
    ui->canvas->setDelay(ui->delayCheckBox->isChecked());
}

void MainWindow::clear()
{
    ui->canvas->clear();
}

void MainWindow::doPaint()
{
    ui->canvas->paint();
    ui->canvas->update();
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
