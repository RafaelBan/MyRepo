#ifndef GCONTROL_H
#define GCONTROL_H

#include <QWidget>

#include <QLCDNumber>
#include <QComboBox>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

#include "gbutton.h"
#include "gindicator.h"

class GControl : public QWidget
{
    Q_OBJECT

public:
    explicit GControl(QWidget *parent = nullptr);
    ~GControl();

    void setUp(int buttonsq = 0);

    int getButtonsCount();
    const GButton *getButton(int idx);

    int buttonsCount;
    GButton *buttons;
    GIndicator *indicator;

    QPushButton *upBtn;
    QPushButton *downBtn;
    QComboBox *floorsList;
    QLCDNumber *floorDisplay;

    QVBoxLayout *mlayout;
    QHBoxLayout *dlayout;
    QHBoxLayout *clayout;
    QGridLayout *blayout;

private:
    void buttonsInit(int quantity);
    GButton *createButton(int number);
};

#endif // GCONTROL_H
