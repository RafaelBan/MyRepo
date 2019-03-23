#include "graphicsview.h"

#include <QDebug>
#include <cmath>
#include <iostream>

GraphicsView::GraphicsView(QWidget *parent)
    : QWidget (parent)
{

}

GraphicsView::~GraphicsView()
{

}

void GraphicsView::paintEvent(QPaintEvent *event)
{
    this->draw();
}

double GraphicsView::dX()
{
    return dx;
}

double GraphicsView::dY()
{
    return dy;
}

double GraphicsView::ScalingK()
{
    return scalingK;
}

void GraphicsView::draw()
{
    QPainter painter(this);

    painter.fillRect(0, 0, this->width(), this->height(), MyColors::gBackground);

    this->setScalingK();

    this->dx = this->width() / 2;
    this->dy = this->height() / 2;

    painter.setPen(QPen(MyColors::black, 0.5));
    painter.drawLine(QPointF(0, 0 * this->scalingK + dy), QPointF(this->width(), 0 * this->scalingK + dy));
    painter.drawLine(QPointF(0 * this->scalingK + dx, 0), QPointF(0 * this->scalingK + dx, this->height()));

    foreach (Figure figure, this->figures)
    {
        this->drawFigure(figure);
    }
}

void GraphicsView::setScalingK()
{
    double kx = (this->width() / 20);
    double ky = (this->height() / 20);

    this->scalingK = fmin(kx, ky);

//    this->scalingK = 50 / 1;
}

void GraphicsView::drawFigure(Figure figure)
{
    if (figure.Points().count() <= 0)
        return;

    QPointF A;
    QPointF start;
    QPainter painter(this);
    QList<point_t> points = figure.Points();

    painter.setPen(QPen(MyColors::black, 1.5));

    start = QPointF(+points[0].x * this->ScalingK() + this->dX(),
                    -points[0].y * this->ScalingK() + this->dY());

    A = start;

    for (int i = 1, len = points.count(); i < len; i++)
    {
        QPointF B = QPointF(+points[i].x * this->ScalingK() + this->dX(),
                            -points[i].y * this->ScalingK() + this->dY());

        painter.drawLine(A, B);

        A = B;
    }

    painter.drawLine(A, start);
}

void GraphicsView::setFigures(QList<Figure> figures)
{
    this->figures = figures;
}

QList<Figure> GraphicsView::getFigures(void)
{
    return this->figures;
}
