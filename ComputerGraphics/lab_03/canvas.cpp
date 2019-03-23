#include "canvas.h"
#include <QDebug>

Canvas::Canvas(QWidget *parent) :
    QWidget (parent),

    bgColor(MyColors::gBackground),
    lineColor(MyColors::black)
{

}

Canvas::~Canvas()
{

}

QColor Canvas::getBGColor(void)
{
    return bgColor;
}

void Canvas::setBGColor(QColor color)
{
    bgColor = color;
}

QColor Canvas::getLineColor(void)
{
    return lineColor;
}

void Canvas::setLineColor(QColor color)
{
    lineColor = color;
}

void Canvas::draw()
{
    QPainter painter(this);

    painter.fillRect(0, 0, this->width(), this->height(), this->bgColor);

    foreach (cartesian::straight::drawTask task, this->tasks)
    {
        task.draw(painter,this);
    }
}

void Canvas::paintEvent(QPaintEvent *)
{
    draw();
}

QPoint Canvas::initQPoint(int cart_x, int cart_y)
{
    int width = this->width();
    int height = this->height();

    return QPoint(+cart_x + width / 2, -cart_y + height / 2);
}

void Canvas::addTask(cartesian::straight::drawTask task)
{
    this->tasks.append(task);
}

void Canvas::clearTasks()
{
    this->tasks.clear();
}

bool cartesian::straight::doFullSmooth = false;

cartesian::straight::drawTask::drawTask(int x1, int y1, int x2, int y2,
                                        QColor color,
                                        QString method) :
    x1(x1), y1(y1),
    x2(x2), y2(y2),
    color(color)
{
    if (method == "DDA")
    {
        this->drawLine = cartesian::straight::dda;
    }
    else if (method == "bresenhamr")
    {
        this->drawLine = cartesian::straight::bresenhamr;
    }
    else if (method == "bresenhami")
    {
        this->drawLine = cartesian::straight::bresenhami;
    }
    else if (method == "bresenhama")
    {
        this->drawLine = cartesian::straight::bresenhama;
    }
    else if (method == "WU")
    {
        this->drawLine = cartesian::straight::wu;
    }
    else if (method == "standard")
    {
        this->drawLine = cartesian::straight::standard;
    }
    else
    {
        this->drawLine = cartesian::straight::standard;
    }
}

void cartesian::straight::drawTask::draw(QPainter &painter, Canvas *canvas)
{
    QPen temp = painter.pen();
    QPoint p1(this->x1, this->y1);
    QPoint p2(this->x2, this->y2);

    if (canvas != nullptr)
    {
        p1 = canvas->initQPoint(this->x1, this->y1);
        p2 = canvas->initQPoint(this->x2, this->y2);
    }

    painter.setPen(this->color);
    this->drawLine(p1, p2, painter);

    painter.setPen(temp);
}

void cartesian::straight::standard(QPoint p1, QPoint p2, QPainter &painter)
{
    painter.drawLine(p1, p2);
}

void cartesian::straight::dda(QPoint p1, QPoint p2, QPainter &painter)
{
    if (p1 == p2)
    {
        painter.drawPoint(p1);
        return;
    }

    double l = std::max(abs(p2.x() - p1.x()), abs(p2.y() - p1.y()));

    double dx = (p2.x() - p1.x()) / l;
    double dy = (p2.y() - p1.y()) / l;

    double x = p1.x();
    double y = p1.y();

//    while (!isEqual(x, p2.x()) || !isEqual(y, p2.y()))
    for (int i = 0; i < l + 1; i++)
    {
        painter.drawPoint(int(round(x)), int(round(y)));

        x += dx;
        y += dy;
    }
}

