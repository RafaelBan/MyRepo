#include "scalingui.h"

ScalingUI::ScalingUI(QWidget *parent) :
    QWidget (parent),
    spacing1(new QSpacerItem(20, 0)),
    spacing2(new QSpacerItem(13, 0))
{
    this->widgetsInit();
    this->widgetsPose();
    this->widgetsFill();
}

ScalingUI::~ScalingUI()
{
    this->widgetsFree();
}

void ScalingUI::widgetsInit()
{
    this->title = new QLabel;

    this->layout = new QVBoxLayout;

    this->entryLayout = new QGridLayout;

    this->MxLabel = new QLabel;
    this->MxEntry = new QLineEdit;
    this->kxLabel = new QLabel;
    this->kxEntry = new QLineEdit;

    this->MyLabel = new QLabel;
    this->MyEntry = new QLineEdit;
    this->kyLabel = new QLabel;
    this->kyEntry = new QLineEdit;

    this->titleLayout = new QHBoxLayout;
    this->buttonLayout = new QHBoxLayout;

    this->scalingButton = new QPushButton;
}

void ScalingUI::widgetsPose()
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
    this->buttonLayout->addWidget(this->scalingButton);

    this->entryLayout->addWidget(this->MxLabel, 0, 0);
    this->entryLayout->addWidget(this->MxEntry, 0, 1);
    this->entryLayout->addItem(this->spacing1, 0, 2);
    this->entryLayout->addWidget(this->MyLabel, 0, 3);
    this->entryLayout->addWidget(this->MyEntry, 0, 4);
    this->entryLayout->addItem(this->spacing2, 0, 5);

    this->entryLayout->addWidget(this->kxLabel, 1, 0);
    this->entryLayout->addWidget(this->kxEntry, 1, 1);
    this->entryLayout->addWidget(this->kyLabel, 1, 3);
    this->entryLayout->addWidget(this->kyEntry, 1, 4);

    this->MxLabel->setSizePolicy(noScaling);
    this->MxEntry->setSizePolicy(noScaling);
    this->kxLabel->setSizePolicy(noScaling);
    this->kxEntry->setSizePolicy(noScaling);
    this->MyLabel->setSizePolicy(noScaling);
    this->MyEntry->setSizePolicy(noScaling);
    this->kyLabel->setSizePolicy(noScaling);
    this->kyEntry->setSizePolicy(noScaling);
    this->scalingButton->setSizePolicy(noScaling);

    this->entryLayout->setHorizontalSpacing(10);
    this->entryLayout->setVerticalSpacing(10);

    this->layout->setAlignment(this->entryLayout, Qt::AlignCenter);
    this->layout->setAlignment(this->buttonLayout, Qt::AlignCenter);
    this->layout->setAlignment(this->titleLayout, Qt::AlignCenter);
}

void ScalingUI::widgetsFill()
{
    this->title->setText("<h2 style=\"font-weight:normal;\">Масштабирование</h2>");

    this->MxLabel->setText("Mx:");
    this->MyLabel->setText("My:");

    this->kxLabel->setText("kx:");
    this->kyLabel->setText("ky:");

    this->scalingButton->setText("Произвести масштабирование");
}

void ScalingUI::widgetsFree()
{
    delete this->title;
    delete this->MxLabel;
    delete this->MxEntry;
    delete this->MyLabel;
    delete this->MyEntry;

    delete this->kxLabel;
    delete this->kxEntry;
    delete this->kyLabel;
    delete this->kyEntry;

    delete this->entryLayout;
    delete this->titleLayout;
    delete this->buttonLayout;

    delete this->layout;
}

