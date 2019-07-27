#ifndef DRAWLINE_H
#define DRAWLINE_H

#include <QPainter>
#include <QMap>

namespace drawAlgo
{
    void
    draw_line_bresenham_i(double x1, double y1, double x2, double y2,
                          QMap< QPair<int, int>, QColor > &borderPixels, QColor color);
}

#endif // DRAWLINE_H
