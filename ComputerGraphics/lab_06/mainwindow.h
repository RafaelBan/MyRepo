#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QColorDialog>
#include <QMessageBox>
#include <QLineEdit>

#include "canvas.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    Ui::MainWindow *ui;

    QString mouseMoveMessage;
    QString repaintMessage;

    void updateStatusMessage();

    void connectAll();

    bool entryCheckIntProcess(QLineEdit *entry, QString errorTitle,
                              QString errorTextEmpty, QString errorText);
    bool entryCheckRealProcess(QLineEdit *entry, QString errorTitle,
                               QString errorTextEmpty, QString errorText);

private slots:
    void setBGColor();
    void setPaintColor();
    void setBorderColor();

    void setCanvasPoint();
    void setCanvasLine();
    void setCanvasSeed();

    void addPoint();
    void closeLine();

    void doPaint();
    void setDelay();

    void clear();
};

#endif // MAINWINDOW_H
