#include "MainPresenter.h"

#include <iostream>

MainPresenter::MainPresenter() :
    QObject()
{
}

void MainPresenter::addView(MainView *view)
{
    views.append(view);

    connect(dynamic_cast<QObject *>(view), SIGNAL(importDataCalled()), this, SLOT(load()));
}

void MainPresenter::load()
{
    std::cout << "Data has been imported." << '\n';
}