void cartesian::straight::bresenhamr(QPoint p1, QPoint p2, QPainter &painter)
{
    if (p1 == p2)
    {
        painter.drawPoint(p1);
        return;
    }

    bool swap_flag = false;

    double dx = p2.x() - p1.x();
    double dy = p2.y() - p1.y();

    int sx = (dx > 0) ? 1 : -1;
    int sy = (dy > 0) ? 1 : -1;

    dx = abs(dx);
    dy = abs(dy);

    if (dx < dy)
    {
         std::swap(dx, dy);
         swap_flag = true;
    }

    double m = dy / dx;
    double error = m - 0.5;

    double x = p1.x();
    double y = p1.y();

//    while (!isEqual(x, p2.x()) || !isEqual(y, p2.y()))
    for (int i = 0; i < round(dx) + 1; i++)
    {
        painter.drawPoint(int(round(x)), int(round(y)));

        if (error > 0)
        {
            if (!swap_flag)
            {
                y += sy;
            }
            else
            {
                x += sx;
            }

            error -= 1;
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

void cartesian::straight::bresenhami(QPoint p1, QPoint p2, QPainter &painter)
{
    if (p1 == p2)
    {
        painter.drawPoint(p1);
        return;
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

//    while (x != p2.x() || y != p2.y())
    for (int i = 0; i < round(dx) + 1; i++)
    {
        painter.drawPoint(x, y);

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

void cartesian::straight::bresenhama(QPoint p1, QPoint p2, QPainter &painter)
{
    QPen safer = painter.pen();
    QColor color = painter.pen().color();
    color.setAlphaF(1);

    if (p1 == p2)
    {
        painter.drawPoint(p1);

        painter.setPen(safer);
        return;
    }

    if (p1.x() == p2.x())
    {
        color.setAlphaF(.75);
        painter.setPen(color);

        for (int cur_y = std::min(p1.y(), p2.y()), fin_y = std::max(p1.y(), p2.y()), x = p1.x();
             cur_y <= fin_y; cur_y++)
        {
            painter.drawPoint(x, cur_y);
        }

        painter.setPen(safer);
        return;
    }

    if (p1.y() == p2.y())
    {
        color.setAlphaF(.75);
        painter.setPen(color);

        for (int cur_x = std::min(p1.x(), p2.x()), fin_x = std::max(p1.x(), p2.x()), y = p1.y();
             cur_x <= fin_x; cur_x++)
        {
            painter.drawPoint(cur_x, y);
        }

        painter.setPen(safer);
        return;
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

    int m = 2 * dy;
    int error = ILevels * dx;

    int x = p1.x();
    int y = p1.y();

    m = ILevels * m;
    int W = ILevels * dx * 2 - m;

    color.setAlpha(error / (2 * dx));
    painter.setPen(color);
    painter.drawPoint(x, y);

    for (int i = 0; i < round(dx) + 1; i++)
    {
        if (error < W)
        {
            if (!swap_flag)
            {
                x += sx;
            }
            else
            {
                y += sy;
            }

            error += m;
        }
        else if (error >= W)
        {
            x += sx;
            y += sy;

            error -= W;
        }

        color.setAlpha(error / (2 * dx));
        painter.setPen(color);
        painter.drawPoint(x, y);

        if (cartesian::straight::doFullSmooth)
        {
            color.setAlpha(ILevels - error / (2 * dx));
            painter.setPen(color);
            painter.drawPoint(x - sx * swap_flag, y - sy * !swap_flag);
        }
    }

    painter.setPen(safer);
}

void cartesian::straight::wu(QPoint p1, QPoint p2, QPainter &painter)
{
    QPen safer = painter.pen();
    QColor color = painter.pen().color();
    color.setAlphaF(1);

    if (p1 == p2)
    {
        painter.drawPoint(p1);

        painter.setPen(safer);
        return;
    }

    if (p1.x() == p2.x())
    {
        color.setAlphaF(.75);
        painter.setPen(color);

        for (int cur_y = std::min(p1.y(), p2.y()), fin_y = std::max(p1.y(), p2.y()), x = p1.x();
             cur_y <= fin_y; cur_y++)
        {
            painter.drawPoint(x, cur_y);
        }

        painter.setPen(safer);
        return;
    }

    if (p1.y() == p2.y())
    {
        color.setAlphaF(.75);
        painter.setPen(color);

        for (int cur_x = std::min(p1.x(), p2.x()), fin_x = std::max(p1.x(), p2.x()), y = p1.y();
             cur_x <= fin_x; cur_x++)
        {
            painter.drawPoint(cur_x, y);
        }

        painter.setPen(safer);
        return;
    }

    bool swap_flag = false;

    double dx = p2.x() - p1.x();
    double dy = p2.y() - p1.y();

    int sx = (dx > 0) ? 1 : -1;
    int sy = (dy > 0) ? 1 : -1;

    dx = abs(dx);
    dy = abs(dy);

    if (dx < dy)
    {
        swap_flag = true;
        std::swap(dx, dy);
    }

    double m = dy / dx;

    color.setAlphaF(0.5);
    painter.setPen(color);

    painter.drawPoint(p1.x(), p1.y());
    if (cartesian::straight::doFullSmooth)
        painter.drawPoint(p1.x() + 1 * swap_flag, p1.y() + 1 * !swap_flag);

    painter.drawPoint(p2.x(), p2.y());
    if (cartesian::straight::doFullSmooth)
        painter.drawPoint(p2.x() + 1 * swap_flag, p2.y() + 1 * !swap_flag);

    double x = p1.x();
    double y = p1.y();

    for (int i = 0; i < dx + 1; i++)
    {
        double fpart = 0;

        if (!swap_flag)
        {
            fpart = abs(y - int(y));
        }
        else
        {
            fpart = abs(x - int(x));
        }

        color.setAlphaF(1 - fpart);
        painter.setPen(color);
        painter.drawPoint(int(x), int(y));

        color.setAlphaF(fpart);
        painter.setPen(color);
        if (cartesian::straight::doFullSmooth)
            painter.drawPoint(int(x) + 1 * swap_flag, int(y) + 1 * !swap_flag);

        if (!swap_flag)
        {
            x += sx;
            y += m * sy;
        }
        else
        {
            x += m * sx;
            y += sy;
        }
    }

    painter.setPen(safer);
}

//void cartesian::straight::wu(QPoint p1, QPoint p2, QPainter &painter)
//{
//    QPen safer = painter.pen();
//    QColor color = painter.pen().color();
//    color.setAlphaF(1);

//    if (p1 == p2)
//    {
//        painter.drawPoint(p1);

//        painter.setPen(safer);
//        return;
//    }

//    if (p1.x() == p2.x())
//    {
////        return;
//        color.setAlphaF(.5);
//        painter.setPen(color);

//        for (int cur_y = std::min(p1.y(), p2.y()), fin_y = std::max(p1.y(), p2.y()), x = p1.x();
//             cur_y <= fin_y; cur_y++)
//        {
//            painter.drawPoint(x, cur_y);
//            painter.drawPoint(x - 1, cur_y);
//        }

//        painter.setPen(safer);
//        return;
//    }

//    if (p1.y() == p2.y())
//    {
////        return;
//        color.setAlphaF(.5);
//        painter.setPen(color);

//        for (int cur_x = std::min(p1.x(), p2.x()), fin_x = std::max(p1.x(), p2.x()), y = p1.y();
//             cur_x <= fin_x; cur_x++)
//        {
//            painter.drawPoint(cur_x, y);
//            painter.drawPoint(cur_x, y - 1);
//        }

//        painter.setPen(safer);
//        return;
//    }

//    painter.drawPoint(p1);
////    painter.drawPoint(p2);

//    int swap_flag = false;

//    double dx = p2.x() - p1.x();
//    double dy = p2.y() - p1.y();

//    int sx = (dx > 0) ? 1 : -1;
//    int sy = (dy > 0) ? 1 : -1;

//    dx = abs(dx);
//    dy = abs(dy);

//    if (dx < dy)
//    {
//        std::swap(dx, dy);
//        swap_flag = true;
//    }

//    double m = dy / dx;

//    double x = p1.x();
//    double y = p1.y();

//    if (!swap_flag)
//    {
//        m *= sy;
//        x += sx;
//        y += m;
//    }
//    else
//    {
//        m *= sx;
//        x += m;
//        y += sy;
//    }

//    for (int i = 0; i < round(dx) + 1; i++)
//    {
//        double I = 0;
//        double cur_x = x, sup_x = x;
//        double cur_y = y, sup_y = y;

//        if (!swap_flag)
//        {
//            I =  (abs(y) - int(abs(y)));
//            if (sy < 0)
//            {
//                I = 1 - I;
//            }

//            sup_y += sy;

//            x += sx;
//            y += m;
//        }
//        else
//        {
//            I = abs(x) - int(abs(x));
//            if (sx < 0)
//            {
//                I = 1 - I;
//            }

//            sup_x += sx;

//            x += m;
//            y += sy;
//        }

//        color.setAlphaF(1 - I);
//        painter.setPen(color);
//        painter.drawPoint(int(cur_x), int(cur_y));

//        color.setAlphaF(I);
//        painter.setPen(color);
//        painter.drawPoint(int(sup_x), int(sup_y));
//    }

//    painter.setPen(safer);
//}

//void cartesian::straight::wu(QPoint p1, QPoint p2, QPainter &painter)
//{
//    QPen safer = painter.pen();
//    QColor color = painter.pen().color();
//    color.setAlphaF(1);

//        if (p1.x() == p2.x())
//        {
//            for (int cur_y = std::min(p1.y(), p2.y()), fin_y = std::max(p1.y(), p2.y()), x = p1.x();
//                 cur_y <= fin_y; cur_y++)
//            {
//                painter.drawPoint(x, cur_y);
//            }

//            painter.setPen(safer);
//            return;
//        }

//        if (p1.y() == p2.y())
//        {
//            for (int cur_x = std::min(p1.x(), p2.x()), fin_x = std::max(p1.x(), p2.x()), y = p1.y();
//                 cur_x <= fin_x; cur_x++)
//            {
//                painter.drawPoint(cur_x, y);
//            }

//            painter.setPen(safer);
//            return;
//        }

//    if (p1 == p2)
//    {
//        painter.drawPoint(p1);

//        painter.setPen(safer);
//        return;
//    }

//    int swap_flag = false;

//    int dx = p2.x() - p1.x();
//    int dy = p2.y() - p1.y();

//    int sx = (dx > 0) ? 1 : -1;
//    int sy = (dy > 0) ? 1 : -1;

//    dx = abs(dx);
//    dy = abs(dy);

//    if (dx < dy)
//    {
//         std::swap(dx, dy);
//         swap_flag = true;
//    }

//    int m = 2 * dy;
//    int error = ILevels * dx;

//    int x = p1.x();
//    int y = p1.y();

//    m = ILevels * m;
//    int W = ILevels * dx * 2 - m;

//    color.setAlpha(error / (2 * dx));
//    painter.setPen(color);
//    painter.drawPoint(x, y);

//    while (x != p2.x() || y != p2.y())
//    {
//        if (error < W)
//        {
//            if (!swap_flag)
//            {
//                x += sx;
//            }
//            else
//            {
//                y += sy;
//            }

//            error += m;
//        }
//        else if (error >= W)
//        {
//            x += sx;
//            y += sy;

//            error -= W;
//        }

//        color.setAlpha(error / (2 * dx));
//        painter.setPen(color);
//        painter.drawPoint(x, y);

//        color.setAlpha((ILevels - error / (2 * dx)));
//        painter.setPen(color);
//        painter.drawPoint(x - sx * swap_flag, y - sy * !swap_flag);
//    }

//    painter.setPen(safer);
//}
