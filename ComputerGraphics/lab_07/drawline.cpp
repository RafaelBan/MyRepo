#include "drawline.h"
#include <cmath>

using namespace std;

void
drawAlgo::draw_line_bresenham_i(QPoint p1, QPoint p2, QPainter &painter)
{
    painter.drawLine(p1, p2);
    return;

    if (p1.y() < p2.y())
    {
        std::swap(p1, p2);
    }

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
