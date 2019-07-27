#include "drawline.h"
#include <cmath>

using namespace std;

void
drawAlgo::draw_line_bresenham_i(double x1, double y1, double x2, double y2,
                                QMap< QPair<int, int>, QColor > &borderPixels, QColor color)
{
    QPoint p1 = { int(round(x1)), int(round(y1)) };
    QPoint p2 = { int(round(x2)), int(round(y2)) };

    if (p1.y() < p2.y())
    {
        std::swap(p1, p2);
    }

    if (p1 == p2)
    {
        borderPixels.insert({p1.x(), p2.y()}, color);
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
        borderPixels.insert({x, y}, color);

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
