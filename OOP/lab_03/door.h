#ifndef DOOR_H
#define DOOR_H

#include <QObject>
#include <QTimer>

static const int DTIME = 1000;

class Door : public QObject
{
    Q_OBJECT

    enum State
    {
        CLOSED = 0,
        OPENING,
        OPENED,
        CLOSING
    };

public:
    Door();

    bool isClosed();

signals:
    void opened();
    void closed();
    void openingTriggered();
    void closingTriggered();

public slots:
    void open();        // for OPENNING
    void close();       // for CLOSING

private slots:
    void unlock();      // for OPENED
    void lock();        // for CLOSED

private:
    int movingTime;

    State state;

    QTimer otimer;
    QTimer ctimer;
};

#endif // DOOR_H
