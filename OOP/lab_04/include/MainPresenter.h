#ifndef MAIN_PRESENTER_H_
#define MAIN_PRESENTER_H_

#include "MainView.h"
#include "Model.h"
#include "MainViewKeeper.h"
#include "MainViewObserver.h"

class MainPresenter : public MainViewObserver, public MainViewKeeper
{
public:
    MainPresenter();

    void addView(MainView *view) override;

private:
    void importData() override;
};

#endif // MAIN_PRESENTER_H_

