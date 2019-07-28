#include "elevator.h"
#include <QDebug>

Elevator::Elevator(int floorsCount) :
    QObject (),

    state (State::WAITING),
    floorsCount (floorsCount),

    delayTime(2000)
{
    connect(this, SIGNAL(called()), this, SLOT(wait()));
    connect(this, SIGNAL(wrongCalled()), this, SLOT(wait()));

    connect(this, SIGNAL(passed()), this, SLOT(process()));

    connect(this, SIGNAL(prepared()), this, SLOT(start()));
    connect(this, SIGNAL(openingTriggered()), this, SLOT(wait()));

    connect(this, SIGNAL(stopped()), this, SLOT(wait()));
    connect(this, SIGNAL(started()), this, SLOT(wait()));

    connect(this, SIGNAL(reached()), this, SLOT(process()));
    connect(this, SIGNAL(came()), this, SLOT(process()));
    connect(this, SIGNAL(keptMoving()), this, SLOT(wait()));

    connect(this, SIGNAL(delayed()), this, SLOT(wait()));

    connect(this, SIGNAL(closingTriggered()), this, SLOT(wait()));

    connect(&(car.door), SIGNAL(opened()), this, SLOT(delay()));
    connect(&dtimer, SIGNAL(timeout()), this, SLOT(close()));
    connect(&(car.door), SIGNAL(closed()), this, SLOT(start()));

    connect(&car, SIGNAL(crossedFloor()), this, SLOT(cross()));
}

bool Elevator::is(State state)
{
    return (this->state == state);
}

void Elevator::become(State state)
{
    this->state = state;
}

bool Elevator::isJobless()
{
    return goToList.isEmpty() && calledUp.isEmpty() && calledDown.isEmpty();
}

void Elevator::target(int floor)
{
    call(floor, 0);
}

void Elevator::callUp(int floor)
{
    call(floor, 1);
}

void Elevator::callDown(int floor)
{
    call(floor, -1);
}

int Elevator::direction()
{
    if (!car.isMoving())
    {
        return 0;
    }
    if (!car.isClosed())
    {
        return 0;
    }

    return car.getDirectrix();
}

int Elevator::position()
{
    return car.getPosition();
}

void Elevator::call(int floor, int direction)
{
    if (is(State::WAITING))
    {
        become(State::CALLING);

        if (floor < 1 || floor > floorsCount)
        {
            emit wrongCalled();
        }
        else
        {
            if (isJobless())
            {
                car.setDirectrix(floor - car.getPosition());
            }

            if (direction == 0)
            {
                goToList.append(floor);
                qDebug() << "Лифт вызван на этаж" << floor;
            }
            else if (direction > 0)
            {
                calledUp.append(floor);
                qDebug() << "Лифт вызван вверх с этажа" << floor;
            }
            else if (direction < 0)
            {
                calledDown.append(floor);
                qDebug() << "Лифт вызван вниз с этажа" << floor;
            }

            emit called();
        }
    }
}

void Elevator::wait()
{
    if (!(is(WAITING)))
    {
        become(State::WAITING);

        if (!car.isMoving() && !isJobless())
        {
            if (car.isClosed())
            {
                emit passed();
            }
        }
    }
}

void Elevator::process()
{
    if (is(WAITING))
    {
        become(State::PROCESSING);

        int pos = car.getPosition();
        int job = findClosestJob();

        car.setDirectrix(job - pos);

        qDebug() << "Лифт готовится к запуску в направлении" << car.getDirectrix();
        emit prepared();
    }
    else if (is(CROSSING))
    {
        become(State::PROCESSING);

        int pos = car.getPosition();
        int dir = car.getDirectrix();
        bool flag = false;

        goToList.removeAll(pos);
        if (dir >= 0 && !calledUp.isEmpty())
        {
            calledUp.removeAll(pos);
        }
        if (dir <= 0 && !calledDown.isEmpty())
        {
            calledDown.removeAll(pos);
        }

        if (dir != 0)
        {
            for (int i = pos; (1 <= i) and (i <= floorsCount); i += dir)
            {
                flag = flag or goToList.contains(i);

                if (dir > 0)
                {
                    flag = flag or calledUp.contains(i);
                }
                if (dir < 0)
                {
                    flag = flag or calledDown.contains(i);
                }
            }
        }

        if (!flag)
        {
            dir *= -1;
        }

        if (dir != 0)
        {
            for (int i = pos; (1 <= i) and (i <= floorsCount); i += dir)
            {
                flag = flag or goToList.contains(i);

                if (dir > 0)
                {
                    flag = flag or calledUp.contains(i);
                }
                if (dir < 0)
                {
                    flag = flag or calledDown.contains(i);
                }
            }
        }

        if (!flag)
        {
            dir *= -1;
        }

        if (dir == 0 && !isJobless())
        {
            int job = findClosestJob();

            dir = job - pos;
        }

        car.setDirectrix(dir);

        car.open();
        emit openingTriggered();
    }
}

void Elevator::start()
{
    if (is(WAITING) or is(PROCESSING))
    {
        become(State::STARTING);

        if (isJobless())
        {
            emit stopped();
        }
        else
        {
            car.start();
            qDebug() << "Лифт стартовал";
            emit started();
        }
    }
}

void Elevator::cross()
{
    if (is(WAITING) || is(STARTING))
    {
        become(State::CROSSING);

        int pos = car.getPosition();
        int dir = car.getDirectrix();

        qDebug() << "Лифт находится на этаже" << pos;

        if (goToList.contains(pos))
        {
            emit reached();
            car.stop();
        }
        else if (dir > 0 && calledUp.contains(pos))
        {
            emit came();
            car.stop();
        }
        else if (dir < 0 && calledDown.contains(pos))
        {
            emit came();
            car.stop();
        }
        else if (dir == 0)
        {
            emit came();
            car.stop();
        }
        else
        {
            emit keptMoving();
        }
    }
}

void Elevator::delay()
{
    if (is(WAITING))
    {
        become(DELAYING);

        dtimer.setSingleShot(true);
        dtimer.start(delayTime);
        emit delayed();
    }
}

void Elevator::close()
{
    if (is(WAITING))
    {
        become(CLOSING);

        car.close();
        emit closingTriggered();
    }
}

int Elevator::findClosestJob()
{
    QQueue<int> jobs;

    if (!goToList.isEmpty())
    {
        jobs.append(findClosestJob(goToList));
    }

    if (!calledUp.isEmpty())
    {
        jobs.append(findClosestJob(calledUp));
    }

    if (!calledDown.isEmpty())
    {
        jobs.append(findClosestJob(calledDown));
    }

    return findClosestJob(jobs);
}

int Elevator::findClosestJob(const QQueue<int> &jobs)
{
    int pos = car.getPosition();
    int rjob = jobs[0];
    int rdelta = abs(rjob - pos);

    for (int job: jobs)
    {
        int delta = abs(job - pos);

        if (rdelta > delta)
        {
            rdelta = delta;
            rjob = job;
        }
    }

    return rjob;
}
