#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>

#include <QMessageBox>
#include <QColorDialog>

#include <QTimer>
#include <QDebug>

#include "handler.h"
#include "drawalgo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;

    QTimer *handlerTimer;

    void connectings();

    bool entryCheckRealProcess(QLineEdit *entry, QString errorTitle = "",
                               QString errorTextEmpty = "",  QString errorTextNReal = "");
    bool entryCheckIntProcess(QLineEdit *entry, QString errorTitle = "",
                              QString errorTextEmpty = "",  QString errorTextNReal = "");

private slots:
    void bgColorSet();
    void fgColorSet();
    void fgToBgColorSet();

    void centerSet();

    void drawAction();
    void clearAction();

    void readCenter(bool *isOK);
    void readCircleBase(bool *isOK);
    void readCircleConc(bool *isOK);
    void readEllipseBase(bool *isOK);
    void readEllipseConc(bool *isOK);

    void handlerTimerAction();
};

#endif // MAINWINDOW_H
