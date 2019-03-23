#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QLineEdit>
#include <QMessageBox>

#include "colorpicker.h"

const QList<QString> algoes = {
    "ЦДА",
    "Брезенхем с действительными числами",
    "Брезенхем с целыми числами",
    "Брезенхем с устранением ступенчатости",
    "Алгоритм Ву",
    "Библиотечный способ"
};

QString getAlgoName(QString itemText);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    bool entryCheckRealProcess(QLineEdit *entry, QString errorTitle = "",
                               QString errorTextEmpty = "",  QString errorTextNReal = "");
    static double readDouble(QLineEdit *entry, bool *isOK = nullptr);

private slots:
    void smoothCBAction();

    void colorButtonsAction();
    void unitedColorButtonAction();

    void drawSLine();
    void drawCluster();
    void clearDisplay();

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // MAINWINDOW_H
