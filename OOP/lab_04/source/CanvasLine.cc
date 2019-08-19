#include "CanvasLine.h"

CanvasLine::CanvasLine(QPoint p1, QPoint p2, QColor color) :
    p1(p1),
    p2(p2)
{
    this->color = color;
}

void CanvasLine::draw(QPainter &painter)
{
    QPen save = painter.pen();

    painter.setPen(color);
    painter.drawLine(p1, p2);

    painter.setPen(save);
}

