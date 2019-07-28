#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFileDialog>
#include <QMessageBox>

#include "management.h"
#include "check_entry.h"

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

    void update(Handler &handler, int exit_code);
    void update_display(const point2d_t *points, size_t pointsq);

private slots:
    void loadFileAction();
    void saveFileAction();
    void transferReadAction();
    void scalingReadAction();
    void rotationReadAction();
};

#endif // MAINWINDOW_H
