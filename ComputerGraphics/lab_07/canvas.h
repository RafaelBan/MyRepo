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

    void setType(InputType type);

protected:
    void paintEvent(QPaintEvent *event);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void leaveEvent(QEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    const double EPSILON = 1e-4;

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

    bool cutterDefined;
    QPoint cp1;
    QPoint cp2;
    QPoint cp3;
    QPoint cp4;

    void draw_line(QPointF p1, QPointF p2, QPainter &painter);
    QBitArray getPointCode(QPointF p);
    int left();
    int right();
    int top();
    int bottom();
    bool sumCode(QBitArray code);

    double pointDist(QPointF p1, QPointF p2);
};

#endif // CANVAS_H
