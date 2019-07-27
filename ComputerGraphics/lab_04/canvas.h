#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>

#include <QPainter>
#include <QList>

#include "mycolors.h"
#include "drawalgo.h"

enum AlgoIdx
{
    canonical = 0,
    parametric,
    bresenham,
    midpoint,
    standard
};

struct DrawTaskCircle
{
    AlgoIdx idx;

    double x0;
    double y0;
    double R;

    QColor color;
};

struct DrawTaskEllipse
{
    AlgoIdx idx;

    double x0;
    double y0;
    double a;
    double b;

    QColor color;
};

class Canvas : public QWidget
{

    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);

    QColor backGroundColor();
    QColor foreGroundColor();

    void setBackGroundColor(QColor color);
    void setForeGroundColor(QColor color);

    void drawCircle(double x0, double y0, double R, AlgoIdx idx = standard);
    void drawEllipse(double x0, double y0, double a, double b, AlgoIdx idx = standard);

    void clear();

protected:
    void paintEvent(QPaintEvent *);

private:
    QColor _backGroundColor;
    QColor _foreGroundColor;

    QList<DrawTaskCircle> tasksCircle;
    QList<DrawTaskEllipse> tasksEllipse;
};

#endif // DRAWINGWIDGET_H
