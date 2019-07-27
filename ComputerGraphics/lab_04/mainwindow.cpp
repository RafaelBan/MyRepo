#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    handlerTimer(new QTimer)
{
    ui->setupUi(this);

    for (size_t i = 0, len = sizeof(drawAlgo::names) / sizeof (char *); i < len; i++)
    {
        ui->algoList->addItem(drawAlgo::names[i]);
    }
    ui->algoList->setCurrentIndex(ui->algoList->count() - 1);

    ui->bgColorButton->setColor(ui->canvas->backGroundColor());
    ui->fgColorButton->setColor(ui->canvas->foreGroundColor());

    ui->centerXEntry->setText(QString::number(ui->canvas->width() / 2));
    ui->centerYEntry->setText(QString::number(ui->canvas->height() / 2));

    this->connectings();

    this->handlerTimer->start(0);
}

void MainWindow::connectings()
{
    connect(ui->bgColorButton, SIGNAL(clicked()), this, SLOT(bgColorSet()));
    connect(ui->fgColorButton, SIGNAL(clicked()), this, SLOT(fgColorSet()));
    connect(ui->toBGColorButton, SIGNAL(clicked()), this, SLOT(fgToBgColorSet()));

    connect(ui->centerSetButton, SIGNAL(clicked()), this, SLOT(centerSet()));

    connect(this->handlerTimer, SIGNAL(timeout()), this, SLOT(handlerTimerAction()));

    connect(ui->drawButton, SIGNAL(clicked()), this, SLOT(drawAction()));
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearAction()));
}

MainWindow::~MainWindow()
{
    delete this->handlerTimer;

    delete ui;
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

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);

    int width, height;

    width = ui->canvas->width();
    height = ui->canvas->height();

    ui->statusBar->showMessage("Размеры холста: " +
                               QString::number(width) +
                               "x" +
                               QString::number(height));
}

void MainWindow::bgColorSet()
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

void MainWindow::fgColorSet()
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

void MainWindow::fgToBgColorSet()
{
    ui->fgColorButton->setColor(ui->bgColorButton->getColor());
    ui->canvas->setForeGroundColor(ui->bgColorButton->getColor());
}

void MainWindow::centerSet()
{
    ui->centerXEntry->setText(QString::number(ui->canvas->width() / 2));
    ui->centerYEntry->setText(QString::number(ui->canvas->height() / 2));
}

void MainWindow::readCenter(bool *isOK)
{
    QString errorTitle = "Ошибка";

    *isOK = entryCheckRealProcess(ui->centerXEntry, errorTitle,
                                  "Координата центра фигуры x не задана",
                                  "Координата центра фигуры x не является "
                                  "вещественным числом");

    if (*isOK != true)
    {
        return;
    }

    *isOK = entryCheckRealProcess(ui->centerYEntry, errorTitle,
                                  "Координата центра фигуры y не задана",
                                  "Координата центра фигуры y не является "
                                  "вещественным числом");

    if (*isOK != true)
    {
        return;
    }

    control::Handler::setCenter(readDouble(ui->centerXEntry),
                                readDouble(ui->centerYEntry));
}

void MainWindow::readCircleBase(bool *isOK)
{
    QString errorTitle = "Ошибка";

    *isOK = entryCheckRealProcess(ui->radiuscEntry, errorTitle,
                                  "Радиус окружности R не задан",
                                  "Радиус окружности R не является "
                                  "вещественным числом");

    if (*isOK != true)
    {
        return;
    }

    if (readDouble(ui->radiuscEntry) < 0)
    {
        QMessageBox::critical(this,
                              errorTitle,
                              "Радиус окружности R не может быть меньше нуля");

        *isOK = false;
        return;
    }

    control::Handler::setCircleBase(readDouble(ui->radiuscEntry));
}

