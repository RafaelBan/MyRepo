#ifndef CAR_H
#define CAR_H

#include <QObject>
#include <QTimer>

#include "door.h"

class Car : public QObject
{
    Q_OBJECT

    enum State
    {
        WAITING_CLOSED = 0,
        WAITING_NOT_CLOSED,
        STARTING,
        MOVING_ALONG,
        MOVING_BETWEEN,
        STOPPING
    };

    enum Direction
    {
        DOWN = -1,
        STAY = 0,
        UP = 1
    };

public:
    Car();

    int getPosition();

    int getDirectrix();
    void setDirectrix(int dir);

    bool isMoving();
    bool isClosed();

    void open();
    void close();

signals:
    void started();
    void stopped();

    void startTriggered();
    void stopTriggered();

    void reachedFloor();
    void crossedFloor();
    void leftFloor();

    void opened();
    void closed();

public slots:
    void start();
    void stop();

    void waitNotClosed();
    void waitClosed();

private slots:
    void moveBetween();
    void moveAlong();

private:
    int movingTime;
    int position;
    Direction directrix;

    Door door;
    State state;

    QTimer mtimer;

    friend class Elevator;
};

#endif // CAR_H
