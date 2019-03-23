#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Компьютерная графика. ЛР2");

    this->widgetsInit();
    this->widgetsFill();
    this->widgetsPose();

    this->buttonsBind();
}

MainWindow::~MainWindow()
{
    this->widgetsFree();
}

void MainWindow::widgetsInit()
{
    QWidget *central = new QWidget(this);

    this->layout = new QHBoxLayout;

    this->widgetsLayout = new QVBoxLayout;
    this->controlsLayout = new QHBoxLayout;

    this->transferUI = new TransferUI;
    this->rotationUI = new RotationUI;
    this->scalingUI = new ScalingUI();

    this->stepBackButton = new QPushButton;
    this->resetButton = new QPushButton;

    this->drawingPlace = new GraphicsView;

    this->setCentralWidget(central);
}

void MainWindow::widgetsPose()
{
//    QSizePolicy noScaling = QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QSizePolicy subScaling = QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    this->centralWidget()->setLayout(this->layout);

    this->layout->addWidget(this->drawingPlace);
    this->layout->addLayout(this->widgetsLayout);

//    this->widgetsLayout->addSpacing(30);
    this->widgetsLayout->addWidget(this->transferUI);
    this->widgetsLayout->addWidget(this->scalingUI);
    this->widgetsLayout->addWidget(this->rotationUI);
    this->widgetsLayout->addSpacing(50);
    this->widgetsLayout->addLayout(this->controlsLayout);
    this->widgetsLayout->addSpacing(30);

    this->controlsLayout->addSpacing(25);
    this->controlsLayout->addWidget(this->stepBackButton);
    this->controlsLayout->addSpacing(15);
    this->controlsLayout->addWidget(this->resetButton);
    this->controlsLayout->addSpacing(25);

    this->transferUI->setSizePolicy(subScaling);
    this->scalingUI->setSizePolicy(subScaling);
    this->rotationUI->setSizePolicy(subScaling);

    this->drawingPlace->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->widgetsLayout->setAlignment(this->transferUI, Qt::AlignCenter);
    this->widgetsLayout->setAlignment(this->scalingUI, Qt::AlignCenter);
    this->widgetsLayout->setAlignment(this->rotationUI, Qt::AlignCenter);

    this->stepBackButton->setEnabled(false);
}

void MainWindow::widgetsFill()
{
    this->stepBackButton->setText("Шаг назад");
    this->resetButton->setText("Сбросить");

    this->drawingPlace->setMinimumSize(700, 700);
    this->drawingPlace->setFigures(Figure::initPicture());
}

void MainWindow::widgetsFree()
{
    delete this->transferUI;
    delete this->scalingUI;
    delete this->rotationUI;

    delete this->stepBackButton;
    delete this->resetButton;

    delete this->controlsLayout;
    delete this->widgetsLayout;
    delete this->drawingPlace;

    delete this->layout;

    delete this->centralWidget();
}

void MainWindow::buttonsBind()
{
    connect(this->transferUI->transferButton, SIGNAL(clicked(bool)), this, SLOT(doTransfer()));
    connect(this->scalingUI->scalingButton, SIGNAL(clicked(bool)), this, SLOT(doScaling()));
    connect(this->rotationUI->rotationButton, SIGNAL(clicked(bool)), this, SLOT(doRotation()));

    connect(this->stepBackButton, SIGNAL(clicked(bool)), this, SLOT(doStepBack()));
    connect(this->resetButton, SIGNAL(clicked(bool)), this, SLOT(doReset()));
}

void MainWindow::doTransfer()
{
    QString errorTitle = "Ошибка";
    QString dxStr = transferUI->dxEntry->text().simplified();
    QString dyStr = transferUI->dyEntry->text().simplified();

    if (dxStr == "")
    {
        QMessageBox::critical(this, errorTitle, "Смещение dx не задано.");
        return;
    }
    if (dyStr == "")
    {
        QMessageBox::critical(this, errorTitle, "Смещение dy не задано.");
        return;
    }

    if (!isDouble(dxStr))
    {
        QMessageBox::critical(this, errorTitle, "Введённое значение dx не является действительным числом.");
        return;
    }
    if (!isDouble(dyStr))
    {
        QMessageBox::critical(this, errorTitle, "Введённое значение dy не является действительным числом.");
        return;
    }

    this->history.push(this->drawingPlace->getFigures());
    this->stepBackButton->setEnabled(true);

    double dx = dxStr.toDouble();
    double dy = dyStr.toDouble();
    QList<Figure> newPicture;
    QList<Figure> oldPicture = this->drawingPlace->getFigures();

    foreach (Figure figure, oldPicture)
    {
        QList<point_t> figureBase;

        foreach (point_t point, figure.Points())
        {
            figureBase.append(point_t(point.x + dx, point.y + dy));
        }

        newPicture.append(Figure(figureBase));
    }

    this->drawingPlace->setFigures(newPicture);
    this->drawingPlace->repaint();

    qDebug() << "Transfer";
}

