#ifndef GBUTTON_H
#define GBUTTON_H

#include <QPushButton>

class GButton : public QPushButton
{
    Q_OBJECT

public:
    explicit GButton(QWidget *parent = nullptr, int number = 0);

    int getNumber();
    void setNumber(int number);

private:
    int number;
};

#endif // GBUTTON_H
