#include "gbutton.h"

GButton::GButton(QWidget *parent, int number) :
    QPushButton (parent)
{
    setNumber(number);
}

int GButton::getNumber()
{
    return number;
}

void GButton::setNumber(int number)
{
    this->number = number;
    setText(QString("%1").arg(QString::number(number), 2));
}
