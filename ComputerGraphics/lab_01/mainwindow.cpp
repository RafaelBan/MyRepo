#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Компьютерная графика. ЛР1");

    this->initWidgets();
    this->placeWidgets();
    this->decorateWidgets();

    this->bindButtons();
}

MainWindow::~MainWindow()
{
    this->freeWidgets();
}

void MainWindow::initWidgets()
{
    this->drawingPlace = new GrapicsView;

    this->labelX = new QLabel;
    this->labelY = new QLabel;
    this->entryX = new QLineEdit;
    this->entryY = new QLineEdit;
    this->pointsList = new QListWidget;

    this->addPointButton = new QPushButton;
    this->remPointButton = new QPushButton;
    this->editPointButton = new QPushButton;
    this->calculateButton = new QPushButton;

    this->keepAxisCB = new QCheckBox;
    this->keepOrthCB = new QCheckBox;

    this->taskContent = new QLabel;

    this->layout = new QVBoxLayout;

    this->subLayout = new QHBoxLayout;
    this->entriesLayout = new QHBoxLayout;
    this->pointsListLayout = new QHBoxLayout;
    this->checkboxesLayout = new QHBoxLayout;
    this->pointButtonsLayout = new QHBoxLayout;

    this->clearSelection = new QShortcut(Qt::ALT + Qt::Key_A, this);

    this->widgetsLayout = new QVBoxLayout;
}

void MainWindow::freeWidgets()
{
    delete this->drawingPlace;

    delete this->labelX;
    delete this->labelY;

    delete this->entryX;
    delete this->entryY;
    delete this->pointsList;

    delete this->addPointButton;
    delete this->remPointButton;
    delete this->editPointButton;
    delete this->calculateButton;

    delete this->keepAxisCB;
    delete this->keepOrthCB;

    delete this->entriesLayout;
    delete this->pointsListLayout;
    delete this->checkboxesLayout;
    delete this->pointButtonsLayout;

    delete this->taskContent;

    delete this->widgetsLayout;

    delete this->subLayout;
    delete this->layout;

    delete this->clearSelection;

    delete this->centralWidget();
}

void MainWindow::placeWidgets()
{
    QWidget *central = new QWidget;

    central->setLayout(this->layout);
    this->setCentralWidget(central);

    this->layout->addLayout(this->subLayout);
    this->layout->addSpacing(20);
    this->layout->addWidget(this->taskContent);

    this->subLayout->addLayout(this->widgetsLayout);
    this->subLayout->addWidget(this->drawingPlace);

    this->entriesLayout->addWidget(this->labelX);
    this->entriesLayout->addWidget(this->entryX);
    this->entriesLayout->addSpacing(15);
    this->entriesLayout->addWidget(this->labelY);
    this->entriesLayout->addWidget(this->entryY);
    this->entriesLayout->addSpacing(30);

    this->widgetsLayout->addSpacing(20);
    this->widgetsLayout->addLayout(this->entriesLayout);
    this->widgetsLayout->addSpacing(5);
    this->widgetsLayout->addLayout(this->pointButtonsLayout);
    this->widgetsLayout->addSpacing(5);

    this->pointButtonsLayout->addWidget(this->addPointButton);
    this->pointButtonsLayout->addWidget(this->editPointButton);

    this->widgetsLayout->addWidget(this->remPointButton);
    this->widgetsLayout->addSpacing(15);
    this->widgetsLayout->addLayout(this->checkboxesLayout);
    this->widgetsLayout->addSpacing(5);
    this->widgetsLayout->addLayout(pointsListLayout);

    this->pointsListLayout->addSpacing(50);
    this->pointsListLayout->addWidget(this->pointsList);
    this->pointsListLayout->addSpacing(50);

    this->widgetsLayout->addSpacing(5);
    this->widgetsLayout->addWidget(this->calculateButton);
    this->widgetsLayout->addSpacing(15);

    this->checkboxesLayout->addWidget(this->keepAxisCB);
    this->checkboxesLayout->addSpacing(20);
    this->checkboxesLayout->addWidget(this->keepOrthCB);

    this->pointsList->setSelectionMode(QListWidget::MultiSelection);

    this->widgetsLayout->setAlignment(this->entriesLayout, Qt::AlignCenter);
    this->widgetsLayout->setAlignment(this->pointButtonsLayout, Qt::AlignCenter);
    this->widgetsLayout->setAlignment(this->remPointButton, Qt::AlignCenter);
    this->widgetsLayout->setAlignment(this->calculateButton, Qt::AlignCenter);
    this->widgetsLayout->setAlignment(this->checkboxesLayout, Qt::AlignCenter);

    this->keepAxisCB->setCheckState(Qt::CheckState::Checked);
    this->keepOrthCB->setCheckState(Qt::CheckState::Checked);
}

