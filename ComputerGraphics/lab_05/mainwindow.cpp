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
    connect(ui->paintColorBtn, SIGNAL(clicked()), this, SLOT(setPaintColor()));
    connect(ui->borderColorBtn, SIGNAL(clicked()), this, SLOT(setBorderColor()));

    connect(ui->pointAddBtn, SIGNAL(clicked()), this, SLOT(addPoint()));
    connect(ui->lineCloseBtn, SIGNAL(clicked()), this, SLOT(closeLine()));

    connect(ui->paintBtn, SIGNAL(clicked()), this, SLOT(doPaint()));
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

//    qDebug() << ui->canvas->getPixelColor(200, 200).name();
}

void MainWindow::setPaintColor()
{
    ColorButton *btn = qobject_cast<ColorButton *>(sender());

    QColorDialog colorDialog(this);

    colorDialog.setCurrentColor(btn->getColor());

    if (colorDialog.exec() == QColorDialog::Accepted)
    {
        btn->setColor(colorDialog.currentColor());

//        ui->canvas->setPaintColor(btn->getColor());
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

void MainWindow::addPoint()
{
    bool isOK;
    QString errorTitle = "Ошибка";

    isOK = entryCheckRealProcess(ui->xEntry, errorTitle,
                                 "Координата x точки не задана",
                                 "Координата x точки не является "
                                 "вещественным числом");
    if (!isOK)
    {
        return;
    }

    isOK = entryCheckRealProcess(ui->yEntry, errorTitle,
                                 "Координата y точки не задана",
                                 "Координата y точки не является "
                                 "вещественным числом");
    if (!isOK)
    {
        return;
    }

    ui->canvas->addPoint(ui->xEntry->text().toDouble(), ui->yEntry->text().toDouble());
}

void MainWindow::closeLine()
{
    ui->canvas->closeReading();
}

void MainWindow::clear()
{
    ui->canvas->clear();
}

void MainWindow::doPaint()
{
    ui->canvas->setPaintColor(ui->paintColorBtn->getColor());

    for (auto figure: ui->canvas->getFigures())
    {
        this->paintFigure(figure);
    }

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

//*
void MainWindow::paintFigure(PaintFigure figure)
{
    int xMax = ui->canvas->width();
    auto points = figure.points;

    for (int i = 0; i < points.count(); i++)
    {
        int curVal = int(round(points[i].first));

        if (curVal > xMax)
        {
            xMax = curVal;
        }
    }

    for (int i = 0, j = points.count() - 1, len = points.count();
         i < len; j = i, i++)
    {
        QPoint p1 = { int(round( points[i].first )), int( points[i].second ) };
        QPoint p2 = { int(round( points[j].first )), int( points[j].second ) };

        if (p1.y() < p2.y())
        {
            std::swap(p1, p2);
        }

        if (p1 == p2)
        {
            continue;
        }

        bool swap_flag = false;

        int dx = p2.x() - p1.x();
        int dy = p2.y() - p1.y();

        int sx = (dx > 0) ? 1 : -1;
        int sy = (dy > 0) ? 1 : -1;

        dx = abs(dx);
        dy = abs(dy);

        if (dx < dy)
        {
             std::swap(dx, dy);
             swap_flag = true;
        }

        int m = dy;
        int error = m;

        int x = p1.x();
        int y = p1.y();
        int prev_y = y;

        for (int i = 0, _end = int(round(dx)) + 1; i <  _end; i++)
        {
            for (int _x = x; y != prev_y && _x < xMax; _x++)
            {
                if (!ui->canvas->isBGPixel(QPoint(_x, y)))
                {
                    ui->canvas->remPixel(QPoint(_x, y));
                }
                else
                {
                    ui->canvas->addPixel(QPoint(_x, y));
                }
            }

            prev_y = y;

            if (2 * error > dx)
            {
                if (!swap_flag)
                {
                    y += sy;
                }
                else
                {
                    x += sx;
                }

                error -= dx;
            }

            if (!swap_flag)
            {
                x += sx;
            }
            else
            {
                y += sy;
            }

            error = error + m;

            if (ui->delayCheckBox->isChecked())
            {
                if (prev_y != y)
                {
                    ui->canvas->update();
                    QTest::qWait(1);
                }
            }
        }
    }
}
//*/
