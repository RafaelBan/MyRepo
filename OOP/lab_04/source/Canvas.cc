#include "Canvas.h"
#include <memory>

#include <QDebug>

Canvas::Canvas(QWidget *parent) :
    QWidget(parent),

    bgColor("#ffffff")
{
    bufferManager = new BufferManager(this, &buffer, bgColor);
}

void Canvas::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    updateBufferSize();
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    auto painter = std::make_unique<QPainter>(this);

    painter->drawPixmap(0, 0, buffer);
}

void Canvas::updateBufferSize()
{
    bufferManager->updateBufferSize();
    update();
}

void Canvas::drawLine(QPoint p1, QPoint p2)
{
    auto painter = std::make_unique<QPainter>(&buffer);

    painter->setPen(QColor("#000000"));
    painter->drawLine(p1, p2);

    update();
}