void MainWindow::decorateWidgets()
{
    QSizePolicy noScaling;
    QSizePolicy onlyVScaling;

    noScaling = QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    onlyVScaling = QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    this->addPointButton->setText("Добавить точку");
    this->remPointButton->setText("Удалить точку(и)");
    this->editPointButton->setText("Изменить точку");

    this->calculateButton->setText("Произвести вычисление");

    this->labelX->setText("x:");
    this->labelY->setText("y:");

    this->taskContent->setText("Набиев Фарис, ИУ7-43Б. ЛР1, Задание 24.\n"
                               "На плоскости дано множество точек. "
                               "Найти такой треугольник с вершинами в этих точках, "
                               "у которого сумма расстояний от точки пересечения "
                               "высот до координатных осей максимальна.");

    this->keepAxisCB->setText("Удерживать\nоси\nна экране");
    this->keepOrthCB->setText("Удерживать\nортоцентр\nна экране");

    this->pointsList->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    this->entryX->setSizePolicy(noScaling);
    this->entryY->setSizePolicy(noScaling);
    this->addPointButton->setSizePolicy(noScaling);
    this->remPointButton->setSizePolicy(noScaling);
    this->calculateButton->setSizePolicy(noScaling);

    this->taskContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->taskContent->setWordWrap(true);

    this->drawingPlace->setMinimumSize(700, 700);
}

void MainWindow::bindButtons()
{
    connect(this->addPointButton, SIGNAL(clicked(bool)), this, SLOT(addPoint()));
    connect(this->remPointButton, SIGNAL(clicked(bool)), this, SLOT(remPoint()));
    connect(this->editPointButton, SIGNAL(clicked(bool)), this, SLOT(editPoint()));

    connect(this->calculateButton, SIGNAL(clicked(bool)), this, SLOT(calculate()));

    connect(this->clearSelection, SIGNAL(activated()), this, SLOT(clearSelectionList()));

    connect(this->keepAxisCB, SIGNAL(stateChanged(int)), this, SLOT(keepCBAction()));
    connect(this->keepOrthCB, SIGNAL(stateChanged(int)), this, SLOT(keepCBAction()));
}

point_t MainWindow::readPoint(bool *isOK)
{
    *isOK = false;

    bool isDoubleX;
    bool isDoubleY;
    point_t point;
    QString strX;
    QString strY;
    QString errorTitle = "Ошибка";

    strX = this->entryX->text().simplified();
    strY = this->entryY->text().simplified();

    isDoubleX = isDouble(strX);
    isDoubleY = isDouble(strY);

    if (strX == "" && strY == "")
    {
        QMessageBox::critical(this, errorTitle, "Пустой ввод");
        return point;
    }
    else if (strX == "" && strY != "")
    {
        QMessageBox::critical(this, errorTitle, "Значение `x` не задано");
        return point;
    }
    else if (strX != "" && strY == "")
    {
        QMessageBox::critical(this, errorTitle, "Значение `y` не задано");
        return point;
    }

    if (isDoubleX == false && isDoubleY == false)
    {
        QMessageBox::critical(this, errorTitle, "Невозможно преобразовать введённые данные в действительные числа");
        return point;
    }
    else if (isDoubleX == false && isDoubleY != false)
    {
        QMessageBox::critical(this, errorTitle, "Значение `x` не является действительным числом");
        return point;
    }
    else if (isDoubleX != false && isDoubleY == false)
    {
        QMessageBox::critical(this, errorTitle, "Значение `y` не является действительным числом");
        return point;
    }

    point.x = strX.toDouble();
    point.y = strY.toDouble();

    for (int i = 0, len = this->pointsList->count(); i < len; i++)
    {
        QString cur_item;

        cur_item = this->pointsList->item(i)->text().simplified();

        if (point_t::parseStr(cur_item.toStdString()) == point)
        {
            QMessageBox::critical(this, errorTitle, "Данная точка уже добавлена");

            this->pointsList->clearSelection();
            this->pointsList->setCurrentRow(i);

            return point;
        }
    }

    *isOK = true;

    return point;
}

