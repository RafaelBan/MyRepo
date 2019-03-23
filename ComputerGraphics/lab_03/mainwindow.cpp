#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <cmath>

using namespace ColorProcess;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineColorButton->setStyleSheet(ColorButtonStyle(ui->drawingWidget->getLineColor().name()));
    ui->bgColorButton->setStyleSheet(ColorButtonStyle(ui->drawingWidget->getBGColor().name()));

    ui->algoesListEntry->addItems(algoes);

    cartesian::straight::doFullSmooth = ui->smoothCheckBox->isChecked();

    connect(ui->bgColorButton, SIGNAL(clicked(bool)), this, SLOT(colorButtonsAction()));
    connect(ui->lineColorButton, SIGNAL(clicked(bool)), this, SLOT(colorButtonsAction()));
    connect(ui->unitedColorButton, SIGNAL(clicked(bool)), this, SLOT(unitedColorButtonAction()));

    connect(ui->strtDrawButton, SIGNAL(clicked(bool)), this, SLOT(drawSLine()));
    connect(ui->clusterDrawButton, SIGNAL(clicked(bool)), this, SLOT(drawCluster()));
    connect(ui->clearButton, SIGNAL(clicked(bool)), this, SLOT(clearDisplay()));

    connect(ui->smoothCheckBox, SIGNAL(stateChanged(int)), this, SLOT(smoothCBAction()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);

    int xMin, xMax;
    int yMin, yMax;
    int width, height;

    width = ui->drawingWidget->width();
    height = ui->drawingWidget->height();

    xMin = -(width / 2);
    xMax = +(xMin + width);
    yMin = -(height / 2);
    yMax = +(yMin + height);

    ui->statusBar->showMessage(QString::number(xMin) + "..." + QString::number(xMax) +
                               ", " +
                               QString::number(yMin) + "..." + QString::number(yMax));
}

void MainWindow::colorButtonsAction()
{
    QColor color;
    QPushButton *requester = static_cast<QPushButton *>(sender());
    QColorDialog *colorDialog = new QColorDialog(this);

    if (requester == ui->bgColorButton)
    {
        colorDialog->setCurrentColor(ui->drawingWidget->getBGColor());
    }
    if (requester == ui->lineColorButton)
    {
        colorDialog->setCurrentColor(ui->drawingWidget->getLineColor());
    }

    if (colorDialog->exec() == QColorDialog::Accepted)
    {
        color = colorDialog->currentColor();
        requester->setStyleSheet(ColorButtonStyle(color.name()));

        if (requester == ui->lineColorButton)
        {
            ui->drawingWidget->setLineColor(color);
            ui->drawingWidget->repaint();
        }
        if (requester == ui->bgColorButton)
        {
            ui->drawingWidget->setBGColor(color);
            ui->drawingWidget->repaint();
        }
    }

    delete colorDialog;
}

void MainWindow::unitedColorButtonAction()
{
    QColor color;
    QColorDialog *colorDialog = new QColorDialog(this);

    colorDialog->setCurrentColor(ui->drawingWidget->getBGColor());

    if (colorDialog->exec() == QColorDialog::Accepted)
    {
        color = colorDialog->currentColor();

        ui->bgColorButton->setStyleSheet(ColorButtonStyle(color.name()));
        ui->lineColorButton->setStyleSheet(ColorButtonStyle(color.name()));

        ui->drawingWidget->setLineColor(color);
        ui->drawingWidget->setBGColor(color);
        ui->drawingWidget->repaint();
    }

    delete colorDialog;
}

double MainWindow::readDouble(QLineEdit *entry, bool *isOK)
{
    return entry->text().toDouble(isOK);
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

    (void)MainWindow::readDouble(entry, &isOK);
    if (isOK == false)
    {
        QMessageBox::critical(this, errorTitle, errorTextNReal);
        return false;
    }

    return true;
}

