#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QPushButton>

class ColorButton : public QPushButton
{
    Q_OBJECT

private:
    QColor color;

public:
    ColorButton(QWidget *parent);

    void updateColor();
    void setColor(QColor color);

    QColor getColor();
};

#endif // COLORBUTTON_H
