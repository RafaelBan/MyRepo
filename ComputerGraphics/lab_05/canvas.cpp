#include "canvas.h"

#include <cmath>
#include <QTest>
#include <QGuiApplication>

using namespace std;

Canvas::Canvas(QWidget *parent) :
    QWidget (parent),

    _paintColor(MyColors::pink),
    _backGroundColor(MyColors::softPink),
    _foreGroundColor(MyColors::black)
{
}

QColor Canvas::backGroundColor()
{
    return _backGroundColor;
}

QColor Canvas::foreGroundColor()
{
    return _foreGroundColor;
}

QColor Canvas::paintColor()
{
    return _paintColor;
}

void Canvas::setBackGroundColor(QColor color)
{
    _backGroundColor = color;
}

void Canvas::setForeGroundColor(QColor color)
{
    _foreGroundColor = color;
}

void Canvas::setPaintColor(QColor color)
{
    _paintColor = color;
}

void Canvas::paintEvent(QPaintEvent *event)
{
    if (needColor)
    {
        return;
    }

    QWidget::paintEvent(event);

    QPainter painter(this);

    painter.fillRect(0, 0, width(), height(), backGroundColor());

    painter.setPen(this->paintColor());
    this->paint(painter);

    for (int i = 0; i < edges.count(); i++)
    {
        auto edge = edges[i];

        painter.setPen(edgeColors[i]);

        drawAlgo::draw_line_bresenham_i(edge.first.x(), edge.first.y(),
                                        edge.second.x(), edge.second.y(), painter);
    }
}

void Canvas::clear()
{
    readingPoints.clear();
    edges.clear();
    edgeColors.clear();
    paintPoints.clear();
    figures.clear();

    this->repaint();
}

void Canvas::drawLine(double x1, double y1, double x2, double y2)
{
    this->edges.append({ {int(round(x1)), int(round(y1))},
                         {int(round(x2)), int(round(y2))} });
    this->edgeColors.append(foreGroundColor());

    this->repaint();
}

void Canvas::addPoint(double x, double y)
{
    if (!readingPoints.isEmpty())
    {
        this->drawLine(readingPoints.last().first, readingPoints.last().second, x, y);
    }
    readingPoints.append({ x, y });
}

void Canvas::closeReading()
{;
    if (readingPoints.count() > 2)
    {
        this->figures.append(PaintFigure(readingPoints));
    }

    if (!readingPoints.isEmpty())
    {
        this->drawLine(readingPoints.first().first, readingPoints.first().second,
                         readingPoints.last().first, readingPoints.last().second);
    }
    readingPoints.clear();
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        double x = event->localPos().x();
        double y = event->localPos().y();

        if (QGuiApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))
        {
            double last_x = this->readingPoints.back().first;
            double last_y = this->readingPoints.back().second;

            if (fabs(last_x - x) < fabs(last_y - y))
            {
                x = last_x;
            }
            else
            {
                y = last_y;
            }
        }

        this->addPoint(x, y);
    }
    else if (event->button() == Qt::RightButton)
    {
        this->closeReading();
    }
}

QList<PaintFigure> Canvas::getFigures()
{
    return figures;
}

void Canvas::addPixel(QPoint pixel)
{
    this->paintPoints.insert( {pixel.x(), pixel.y()} );
}

void Canvas::remPixel(QPoint pixel)
{
    this->paintPoints.remove( {pixel.x(), pixel.y()} );
}

void Canvas::paint(QPainter &painter)
{
    painter.setPen(paintColor());

    for (auto pixel: paintPoints)
    {
        painter.drawPoint(pixel.first, pixel.second);
    }

//    for (auto figure: figures)
//    {
//        paintFigure(figure, painter);
//    }
}

void Canvas::paintFigure(PaintFigure figure, QPainter &painter)
{
    return;
    for (int i = 0, j = figure.points.count() - 1; i < figure.points.count(); j = i, i++)
    {
        auto _p1 = figure.points[j];
        auto _p2 = figure.points[i];

        QPoint p1 = { int(round(_p1.first)), int(round(_p1.second)) };
        QPoint p2 = { int(round(_p2.first)), int(round(_p2.second)) };

        if (p1.y() < p2.y())
        {
            std::swap(p1, p2);
        }

        int xMax = width();

        if (p1 == p2)
        {
            addPixel(p1);
            continue;
        }

        bool swap_flag = false;

        int dx = p2.x() - p1.x();
        int dy = p2.y() - p1.y();

        int sx = (dx > 0) ? 1 : -1;
        int sy = (dy > 0) ? 1 : -1;

        dx = abs(dx);
        dy = abs(dy);

        if (dx < dy)
        {
             std::swap(dx, dy);
             swap_flag = true;
        }

        int m = dy;
        int error = m;

        int x = p1.x();
        int y = p1.y();
        int prev_y = y - sy;

        for (int _x = x; _x < xMax; _x++)
        {
            if (!isBGPixel(QPoint(_x, y)))
            {
                remPixel(QPoint(_x, y));
                painter.setPen(backGroundColor());
                painter.drawPoint(_x, y);
            }
            else
            {
                addPixel(QPoint(_x, y));
                painter.setPen(paintColor());
                painter.drawPoint(_x, y);
            }
        }

        for (int i = 0; i < round(dx) + 1; i++)
        {

            for (int _x = x; _x < xMax && y != prev_y; _x++)
            {
                if (!isBGPixel(QPoint(_x, y)))
                {
                    remPixel(QPoint(_x, y));
                    painter.setPen(backGroundColor());
                    painter.drawPoint(_x, y);
                }
                else
                {
                    addPixel(QPoint(_x, y));
                    painter.setPen(paintColor());
                    painter.drawPoint(_x, y);
                }
            }

            prev_y = y;

            if (2 * error > dx)
            {
                if (!swap_flag)
                {
                    y += sy;
                }
                else
                {
                    x += sx;
                }

                error -= dx;
            }

            if (!swap_flag)
            {
                x += sx;
            }
            else
            {
                y += sy;
            }

            error = error + m;
        }
    }
}
