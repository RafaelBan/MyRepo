#ifndef CANVAS_H
#define CANVAS_H

#include <QPainter>
#include <QWidget>
#include <QMouseEvent>

#include <QList>
#include <QBitArray>

#include <cmath>
#include "mycolors.h"
#include "drawline.h"

class Canvas : virtual public QWidget
{
    Q_OBJECT

public:
    enum InputType
    {
        Cutter,
        Line
    };

    enum InputState
    {
        Undefined,
        Entering
    };

    Canvas(QWidget *parent = nullptr);

    QColor cutColor();
    QColor cutterColor();
    QColor backGroundColor();
    QColor foreGroundColor();

    void setCutColor(QColor color);
    void setCutterColor(QColor color);
    void setBackGroundColor(QColor color);
    void setForeGroundColor(QColor color);

    void clear();

    void addPoint(int x, int y);
    void touchPoint(int x, int y);
    void lockPoint(int x, int y);

    void selectEdge(int x, int y);
    void unselectEdge();

    void setType(InputType type);

    bool isConvex(QList<QPoint> figure, int *sign = nullptr);

    double smul(QPointF v1, QPointF v2);
    double vmul(QPointF v1, QPointF v2);

protected:
    void paintEvent(QPaintEvent *event);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void leaveEvent(QEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    const double EPSILON = 1e-7;

    InputType type;
    InputState state;
    QPoint tempPoint;

    QColor _cutColor;
    QColor _cutterColor;
    QColor _backGroundColor;
    QColor _foreGroundColor;

    QList< QPair<QPoint, QPoint> > tempEdges;

    QList<bool> doCutting;
    QList< QPair<QPoint, QPoint> > edges;

    QList<QPoint> cutterPoints;

    bool edgeIsSelected;
    QPair<QPoint, QPoint> selectedEdge;

    void draw_line(QPointF p1, QPointF p2, QPainter &painter);

    double pointDist(QPointF p1, QPointF p2);
    double pointLineDist(QPointF p0, QPointF p1, QPointF p2);
    QPointF toParallelPoint(QPointF p2, QPointF p1);
    QPointF toParallelPoint(QPointF p2, QPointF p1, QPointF A, QPointF B);
    QPointF pointProjection(QPointF p0, QPointF p1, QPointF p2);
    QPointF pointProjection(QPointF p0, QPointF p1, double A, double B, double C);
};

#endif // CANVAS_H