void MainWindow::readCircleConc(bool *isOK)
{
    QString errorTitle = "Ошибка";

    *isOK = entryCheckRealProcess(ui->radiuscEntry, errorTitle,
                                  "Начальный радиус концентрических окружностей R не задан",
                                  "Начальный радиус концентрических окружностей R не является "
                                  "вещественным числом");

    if (*isOK != true)
    {
        return;
    }

    if (readDouble(ui->radiuscEntry) <= 0)
    {
        QMessageBox::critical(this,
                              errorTitle,
                              "Начальный радиус окружности R не может быть меньше или равно нуля");

        *isOK = false;
        return;
    }

    *isOK = entryCheckRealProcess(ui->rfEntry, errorTitle,
                                  "Конечный радиус концентрических окружностей Rf не задан",
                                  "Конечный радиус концентрических окружностей Rf не является "
                                  "вещественным числом");

    if (*isOK != true)
    {
        return;
    }

    if (readDouble(ui->rfEntry) <= 0)
    {
        QMessageBox::critical(this,
                              errorTitle,
                              "Конечный радиус окружности Rf не может быть меньше или равно нуля");

        *isOK = false;
        return;
    }

    if (readDouble(ui->rfEntry) < readDouble(ui->radiuscEntry))
    {
        QMessageBox::critical(this,
                              errorTitle,
                              "Значение Rf не может быть меньше R.");

        *isOK = false;
        return;
    }

    *isOK = entryCheckIntProcess(ui->ncEntry, errorTitle,
                                 "Кол-во концентрических окружностей N не задано",
                                 "Кол-во концентрических окружностей N не является "
                                 "целым числом");

    if (*isOK != true)
    {
        return;
    }

    if (readInt(ui->ncEntry) < 2)
    {
        QMessageBox::critical(this,
                              errorTitle,
                              "Кол-во концентрических окружностей "
                              "N не может быть меньше 2");

        *isOK = false;
        return;
    }

    control::Handler::setCircleConc(readDouble(ui->radiuscEntry),
                                    readDouble(ui->rfEntry),
                                    readInt(ui->ncEntry));
}

void MainWindow::readEllipseBase(bool *isOK)
{
    QString errorTitle = "Ошибка";

    *isOK = entryCheckRealProcess(ui->aEllEntry, errorTitle,
                                  "Полуось эллипса a не задана",
                                  "Полуось эллипса a не является "
                                  "вещественным числом");

    if (*isOK != true)
    {
        return;
    }

    if (readDouble(ui->aEllEntry) <= 0)
    {
        QMessageBox::critical(this,
                              errorTitle,
                              "Полуось эллипса a не может быть меньше или равно нуля");

        *isOK = false;
        return;
    }

    *isOK = entryCheckRealProcess(ui->bEllEntry, errorTitle,
                                  "Полуось эллипса b не задана",
                                  "Полуось эллипса b не является "
                                  "вещественным числом");

    if (*isOK != true)
    {
        return;
    }

    if (readDouble(ui->bEllEntry) <= 0)
    {
        QMessageBox::critical(this,
                              errorTitle,
                              "Полуось эллипса b не может быть меньше или равно нуля");

        *isOK = false;
        return;
    }

    control::Handler::setEllipseBase(readDouble(ui->aEllEntry),
                                     readDouble(ui->bEllEntry));
}

void MainWindow::readEllipseConc(bool *isOK)
{
    QString errorTitle = "Ошибка";

    *isOK = entryCheckRealProcess(ui->aEllEntry, errorTitle,
                                  "Начальное значение полуоси a не задано",
                                  "Начальное значение полуоси a не является "
                                  "вещественным числом");

    if (*isOK != true)
    {
        return;
    }

    if (readDouble(ui->aEllEntry) <= 0)
    {
        QMessageBox::critical(this,
                              errorTitle,
                              "Начальное значение полуоси a не может быть меньше или равно нуля");

        *isOK = false;
        return;
    }

    *isOK = entryCheckRealProcess(ui->afEntry, errorTitle,
                                  "Конечное значение полуоси a не задано",
                                  "Конечное значение полуоси a не является "
                                  "вещественным числом");

    if (*isOK != true)
    {
        return;
    }

    if (readDouble(ui->afEntry) <= 0)
    {
        QMessageBox::critical(this,
                              errorTitle,
                              "Конечное значение полуоси a не может быть меньше или равно нуля");

        *isOK = false;
        return;
    }

    if (readDouble(ui->afEntry) < readDouble(ui->aEllEntry))
    {
        QMessageBox::critical(this,
                              errorTitle,
                              "Значение af не может быть меньше a.");

        *isOK = false;
        return;
    }

    *isOK = entryCheckRealProcess(ui->bEllEntry, errorTitle,
                                  "Начальное значение полуоси b не задано",
                                  "Начальное значение полуоси b не является "
                                  "вещественным числом");

    if (*isOK != true)
    {
        return;
    }

    if (readDouble(ui->bEllEntry) <= 0)
    {
        QMessageBox::critical(this,
                              errorTitle,
                              "Начальное значение полуоси b не может быть меньше или равно нуля");

        *isOK = false;
        return;
    }

    *isOK = entryCheckIntProcess(ui->neEntry, errorTitle,
                                 "Кол-во концентрических эллипсов N не задано",
                                 "Кол-во концентрических эллипсов N не является "
                                 "целым числом");

    if (*isOK != true)
    {
        return;
    }

    if (readInt(ui->neEntry) < 2)
    {
        QMessageBox::critical(this,
                              errorTitle,
                              "Кол-во концентрических эллипсов "
                              "N не может быть меньше 2");

        *isOK = false;
        return;
    }

    control::Handler::setEllipseConc(readDouble(ui->aEllEntry),
                                     readDouble(ui->afEntry),
                                     readDouble(ui->bEllEntry),
                                     readInt(ui->neEntry));
}

