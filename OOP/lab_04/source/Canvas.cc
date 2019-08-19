#include "Canvas.h"
#include <memory>

Canvas::Canvas(QWidget *parent) :
    QWidget(parent),

    bgColor("#ffffff")
{
}

void Canvas::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    auto painter = std::make_unique<QPainter>(this);

    painter->fillRect(0, 0, width(), height(), bgColor);

    for (auto drawObject: drawObjects)
    {
        drawObject->draw(*painter);
    }
}

void Canvas::setBackgroundColor(QColor color)
{
    bgColor = color;
}

void Canvas::drawLine(QPoint p1, QPoint p2, QColor color)
{
    drawObjects.append( std::make_shared<CanvasLine>(p1, p2, color) );

    update();
}

