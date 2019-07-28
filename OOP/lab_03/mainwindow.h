#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "elevator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void target();
    void callup();
    void calldown();

    void updateDisplay();
    void updateIndicator();

private:
    Ui::MainWindow *ui;

    int floorsCount;

    Elevator *elevator;
};

#endif // MAINWINDOW_H
