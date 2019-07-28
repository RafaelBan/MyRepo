#ifndef GELEVATOR_H
#define GELEVATOR_H

#include <QWidget>

class GElevator : public QWidget
{
    Q_OBJECT

public:
    explicit GElevator(QWidget *parent = nullptr);
    ~GElevator();
};

#endif // GELEVATOR_H
