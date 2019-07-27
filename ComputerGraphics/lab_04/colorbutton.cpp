#include "colorbutton.h"

ColorButton::ColorButton(QWidget *parent) :
    QPushButton (parent),
    color("black")
{
    this->updateColor();
}

void ColorButton::updateColor()
{
    this->setText("");
    this->setStyleSheet("* {"
                        "border-style: solid; "
                        "border-color: #424242; "
                        "border-width: 2px;"
                        "border-radius: 0px;"
                        "padding: 7px 3px;"
                        "background: " + this->color.name() + ";"
                        "}");
}

void ColorButton::setColor(QColor color)
{
    this->color = color;
    this->updateColor();
}

QColor ColorButton::getColor()
{
    return  this->color;
}
