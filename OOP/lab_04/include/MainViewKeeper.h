#ifndef MAIN_VIEW_KEEPER_H_
#define MAIN_VIEW_KEEPER_H_

#include "MainView.h"
#include "Container.h"

class MainViewKeeper
{
public:
    virtual void addView(MainView *view);

private:
    Container<MainView *> views;
};

#endif // MAIN_VIEW_KEEPER_H_

