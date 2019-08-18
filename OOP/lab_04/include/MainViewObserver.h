#ifndef MAIN_VIEW_OBSERVER_H_
#define MAIN_VIEW_OBSERVER_H_

class MainViewObserver
{
private:
    virtual void importData() = 0;

    friend class MainViewEmitter;
};

#endif // MAIN_VIEW_OBSERVER_H_

