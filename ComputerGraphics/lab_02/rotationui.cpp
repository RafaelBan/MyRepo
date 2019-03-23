#include "rotationui.h"

RotationUI::RotationUI(QWidget *parent) :
    QWidget (parent),
    spacing1(new QSpacerItem(20, 0)),
    spacing2(new QSpacerItem(13, 0))
{
    this->widgetsInit();
    this->widgetsPose();
    this->widgetsFill();
}

RotationUI::~RotationUI()
{
    this->widgetsFree();
}

void RotationUI::widgetsInit()
{
    this->title = new QLabel;

    this->layout = new QVBoxLayout;

    this->entryLayout = new QGridLayout;

    this->TxLabel = new QLabel;
    this->TxEntry = new QLineEdit;

    this->TyLabel = new QLabel;
    this->TyEntry = new QLineEdit;

    this->ThetaLabel = new QLabel;
    this->ThetaEntry = new QLineEdit;

    this->ThetaLayout = new QHBoxLayout;
    this->titleLayout = new QHBoxLayout;
    this->buttonLayout = new QHBoxLayout;

    this->rotationButton = new QPushButton;
}

void RotationUI::widgetsPose()
{
    QSizePolicy noScaling = QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    this->setLayout(this->layout);

    this->titleLayout->addSpacing(13);
    this->titleLayout->addWidget(this->title);

    this->layout->addLayout(this->titleLayout);
    this->layout->addSpacing(20);

    this->layout->addLayout(this->entryLayout);
    this->layout->addSpacing(10);

    this->buttonLayout->addSpacing(20);
    this->layout->addLayout(this->buttonLayout);
    this->buttonLayout->addWidget(this->rotationButton);

    this->entryLayout->addWidget(this->TxLabel, 0, 0);
    this->entryLayout->addWidget(this->TxEntry, 0, 1);
    this->entryLayout->addItem(this->spacing1, 0, 2);
    this->entryLayout->addWidget(this->TyLabel, 0, 3);
    this->entryLayout->addWidget(this->TyEntry, 0, 4);
    this->entryLayout->addItem(this->spacing2, 0, 5);

    this->ThetaLayout->addSpacing(4);
    this->ThetaLayout->addWidget(this->ThetaLabel);
    this->ThetaLayout->addWidget(this->ThetaEntry);
    this->entryLayout->addLayout(this->ThetaLayout, 1, 0, 1, 5);
    this->entryLayout->setAlignment(this->ThetaLayout, Qt::AlignCenter);

    this->TxLabel->setSizePolicy(noScaling);
    this->TxEntry->setSizePolicy(noScaling);
    this->TyLabel->setSizePolicy(noScaling);
    this->TyEntry->setSizePolicy(noScaling);
    this->ThetaLabel->setSizePolicy(noScaling);
    this->ThetaEntry->setSizePolicy(noScaling);
    this->rotationButton->setSizePolicy(noScaling);

    this->entryLayout->setHorizontalSpacing(10);
    this->entryLayout->setVerticalSpacing(10);

    this->layout->setAlignment(this->entryLayout, Qt::AlignCenter);
    this->layout->setAlignment(this->buttonLayout, Qt::AlignCenter);
    this->layout->setAlignment(this->titleLayout, Qt::AlignCenter);
}

void RotationUI::widgetsFill()
{
    this->title->setText("<h2 style=\"font-weight:normal;\">Поворот</h2>");

    this->TxLabel->setText("\u03F4x:");
    this->TyLabel->setText("\u03F4y:");

    this->ThetaLabel->setText("\u03F4:"); // ϴ

    this->rotationButton->setText("Произвести поворот");
}

void RotationUI::widgetsFree()
{
    delete this->title;
    delete this->TxLabel;
    delete this->TxEntry;
    delete this->TyLabel;
    delete this->TyEntry;

    delete this->ThetaLabel;
    delete this->ThetaEntry;

    delete this->ThetaLayout;
    delete this->entryLayout;

    delete this->titleLayout;
    delete this->buttonLayout;

    delete this->layout;
}