void MainWindow::addPoint()
{
    bool isOK;
    point_t point;
    QString item;

    point = this->readPoint(&isOK);

    if (isOK == false)
    {
        return;
    }

    item = point.toStr().c_str();
    this->pointsList->addItem(item);

    this->entryX->setText("");
    this->entryY->setText("");
}

void MainWindow::remPoint()
{
    QList<QListWidgetItem*> selectedItems = this->pointsList->selectedItems();

    for (int i = 0, len = selectedItems.count(); i < len; i++)
    {
        this->pointsList->removeItemWidget(selectedItems[i]);
        delete selectedItems[i];
    }
}

void MainWindow::calculate()
{
    QString errorTittle = "Ошибка";
    QList<point_t> points;
    QList<point_t> workPoints;
    QList<triangle_t> triangles;

    if (this->pointsList->count() < 3)
    {
        QMessageBox::critical(this, errorTittle, "Введено недостаточно точек для построения треугольника");
        return;
    }

    for (int i = 0, len = this->pointsList->count(); i < len; i++)
    {
        std::string itemText = this->pointsList->item(i)->text().toStdString();

        points.append(point_t::parseStr(itemText));
    }

    triangles = makeTriangels(points);

    if (triangles.count() <= 0)
    {
        QMessageBox::critical(this, errorTittle, "Введённые точки лежат на одной прямой. Невозможно построить треугольник");
        return;
    }

    triangle_t searchTriangle = findTriangle(triangles);

    if (this->keepAxisCB->checkState() == Qt::CheckState::Checked)
    {
        workPoints.append(point_t(0, 0));
    }

    if (this->keepOrthCB->checkState() == Qt::CheckState::Checked)
    {
        workPoints.append(searchTriangle.orthocenter());
    }

    workPoints.append(searchTriangle.A().copy());
    workPoints.append(searchTriangle.B().copy());
    workPoints.append(searchTriangle.C().copy());

    this->triangles.clear();
    this->triangles.append(searchTriangle);
    this->workPoints = workPoints;
    this->points= points;

    this->draw();
}

void MainWindow::draw()
{
    this->drawingPlace->setDisplayRange(this->workPoints);
    this->drawingPlace->setTriangles(this->triangles);

    this->drawingPlace->repaint();
}

void MainWindow::clearSelectionList()
{
    if (QWidget::focusWidget() == this->pointsList)
    {
        this->pointsList->clearSelection();
    }
}

void MainWindow::editPoint()
{
    bool isOK;
    point_t point;
    QString item;
    QString errorTitle = "Ошибка";
    QList<QListWidgetItem*> selectedItems = this->pointsList->selectedItems();

    if (selectedItems.count() < 1)
    {
        QMessageBox::critical(this, errorTitle, "Не выбрана точка для редактирования");
        return;
    }
    else if (selectedItems.count() > 1)
    {
        QMessageBox::critical(this, errorTitle, "За раз можно отредактировать только одну точку");
        return;
    }

    point = this->readPoint(&isOK);

    if (isOK == false)
    {
        return;
    }

    item = point.toStr().c_str();
    selectedItems[0]->setText(item);
    this->pointsList->clearSelection();

    this->entryX->setText("");
    this->entryY->setText("");
}

void MainWindow::keepCBAction()
{
    if (this->triangles.count() <= 0)
    {
        return;
    }

    this->workPoints.clear();

    triangle_t searchTriangle = this->triangles[0];

    if (this->keepAxisCB->checkState() == Qt::CheckState::Checked)
    {
        this->workPoints.append(point_t(0, 0));
    }

    if (this->keepOrthCB->checkState() == Qt::CheckState::Checked)
    {
        this->workPoints.append(searchTriangle.orthocenter());
    }

    this->workPoints.append(searchTriangle.A().copy());
    this->workPoints.append(searchTriangle.B().copy());
    this->workPoints.append(searchTriangle.C().copy());

    this->draw();
}