void MainWindow::handlerTimerAction()
{
    control::hcommand_t command = control::Handler::getCommand();
    control::Handler::setCommand(control::DO_WAITING);

    AlgoIdx idx = (AlgoIdx) ui->algoList->currentIndex();

    switch (command)
    {
    case control::DO_WAITING:
        break;

    case control::DO_CIRCLE:
        qDebug() << "CIRC";
        ui->canvas->drawCircle(control::Handler::getCenter().x,
                               control::Handler::getCenter().y,
                               control::Handler::getCircleBase().R,
                               idx);
        break;

    case control::DO_CCONC:
        qDebug() << "CCONC";
        double h;
        h = control::Handler::getCircleConc().Rf - control::Handler::getCircleConc().R0;
        h /= control::Handler::getCircleConc().N - 1;

        for (int i = 0; i < control::Handler::getCircleConc().N; i++)
        {
            ui->canvas->drawCircle(control::Handler::getCenter().x,
                                   control::Handler::getCenter().y,
                                   control::Handler::getCircleConc().R0 + h * i,
                                   idx);
        }
        break;

    case control::DO_ELLIPSE:
        qDebug() << "ELL";
        ui->canvas->drawEllipse(control::Handler::getCenter().x,
                                control::Handler::getCenter().y,
                                control::Handler::getEllipseBase().a,
                                control::Handler::getEllipseBase().b,
                                idx);
        break;

    case control::DO_ECONC:
        qDebug() << "ECONC" << control::Handler::getEllipseConc().af << control::Handler::getEllipseConc().a0 <<
                    control::Handler::getEllipseConc().N <<
                    control::Handler::getEllipseConc().b0;
        h = control::Handler::getEllipseConc().af - control::Handler::getEllipseConc().a0;
        h /= control::Handler::getEllipseConc().N - 1;

        double axisRatio;
        axisRatio = control::Handler::getEllipseConc().b0 / control::Handler::getEllipseConc().a0;

        for (int i = 0; i < control::Handler::getEllipseConc().N; i++)
        {
            ui->canvas->drawEllipse(control::Handler::getCenter().x,
                                    control::Handler::getCenter().y,
                                    control::Handler::getEllipseConc().a0 + h * i,
                                    (control::Handler::getEllipseConc().a0 + h * i) * axisRatio,
                                    idx);
        }
        break;

    default:
        qDebug() << "Unknown command";
        break;
    }

    ui->canvas->repaint();
    this->handlerTimer->start(0);
}

void MainWindow::drawAction()
{
    bool isOK;

    this->readCenter(&isOK);

    if (!isOK)
    {
        return;
    }

    if (ui->figureTab->currentIndex() == 0)
    {
        if (!ui->concenterCFlag->isChecked())
        {
            this->readCircleBase(&isOK);

            if (!isOK)
            {
                return;
            }

            control::Handler::setCommand(control::DO_CIRCLE);
        }
        else
        {
            this->readCircleConc(&isOK);

            if (!isOK)
            {
                return;
            }

            control::Handler::setCommand(control::DO_CCONC);
        }
    }
    if (ui->figureTab->currentIndex() == 1)
    {
        if (!ui->concenterEFlag->isChecked())
        {
            this->readEllipseBase(&isOK);

            if (!isOK)
            {
                return;
            }

            control::Handler::setCommand(control::DO_ELLIPSE);
        }
        else
        {
            this->readEllipseConc(&isOK);

            if (!isOK)
            {
                return;
            }

            control::Handler::setCommand(control::DO_ECONC);
        }
    }
}

void MainWindow::clearAction()
{
    ui->canvas->clear();
    ui->canvas->repaint();
}
