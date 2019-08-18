#ifndef MAIN_PRESENTER_H_
#define MAIN_PRESENTER_H_

#include <QObject>

#include "MainView.h"
#include "Model.h"
#include "MainViewContainer.h"

class MainPresenter : public QObject
{
    Q_OBJECT;

public:
    MainPresenter();

    void addView(MainView *view);

private:
    MainViewContainer views;

private slots:
    void load();
};

#endif // MAIN_PRESENTER_H_

