#include "gcontrol.h"

GControl::GControl(QWidget *parent) :
    QWidget (parent),

    buttonsCount (0),
    buttons (nullptr),

    indicator (new GIndicator),

    upBtn (new QPushButton),
    downBtn (new QPushButton),
    floorsList (new QComboBox),
    floorDisplay (new QLCDNumber),

    mlayout (new QVBoxLayout),
    dlayout (new QHBoxLayout),
    clayout (new QHBoxLayout),
    blayout (new QGridLayout)
{
    setLayout(mlayout);

    mlayout->addLayout(dlayout);
    mlayout->addLayout(blayout);
    mlayout->addSpacing(100);
    mlayout->addWidget(floorsList);
    mlayout->addLayout(clayout);

    dlayout->addWidget(indicator);
    dlayout->addWidget(floorDisplay);

    clayout->addWidget(upBtn);
    clayout->addWidget(downBtn);

    floorDisplay->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    floorDisplay->setStyleSheet("*{ background-color: black; }");
    floorDisplay->setPalette(Qt::red);

    indicator->setBackground("black");
    indicator->setForeground("#7d0000");
    indicator->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    indicator->setMinimumSize(20, 20);

    upBtn->setText("Вверх");
    downBtn->setText("Вниз");
}

GControl::~GControl()
{
    buttonsCount = 0;
    delete[] buttons;

    delete indicator;

    delete upBtn;
    delete downBtn;
    delete floorsList;
    delete floorDisplay;

    delete blayout;
    delete dlayout;
    delete clayout;
    delete mlayout;
}

int GControl::getButtonsCount()
{
    return buttonsCount;
}

const GButton *GControl::getButton(int idx)
{
    if (idx >= buttonsCount)
    {
        return nullptr;
    }

    return &buttons[idx];
}

void GControl::buttonsInit(int quantity)
{
    buttonsCount = quantity;
    buttons = new GButton[quantity];

    for (int i = 0; i < quantity; i++)
    {
        buttons[i].setNumber(i + 1);
    }
}

GButton *GControl::createButton(int number)
{
    return new GButton(this, number);
}

void GControl::setUp(int buttonsq)
{
    if (!buttons)
    {
        delete[] buttons;

        buttonsCount = 0;
        buttons = nullptr;
    }

    floorsList->clear();
    buttonsInit(buttonsq);

    for (int idx = 0; idx < buttonsq; idx++)
    {
        int i = 5 - (idx % 5);
        int j = idx / 5;

        blayout->addWidget(buttons + idx, i, j);
        floorsList->addItem(QString::number(idx + 1));
    }
}
