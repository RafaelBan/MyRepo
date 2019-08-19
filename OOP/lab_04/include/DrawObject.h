#ifndef DRAW_OBJECT_H_
#define DRAW_OBJECT_H_

#include <QPainter>
#include <QColor>

class DrawObject
{
public:
    virtual ~DrawObject() = default;

    virtual void draw(QPainter &painter) = 0;

protected:
    QColor color;
};

#endif // DRAW_OBJECT_H_

