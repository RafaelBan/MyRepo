#ifndef CANVAS_LINE_H_
#define CANVAS_LINE_H_

#include "DrawObject.h"
#include "QPoint"

class CanvasLine : public DrawObject
{
public:
    ~CanvasLine() = default;

    CanvasLine(QPoint p1, QPoint p2, QColor color = "#000000");

    void draw(QPainter &painter) override;

private:
    QPoint p1;
    QPoint p2;
};

#endif // CANVAS_LINE_H_

