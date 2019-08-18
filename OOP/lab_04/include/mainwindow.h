#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>

#include "MainView.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow, public MainView
{
    Q_OBJECT;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

private:
    Ui::MainWindow *ui;

    void connectAll();

private slots:
    void importData();

signals:
    void importDataCalled();
};

#endif // MAINWINDOW_H_

