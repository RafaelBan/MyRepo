#include "car.h"
#include <QDebug>

Car::Car() :
    QObject (),

    movingTime(1000),

    position (1),
    directrix(Direction::STAY),

    state (State::WAITING_CLOSED)
{
    connect(&mtimer, SIGNAL(timeout()), this, SLOT(moveBetween()));

    connect(this, SIGNAL(reachedFloor()), this, SLOT(moveAlong()));
    connect(this, SIGNAL(startTriggered()), this, SLOT(moveAlong()));

    connect(this, SIGNAL(stopTriggered()), this, SLOT(waitClosed()));
    connect(&door, SIGNAL(closed()), this, SLOT(waitClosed()));

    connect(this, SIGNAL(stopped()), this, SLOT(waitNotClosed()));
    connect(&door, SIGNAL(openingTriggered()), this, SLOT(waitNotClosed()));
}

int Car::getPosition()
{
    return position;
}

int Car::getDirectrix()
{
    return directrix;
}

void Car::setDirectrix(int dir)
{
    if (dir < 0)
    {
        directrix = Direction::DOWN;
    }

    if (dir == 0)
    {
        directrix = Direction::STAY;
    }

    if (dir > 0)
    {
        directrix = Direction::UP;
    }
}

bool Car::isMoving()
{
    return !(state == State::WAITING_CLOSED || state == State::WAITING_NOT_CLOSED || state == State::STOPPING);
}

bool Car::isClosed()
{
//    return (state == !State::WAITING_NOT_CLOSED);
    return door.isClosed();
}

void Car::open()
{
    door.open();
}

void Car::close()
{
    door.close();
}

void Car::waitClosed()
{
    if (state == State::STOPPING)
    {
        state = State::WAITING_CLOSED;
        emit stopped();
    }
    else if (state == State::WAITING_NOT_CLOSED)
    {
        state = State::WAITING_CLOSED;
        emit closed();
    }
}

void Car::waitNotClosed()
{
    if (state == State::WAITING_CLOSED)
    {
        state = State::WAITING_NOT_CLOSED;
        emit opened();
    }
}

void Car::start()
{
    if (state == State::WAITING_CLOSED)
    {
        state = State::STARTING;
        emit startTriggered();
    }
}

void Car::stop()
{
    if (state == State::MOVING_ALONG)
    {
        state = State::STOPPING;
        emit stopTriggered();
    }
}

void Car::moveAlong()
{
    if (state == State::STARTING || state == State::MOVING_BETWEEN)
    {
        state = State::MOVING_ALONG;

        if (state == State::STARTING)
        {
            emit started();
        }
        emit crossedFloor();

        if (state == State::MOVING_ALONG)
        {
            mtimer.setSingleShot(true);
            mtimer.start(movingTime);
            emit leftFloor();
        }
    }
}

void Car::moveBetween()
{
    if (state == State::MOVING_ALONG)
    {
        state = State::MOVING_BETWEEN;
        position += directrix;

        emit reachedFloor();
    }
}
