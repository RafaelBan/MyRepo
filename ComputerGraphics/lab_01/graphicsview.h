#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QPainter>
#include <QPointF>
#include <QWidget>
#include <QList>

#include "geometry.h"

const int TextRectW = 100;
const int TextRectH = 60;
const int TextRectT = 25;
const int TextRectL = 45;
const int TextFontSZ = 12;

class GrapicsView : public QWidget
{
    Q_OBJECT

private:
    double xMax;
    double xMin;
    double yMax;
    double yMin;
    double xRange;
    double yRange;
    double scalingK;
    double imageOffset;

    QList<point_t> points;
    QList<triangle_t> triangles;

    void setScalingK();

public:
    explicit GrapicsView(QWidget *parent = nullptr);
    ~GrapicsView();

    void draw();

    void setPoints(QList<point_t> points);

    void setTriangles(triangle_t triangle);
    void setTriangles(QList<triangle_t> triangles);

    void setDisplayRange(QList<point_t> workPoints);

    double xCartToDisp(double xC);
    double yCartToDisp(double yC);
    double xDispToCart(double xD);
    double yDispToCart(double yD);

protected:
    void paintEvent(QPaintEvent *event);
};

namespace MyColors
{
    const QColor gBackground = QColor("#eeeeee");
    const QColor red = QColor("#d50000");
    const QColor green = QColor("#00bc6c");
    const QColor blue = QColor("#2962ff");
    const QColor black = QColor("#000000");
    const QColor pink = QColor("#e91e63");
}

#endif // GRAPHICSVIEW_H
