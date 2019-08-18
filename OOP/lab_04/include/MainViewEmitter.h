#ifndef MAIN_VIEW_EMITTER_H_
#define MAIN_VIEW_EMITTER_H_

#include "MainViewObserver.h"
#include "Container.h"

class MainViewEmitter
{
public:
    void attach(MainViewObserver *observer);

protected:
    void importDataTriggered();

private:
    Container<MainViewObserver *> observers;
    void notify(void (MainViewObserver::*update)());
};

#endif // MAIN_VIEW_EMITTER_H_

