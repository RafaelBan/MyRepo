#include "door.h"
#include <QDebug>

Door::Door() :
    QObject (),

    movingTime (DTIME),

    state (State::CLOSED)
{
    connect(&otimer, SIGNAL(timeout()), this, SLOT(unlock()));
    connect(&ctimer, SIGNAL(timeout()), this, SLOT(lock()));
}

bool Door::isClosed()
{
    return (state == State::CLOSED);
}

void Door::lock()
{
    if (state == State::CLOSING)
    {
        state = State::CLOSED;
        qDebug() << "Двери закрылись";
        emit closed();
    }
}

void Door::unlock()
{
    if (state == State::OPENING)
    {
        state = State::OPENED;
        qDebug() << "Двери открылись";
        emit opened();
    }
}

void Door::close()
{
    if (state == State::OPENED)
    {
        state = State::CLOSING;
        ctimer.setSingleShot(true);
        ctimer.start(movingTime);

        qDebug() << "Двери закрываются";
        emit closingTriggered();
    }
}

void Door::open()
{
    if (state == State::CLOSED || state == State::CLOSING)
    {
        int timerTime = movingTime;
        state = State::OPENING;

        if (state == State::CLOSING)
        {
            timerTime -= ctimer.remainingTime();
            ctimer.stop();
        }

        otimer.setSingleShot(true);
        otimer.start(timerTime);

        qDebug() << "Двери открываются";
        emit openingTriggered();
    }
}
