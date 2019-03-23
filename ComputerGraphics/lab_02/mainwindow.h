#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QStack>
#include <QString>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "graphicsview.h"

#include "transferui.h"
#include "rotationui.h"
#include "scalingui.h"

#include "figure.h"
#include "mylib.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    GraphicsView *drawingPlace;

    TransferUI *transferUI;
    RotationUI *rotationUI;
    ScalingUI *scalingUI;

    QHBoxLayout *layout;
    QVBoxLayout *widgetsLayout;
    QHBoxLayout *controlsLayout;

    QPushButton *stepBackButton;
    QPushButton *resetButton;

    QStack< QList<Figure> > history;

    void widgetsInit();
    void widgetsPose();
    void widgetsFill();
    void widgetsFree();

    void buttonsBind();

private slots:
    void doTransfer();
    void doScaling();
    void doRotation();

    void doStepBack();
    void doReset();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif // MAINWINDOW_H
