#include "transferui.h"

TransferUI::TransferUI(QWidget *parent) :
    QWidget (parent),
    spacing1(new QSpacerItem(20, 0)),
    spacing2(new QSpacerItem(13, 0))
{
    this->widgetsInit();
    this->widgetsPose();
    this->widgetsFill();
}

TransferUI::~TransferUI()
{
    this->widgetsFree();
}

void TransferUI::widgetsInit()
{
    this->title = new QLabel;

    this->layout = new QVBoxLayout;

    this->entryLayout = new QGridLayout;

    this->dxLabel = new QLabel;
    this->dxEntry = new QLineEdit;

    this->dyLabel = new QLabel;
    this->dyEntry = new QLineEdit;

    this->titleLayout = new QHBoxLayout;
    this->buttonLayout = new QHBoxLayout;

    this->transferButton = new QPushButton;
}

void TransferUI::widgetsPose()
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
    this->buttonLayout->addWidget(this->transferButton);
    this->layout->addLayout(this->buttonLayout);

    this->entryLayout->addWidget(this->dxLabel, 0, 0);
    this->entryLayout->addWidget(this->dxEntry, 0, 1);
    this->entryLayout->addItem(this->spacing1, 0, 2);
    this->entryLayout->addWidget(this->dyLabel, 0, 3);
    this->entryLayout->addWidget(this->dyEntry, 0, 4);
    this->entryLayout->addItem(this->spacing2, 0, 5);

    this->dxLabel->setSizePolicy(noScaling);
    this->dxEntry->setSizePolicy(noScaling);
    this->dyLabel->setSizePolicy(noScaling);
    this->dyEntry->setSizePolicy(noScaling);
    this->transferButton->setSizePolicy(noScaling);

    this->entryLayout->setHorizontalSpacing(10);
    this->entryLayout->setVerticalSpacing(10);

    this->layout->setAlignment(this->entryLayout, Qt::AlignCenter);
    this->layout->setAlignment(this->buttonLayout, Qt::AlignCenter);
    this->layout->setAlignment(this->titleLayout, Qt::AlignCenter);
}

void TransferUI::widgetsFill()
{
    this->title->setText("<h2 style=\"font-weight:normal;\">Перенос</h2>");

    this->dxLabel->setText("dx:");
    this->dyLabel->setText("dy:");

    this->transferButton->setText("Произвести перенос");
}

void TransferUI::widgetsFree()
{
    delete this->title;
    delete this->dxLabel;
    delete this->dxEntry;

    delete this->dyLabel;
    delete this->dyEntry;

    delete this->entryLayout;
    delete this->titleLayout;
    delete this->buttonLayout;

    delete this->layout;
}
