#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
#include <QTimer>
#include <QQueue>

#include "car.h"

class Elevator : public QObject
{
    Q_OBJECT

    enum State
    {
        WAITING = 0,
        CALLING,
        STARTING,
        CROSSING,
        PROCESSING,
        DELAYING,
        CLOSING,
    };

public:
    Elevator(int floorsCount);

    bool isJobless();

    void target(int floor);
    void callUp(int floor);
    void callDown(int floor);

    int direction();
    int position();

signals:
    void started();
    void stopped();
    void keptMoving();
    void finished();
    void processed();
    void delayed();
    void openingTriggered();
    void closingTriggered();

    void wrongCalled();
    void wrongStarted();

    void called();

    void reached();
    void came();

    void prepared();
    void passed();

public slots:

private slots:
    void wait();
    void call(int floor, int direction);
    void start();
    void cross();
    void process();
    void delay();
    void close();

private:
    State state;

    int floorsCount;
    QQueue<int> goToList;
    QQueue<int> calledDown;
    QQueue<int> calledUp;

    bool is(State state);
    void become(State state);

    int findClosestJob();
    int findClosestJob(const QQueue<int> &jobs);

    Car car;

    int delayTime;
    QTimer dtimer;
};

#endif // ELEVATOR_H
