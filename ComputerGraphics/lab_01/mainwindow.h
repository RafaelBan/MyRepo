#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>

#include <QMainWindow>

#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QShortcut>
#include <QCheckBox>
#include <QListWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QListWidgetItem>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <vector>

#include "graphicsview.h"
#include "geometry.h"
#include "mylib.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private: // поля
//!     Виджет рисования
    GrapicsView *drawingPlace;

//!     Подписи полей ввода
    QLabel *labelX;
    QLabel *labelY;
    QLabel *taskContent;
//!     Поля ввода
    QLineEdit *entryX;
    QLineEdit *entryY;
//!     Кнопки добавлени, удаления точек и вычисления
    QPushButton *addPointButton;
    QPushButton *remPointButton;
    QPushButton *editPointButton;
    QPushButton *calculateButton;
//!     Список точек
    QListWidget *pointsList;

    QCheckBox *keepAxisCB;
    QCheckBox *keepOrthCB;
//!     Главный компоновщик
    QVBoxLayout *layout;
//!     Компоновщик всех виджетов, кроме виджета рисования
    QVBoxLayout *widgetsLayout;

    QHBoxLayout *subLayout;
    QHBoxLayout *entriesLayout;
    QHBoxLayout *pointsListLayout;
    QHBoxLayout *checkboxesLayout;
    QHBoxLayout *pointButtonsLayout;

    QShortcut *clearSelection;

    QList<point_t> points;
    QList<point_t> workPoints;
    QList<triangle_t> triangles;

private: // функции
    void draw();
    void initWidgets();
    void freeWidgets();
    void placeWidgets();
    void decorateWidgets();

    void bindButtons();

    point_t readPoint(bool *isOK);

private slots:
    void addPoint();
    void remPoint();
    void editPoint();
    void calculate();
    void clearSelectionList();
    void keepCBAction();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif // MAINWINDOW_H
