#include "MainViewEmitter.h"

void MainViewEmitter::attach(MainViewObserver *observer)
{
    observers.append(observer);
}

void MainViewEmitter::notify(void (MainViewObserver::*update)())
{
    for (MainViewObserver *observer: observers)
    {
        (observer->*update)();
    }
}

void MainViewEmitter::importDataTriggered()
{
    notify(&MainViewObserver::importData);
}

