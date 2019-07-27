#ifndef DRAWLINE_H
#define DRAWLINE_H

#include <QPainter>

namespace drawAlgo
{
    void
    draw_line_bresenham_i(double x1, double y1, double x2, double y2, QPainter &painter);
}

#endif // DRAWLINE_H