void MainWindow::drawSLine()
{
    bool isOK;
    QString errorTitle = "Ошибка";

    isOK =  this->entryCheckRealProcess(ui->x1Entry,
                                        errorTitle,
                                        "Значение x1 не задано",
                                        "Заданное значение x1 "
                                        "не является действительным числом");
    if (isOK == false)
    {
        return;
    }

    isOK =  this->entryCheckRealProcess(ui->y1Entry,
                                        errorTitle,
                                        "Значение y1 не задано",
                                        "Заданное значение y1 "
                                        "не является действительным числом");
    if (isOK == false)
    {
        return;
    }

    isOK =  this->entryCheckRealProcess(ui->x2Entry,
                                        errorTitle,
                                        "Значение x2 не задано",
                                        "Заданное значение x2 "
                                        "не является действительным числом");
    if (isOK == false)
    {
        return;
    }

    isOK =  this->entryCheckRealProcess(ui->y2Entry,
                                        errorTitle,
                                        "Значение y2 не задано",
                                        "Заданное значение y2 "
                                        "не является действительным числом");
    if (isOK == false)
    {
        return;
    }

    QString algoName = getAlgoName(ui->algoesListEntry->currentText());

    int x1, y1;
    int x2, y2;

    x1 =  int(round(ui->x1Entry->text().toDouble()));
    y1 =  int(round(ui->y1Entry->text().toDouble()));
    x2 =  int(round(ui->x2Entry->text().toDouble()));
    y2 =  int(round(ui->y2Entry->text().toDouble()));

    cartesian::straight::drawTask newTask(x1, y1, x2, y2, ui->drawingWidget->getLineColor(), algoName);

    ui->drawingWidget->addTask(newTask);

    ui->drawingWidget->repaint();
}

void MainWindow::drawCluster()
{
    bool isOK;
    QString errorTitle = "Ошибка";

    isOK =  this->entryCheckRealProcess(ui->strtLenEntry,
                                        errorTitle,
                                        "Значение радиуса пучка не задано",
                                        "Заданное значение радиуса пучка "
                                        "не является действительным числом");
    if (isOK == false)
    {
        return;
    }

    isOK =  this->entryCheckRealProcess(ui->angleStepEntry,
                                        errorTitle,
                                        "Значение шага угла не задано",
                                        "Заданное значение шага угла "
                                        "не является действительным числом");
    if (isOK == false)
    {
        return;
    }

    QString algoName = getAlgoName(ui->algoesListEntry->currentText());

    double angleStep = ui->angleStepEntry->text().toDouble();
    double radius = ui->strtLenEntry->text().toDouble();

    if (isEqual(angleStep, 0))
    {
        QMessageBox::critical(this, errorTitle, "Значение шага угла слишком близко к нулю");
        return;
    }

    double angle = 0;

    while (abs(angle) < 360)
    {
        ui->drawingWidget->addTask(
                    cartesian::straight::drawTask(0, 0,
                                                  int(round(radius * cos(degToRad(angle)))),
                                                  int(round(radius * sin(degToRad(angle)))),
                                                  ui->drawingWidget->getLineColor(),
                                                  algoName
                    ));
        angle += angleStep;
    }

    ui->drawingWidget->repaint();
}

void MainWindow::clearDisplay()
{
    ui->drawingWidget->clearTasks();
    ui->drawingWidget->repaint();
}

void MainWindow::smoothCBAction()
{
    cartesian::straight::doFullSmooth = ui->smoothCheckBox->isChecked();
}

QString getAlgoName(QString itemText)
{
    if (itemText == algoes[0])
    {
        return "DDA";
    }
    if (itemText == algoes[1])
    {
        return "bresenhamr";
    }
    if (itemText == algoes[2])
    {
        return "bresenhami";
    }
    if (itemText == algoes[3])
    {
        return "bresenhama";
    }
    if (itemText == algoes[4])
    {
        return "WU";
    }
    if (itemText == algoes[5])
    {
        return "standard";
    }

    return "standard";
}