void MainWindow::doScaling()
{

    QString errorTitle = "Ошибка";
    QString MxStr = scalingUI->MxEntry->text().simplified();
    QString MyStr = scalingUI->MyEntry->text().simplified();
    QString kxStr = scalingUI->kxEntry->text().simplified();
    QString kyStr = scalingUI->kyEntry->text().simplified();

    if (MxStr == "")
    {
        QMessageBox::critical(this, errorTitle, "Координата Mx не задана.");
        return;
    }
    if (MyStr == "")
    {
        QMessageBox::critical(this, errorTitle, "Координата My не задана.");
        return;
    }
    if (kxStr == "")
    {
        QMessageBox::critical(this, errorTitle, "Коэффициент kx не задан.");
        return;
    }
    if (kyStr == "")
    {
        QMessageBox::critical(this, errorTitle, "Коэффициент ky не задан.");
        return;
    }

    if (!isDouble(MxStr))
    {
        QMessageBox::critical(this, errorTitle, "Введённое значение Mx не является действительным числом.");
        return;
    }
    if (!isDouble(MyStr))
    {
        QMessageBox::critical(this, errorTitle, "Введённое значение My не является действительным числом.");
        return;
    }
    if (!isDouble(kxStr))
    {
        QMessageBox::critical(this, errorTitle, "Введённое значение kx не является действительным числом.");
        return;
    }
    if (!isDouble(kyStr))
    {
        QMessageBox::critical(this, errorTitle, "Введённое значение ky не является действительным числом.");
        return;
    }

    this->history.push(this->drawingPlace->getFigures());
    this->stepBackButton->setEnabled(true);

    double Mx = MxStr.toDouble();
    double My = MyStr.toDouble();
    double kx = kxStr.toDouble();
    double ky = kyStr.toDouble();
    QList<Figure> newPicture;
    QList<Figure> oldPicture = this->drawingPlace->getFigures();

    foreach (Figure figure, oldPicture)
    {
        QList<point_t> figureBase;

        foreach (point_t point, figure.Points())
        {
            figureBase.append(point_t(point.x * kx + (1 - kx) * Mx,
                                      point.y * ky + (1 - ky) * My));
        }

        newPicture.append(Figure(figureBase));
    }

    this->drawingPlace->setFigures(newPicture);
    this->drawingPlace->repaint();

    qDebug() << "Scaling";
}

void MainWindow::doRotation()
{
    QString errorTitle = "Ошибка";
    QString TxStr = rotationUI->TxEntry->text().simplified();
    QString TyStr = rotationUI->TyEntry->text().simplified();
    QString ThetaStr = rotationUI->ThetaEntry->text().simplified();

    if (TxStr == "")
    {
        QMessageBox::critical(this, errorTitle, "Координата \u03F4x не задана."); // ϴ
        return;
    }
    if (TyStr == "")
    {
        QMessageBox::critical(this, errorTitle, "Координата \u03F4y не задана.");
        return;
    }
    if (ThetaStr == "")
    {
        QMessageBox::critical(this, errorTitle, "Угол поворота \u03F4 не задан.");
        return;
    }

    if (!isDouble(TxStr))
    {
        QMessageBox::critical(this, errorTitle, "Введённое значение \u03F4x не является действительным числом.");
        return;
    }
    if (!isDouble(TyStr))
    {
        QMessageBox::critical(this, errorTitle, "Введённое значение \u03F4y не является действительным числом.");
        return;
    }
    if (!isDouble(ThetaStr))
    {
        QMessageBox::critical(this, errorTitle, "Введённое значение \u03F4 не является действительным числом.");
        return;
    }

    this->history.push(this->drawingPlace->getFigures());
    this->stepBackButton->setEnabled(true);

    double Tx = TxStr.toDouble();
    double Ty = TyStr.toDouble();
    double theta = ThetaStr.toDouble();
    QList<Figure> newPicture;
    QList<Figure> oldPicture = this->drawingPlace->getFigures();

    foreach (Figure figure, oldPicture)
    {
        QList<point_t> figureBase;

        foreach (point_t point, figure.Points())
        {
            figureBase.append(point_t(Tx + (point.x - Tx) * cos(degToRad(theta)) + (point.y - Ty) * sin(degToRad(theta)),
                                      Ty - (point.x - Tx) * sin(degToRad(theta)) + (point.y - Ty) * cos(degToRad(theta))));
        }

        newPicture.append(Figure(figureBase));
    }

    this->drawingPlace->setFigures(newPicture);
    this->drawingPlace->repaint();

    qDebug() << "Rotation";
}

void MainWindow::doStepBack()
{
    QList<Figure> picture = this->history.pop();
    this->drawingPlace->setFigures(picture);
    this->drawingPlace->repaint();

    if (this->history.count() <= 0)
    {
        this->stepBackButton->setEnabled(false);
    }
}

void MainWindow::doReset()
{
    this->history.clear();
    this->drawingPlace->setFigures(Figure::initPicture());
    this->drawingPlace->repaint();

    this->stepBackButton->setEnabled(false);
}
