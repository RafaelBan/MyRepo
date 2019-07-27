#ifndef CANVAS_H
#define CANVAS_H

#include <QPainter>
#include <QWidget>
#include <QPixmap>
#include <QImage>
#include <QSet>
#include <QMouseEvent>

#include <cmath>
#include "mycolors.h"
#include "drawline.h"

struct PaintFigure
{
    bool doPaint;
    QColor color;
    QList< QPair<double, double> > points;

    PaintFigure(QList< QPair<double, double> > points) : doPaint(false), color(QColor("#000000")), points(points) {}
};

class Canvas : virtual public QWidget
{
    Q_OBJECT

public:
    Canvas(QWidget *parent = nullptr);

    QColor getPixelColor(int x, int y)
    {
        QPixmap pixmap(this->size());

        pixmap = this->grab();
        pixmap.save("C:\\Users\\Faris\\Documents\\Workplace\\ComputerGraphics\\build-lab_05-Desktop_Qt_5_12_1_MinGW_64_bit-Debug\\debug\\test.png");

        return pixmap.toImage().pixelColor(x, y);
    }

    bool isBGPixel(QPoint p)
    {
        return !paintPoints.contains( {p.x(), p.y()} );
    }

    QColor paintColor();
    QColor backGroundColor();
    QColor foreGroundColor();

    void setPaintColor(QColor color);
    void setBackGroundColor(QColor color);
    void setForeGroundColor(QColor color);

    void clear();

    QList<PaintFigure> getFigures();
    void addPoint(double x, double y);
    void closeReading();

    void addPixel(QPoint pixel);
    void remPixel(QPoint pixel);

    void drawLine(double x1, double y1, double x2, double y2);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    bool needColor = false;

    QColor _paintColor;
    QColor _backGroundColor;
    QColor _foreGroundColor;

    QList<QColor> edgeColors;
    QList< QPair<QPoint, QPoint> > edges;
    QList< QPair<double, double> > readingPoints;

    QList<PaintFigure> figures;
    QSet< QPair<int, int> > paintPoints;

    void paint(QPainter &painter);
    void paintFigure(PaintFigure figure, QPainter &painter);
};

#endif // CANVAS_H
