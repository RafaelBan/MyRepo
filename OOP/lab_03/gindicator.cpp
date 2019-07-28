#include "gindicator.h"

GIndicator::GIndicator(QWidget *parent) :
    QWidget (parent),

    state(State::NONE),

    background ("white"),
    foreground ("black")
{
}

void GIndicator::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);

    QPainter painter(this);

    QPoint up[3] = {{0, height()}, {width(), height()}, {width() / 2, 0}};
    QPoint down[3] = {{0, 0}, {width(), 0}, {width() / 2, height()}};

    painter.fillRect(0, 0, width(), height(), background);

    painter.setPen(foreground);
    painter.setBrush(QBrush(foreground, Qt::SolidPattern));
    if (state == State::UP)
    {
        painter.drawPolygon(up, 3);
    }
    else if (state == State::DOWN)
    {
        painter.drawPolygon(down, 3);
    }
}

void GIndicator::setForeground(QColor color)
{
    foreground = color;
}

QColor GIndicator::getForeground()
{
    return foreground;
}

void GIndicator::setBackground(QColor color)
{
    background = color;
}

QColor GIndicator::getBackground()
{
    return background;
}

void GIndicator::setDirection(int dir)
{
    if (dir == 0)
    {
        state = State::NONE;
    }
    else if (dir > 0)
    {
        state = State::UP;
    }
    else if (dir < 0)
    {
        state = State::DOWN;
    }

    update();
}
