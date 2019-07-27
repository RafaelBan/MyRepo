#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

#include <QPainter>
#include <QMouseEvent>

#include <QStack>
#include <QMap>

#include <cmath>
#include "mycolors.h"
#include "mycursors.h"
#include "drawline.h"

class Canvas : virtual public QWidget
{
    Q_OBJECT

public:
    using State = enum {SEED, LINE, POINT};

    Canvas(QWidget *parent = nullptr);

    bool isBGColor(int x, int y);
    bool isFGColor(int x, int y);
    bool isPaintColor(int x, int y);

    QColor paintColor();
    QColor backGroundColor();
    QColor foreGroundColor();

    void setPaintColor(QColor color);
    void setBackGroundColor(QColor color);
    void setForeGroundColor(QColor color);

    void clear();

    void addBorderPixel(int x, int y);

    void paintPixel(QPoint pixel);
    void unpaintPixel(QPoint pixel);

    void drawLine(QPoint p1, QPoint p2);
    void lock();

    void setState(State state);

    void setSeed(QPoint point);
    void resetSeed();
    bool isSeedMarked();

    void paint();
    void touchPoint(int x, int y);

    void setDelay(bool flag);

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void leaveEvent(QEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    QColor _paintColor;
    QColor _backGroundColor;
    QColor _foreGroundColor;

    bool locked;
    bool seedMarked;
    QPoint seed;
    QPoint firstPoint;
    QPoint lastPoint;

    QMap< QPair<int, int>, QColor > paintPixels;
    QMap< QPair< QPair<int, int>, QPair<int, int> >, QColor > tempEdges;

    State state;

    bool delayEnabled;

    inline void paintCheckLine(int x, int y, int xr, QStack<QPoint> &stack);
};

#endif // CANVAS_H
