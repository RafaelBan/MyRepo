#include "canvas.h"

Canvas::Canvas(QWidget *parent) :
    QWidget (parent),

    _backGroundColor(MyColors::white),
    _foreGroundColor(MyColors::black)
{

}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.fillRect(0, 0, width(), height(), backGroundColor());

    for (auto task: this->tasksCircle)
    {
        painter.setPen(task.color);

        switch (task.idx)
        {
        case standard:
            painter.drawEllipse(int(round(task.x0)) - int(round(task.R)),
                                int(round(task.y0)) - int(round(task.R)),
                                int(round(task.R)) * 2,
                                int(round(task.R)) * 2);
            break;

        case canonical:
            drawAlgo::draw_circle_canonical(task.x0, task.y0, task.R, painter);
            break;

        case parametric:
            drawAlgo::draw_circle_parametric(task.x0, task.y0, task.R, painter);
            break;

        case bresenham:
            drawAlgo::draw_circle_bresenham(task.x0, task.y0, task.R, painter);
            break;

        case midpoint:
            drawAlgo::draw_circle_midpoint(task.x0, task.y0, task.R, painter);
            break;

        default:
            break;
        }
    }

    for (auto task: this->tasksEllipse)
    {
        painter.setPen(task.color);

        switch (task.idx)
        {
        case standard:
            painter.drawEllipse(int(round(task.x0)) - int(round(task.a)),
                                int(round(task.y0)) - int(round(task.b)),
                                int(round(task.a)) * 2,
                                int(round(task.b)) * 2);
            break;

        case canonical:
            drawAlgo::draw_ellipse_canonical(task.x0, task.y0, task.a, task.b, painter);
            break;

        case parametric:
            drawAlgo::draw_ellipse_parametric(task.x0, task.y0, task.a, task.b, painter);
            break;

        case bresenham:
            drawAlgo::draw_ellipse_bresenham(task.x0, task.y0, task.a, task.b, painter);
            break;

        case midpoint:
            drawAlgo::draw_ellipse_midpoint(task.x0, task.y0, task.a, task.b, painter);
            break;

        default:
            break;
        }
    }
}

QColor Canvas::backGroundColor()
{
    return _backGroundColor;
}

QColor Canvas::foreGroundColor()
{
    return _foreGroundColor;
}

void Canvas::setBackGroundColor(QColor color)
{
    _backGroundColor = color;
}

void Canvas::setForeGroundColor(QColor color)
{
    _foreGroundColor = color;
}

void Canvas::drawCircle(double x0, double y0, double R, AlgoIdx idx)
{
    this->tasksCircle.append({ idx, x0, y0, R, this->foreGroundColor() });
}

void Canvas::drawEllipse(double x0, double y0, double a, double b, AlgoIdx idx)
{
    this->tasksEllipse.append({ idx, x0, y0, a, b, this->foreGroundColor() });
}

void Canvas::clear()
{
    this->tasksCircle.clear();
    this->tasksEllipse.clear();
}
