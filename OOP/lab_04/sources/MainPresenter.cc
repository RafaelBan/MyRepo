#include "MainPresenter.h"

#include <iostream>

MainPresenter::MainPresenter()
{
}

void MainPresenter::addView(MainView *view)
{
    MainViewKeeper::addView(view);
    view->attach(this);
}

void MainPresenter::importData()
{
    std::cout << "Data has been imported!!!" << '\n';
}

