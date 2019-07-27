#include "drawalgo.h"

void drawAlgo::draw_circle_canonical(double x0, double y0, double R, QPainter &painter)
{
    int R_ = int(round(R));
    int x0_ = int(round(x0));
    int y0_ = int(round(y0));

    int x_max = int(round(R / sqrt(2.0)));

    for (int x = 0; x <= x_max; x++)
    {
        int y = int(round(sqrt(R_ * R_ - x * x)));

        painter.drawPoint(x0_ + x, y0_ + y);
        painter.drawPoint(x0_ + x, y0_ - y);
        painter.drawPoint(x0_ - x, y0_ + y);
        painter.drawPoint(x0_ - x, y0_ - y);

        painter.drawPoint(x0_ + y, y0_ + x);
        painter.drawPoint(x0_ - y, y0_ + x);
        painter.drawPoint(x0_ + y, y0_ - x);
        painter.drawPoint(x0_ - y, y0_ - x);
    }
}

void drawAlgo::draw_circle_parametric(double x0, double y0, double R, QPainter &painter)
{
    double x;
    double y = R;
    double t = 0;
    double h = 1 / R;

//    while(t < M_PI_2)
    while(y > 0)
    {
        x = R * sin(t);
        y = R * cos(t);

        painter.drawPoint(int(round(x0 + x)), int(round(y0 + y)));
        painter.drawPoint(int(round(x0 + x)), int(round(y0 - y)));
        painter.drawPoint(int(round(x0 - x)), int(round(y0 + y)));
        painter.drawPoint(int(round(x0 - x)), int(round(y0 - y)));

        t += h;
    }
}

void drawAlgo::draw_circle_bresenham(double x0, double y0, double R, QPainter &painter)
{
    int x = 0;
    int y = int(round(R));
    int d = 2 - 2 * int(round(R));
    int x0_ = int(round(x0));
    int y0_ = int(round(y0));

    while (y >= 0)
    {
        painter.drawPoint(x0_ + x, y0_ + y);
        painter.drawPoint(x0_ + x, y0_ - y);
        painter.drawPoint(x0_ - x, y0_ + y);
        painter.drawPoint(x0_ - x, y0_ - y);

        if (d < 0)
        {
            int d_ = 2 * d + 2 * y - 1;
            x += 1;

            if (d_ <= 0)
            {
                d = d + 2 * x + 1;
            }
            else
            {
                y -= 1;
                d = d + 2 * x - 2 * y + 2;
            }
        }

        else if (d > 0)
        {
            int d_ = 2 * d - 2 * x - 1;
            y -= 1;

            if (d_ > 0)
            {
                d = d - 2 * y + 1;
            }
            else
            {
                x += 1;
                d = d + 2 * x - 2 * y + 2;
            }
        }

       else // if (d == 0)
       {
            x += 1;
            y -= 1;
            d = d + 2 * x - 2 * y + 2;
       }
    }
}

void drawAlgo::draw_circle_midpoint(double x0, double y0, double R, QPainter &painter)
{
    int x = 0;
    int y = int(round(R));
    double p = 1.25 - round(R);

    int x0_ = int(round(x0));
    int y0_ = int(round(y0));

    while (x <= y)
    {
        painter.drawPoint(x0_ + x, y0_ + y);
        painter.drawPoint(x0_ - x, y0_ + y);
        painter.drawPoint(x0_ + x, y0_ - y);
        painter.drawPoint(x0_ - x, y0_ - y);

        painter.drawPoint(x0_ + y, y0_ + x);
        painter.drawPoint(x0_ - y, y0_ + x);
        painter.drawPoint(x0_ + y, y0_ - x);
        painter.drawPoint(x0_ - y, y0_ - x);

        x += 1;

        if (p > 0)
        {
            y -= 1;
            p -= y + y;
        }

        p += x + x + 1;
    }
}

void drawAlgo::draw_ellipse_canonical(double x0, double y0, double a, double b, QPainter &painter)
{
    int a_ = int(round(a));
    int b_ = int(round(b));
    int x0_ = int(round(x0));
    int y0_ = int(round(y0));

    int x_max = int(round(a*a / sqrt(a*a + b*b)));
    int y_max = int(round(b*b / sqrt(a*a + b*b)));

    for (int x = 0; x <= x_max; x++)
    {
        int y = int(round(sqrt(b_ * b_ * (1 - x * double(x) / (a_ * a_)))));

        painter.drawPoint(x0_ + x, y0_ + y);
        painter.drawPoint(x0_ + x, y0_ - y);
        painter.drawPoint(x0_ - x, y0_ + y);
        painter.drawPoint(x0_ - x, y0_ - y);
    }

    for (int y = y_max; y >= 0; y--)
    {
        int x = int(round(sqrt(a_ * a_ * (1 - y * double(y) / (b_ * b_)))));

        painter.drawPoint(x0_ + x, y0_ + y);
        painter.drawPoint(x0_ + x, y0_ - y);
        painter.drawPoint(x0_ - x, y0_ + y);
        painter.drawPoint(x0_ - x, y0_ - y);
    }
}

void drawAlgo::draw_ellipse_parametric(double x0, double y0, double a, double b, QPainter &painter)
{
    double x;
    double y = b;
    double t = 0;
    double h = 1.0 / a;

    int x0_ = int(round(x0));
    int y0_ = int(round(y0));

    int y_min = int(round(b*b / sqrt(a*a + b*b)));

//    while(t <= M_PI_4)
    while (y >= y_min)
    {
        x = a * sin(t);
        y = b * cos(t);

        int _x = int(round(x));
        int _y = int(round(y));

        painter.drawPoint(x0_ + _x, y0_ + _y);
        painter.drawPoint(x0_ + _x, y0_ - _y);
        painter.drawPoint(x0_ - _x, y0_ + _y);
        painter.drawPoint(x0_ - _x, y0_ - _y);

        t += h;
    }

    h = 1.0 / b;

//    while(t <= M_PI_2)
    while (y >= 0)
    {
        x = a * sin(t);
        y = b * cos(t);

        int _x = int(round(x));
        int _y = int(round(y));

        painter.drawPoint(x0_ + _x, y0_ + _y);
        painter.drawPoint(x0_ + _x, y0_ - _y);
        painter.drawPoint(x0_ - _x, y0_ + _y);
        painter.drawPoint(x0_ - _x, y0_ - _y);

        t += h;
    }
}

void drawAlgo::draw_ellipse_bresenham(double x0, double y0, double a, double b, QPainter &painter)
{
    int a_ = int(round(a));
    int b_ = int(round(b));
    int x0_ = int(round(x0));
    int y0_ = int(round(y0));

    int x = 0;
    int y = b_;
    int d;

    int aa = a_ * a_;
    int bb = b_ * b_;

    d = aa + bb - 2 * aa * y;

    while (y >= 0)
    {
        painter.drawPoint(x0_ + x, y0_ + y);
        painter.drawPoint(x0_ + x, y0_ - y);
        painter.drawPoint(x0_ - x, y0_ + y);
        painter.drawPoint(x0_ - x, y0_ - y);

        if (d < 0)
        {
            int d_ = 2 * d + 2 * aa * y - aa;
            x += 1;

            if (d_ < 0)
            {
                d += 2 * bb * x + bb;
            }
            else
            {
                y -= 1;
                d += 2 * x * bb - 2 * y * aa + aa + bb;
            }
        }
        else if (d > 0)
        {
            int d_ = 2 * d - 2 * bb * x - bb;
            y -=1;

            if (d_ > 0)
            {
                d += -2 * y * aa + aa;
            }
            else
            {
                x += 1;
                d += 2 * x * bb - 2 * y * aa + aa + bb;
            }

            continue;
        }
        else // if (d == 0)
        {
            x += 1;
            y -= 1;
            d += 2 * x * bb - 2 * y * aa + aa + bb;
        }
    }
}

void drawAlgo::draw_ellipse_midpoint(double x0, double y0, double a, double b, QPainter &painter)
{
    int a_ = int(round(a));
    int b_ = int(round(b));
    int x0_ = int(round(x0));
    int y0_ = int(round(y0));

    int x = 0;
    int y = b_;

    int aa = a_ * a_;
    int bb = b_ * b_;

    int aa2 = 2 * aa;
    int bb2 = 2 * bb;

    int x_max = int(round(aa / sqrt(aa + bb)));

    int df_pr = 0;
    int delta_f_pr = -aa2 * y;

    double f = bb - aa * y + aa * 0.25;

    while (x < x_max)
    {
        painter.drawPoint(x0_ + x, y0_ + y);
        painter.drawPoint(x0_ + x, y0_ - y);
        painter.drawPoint(x0_ - x, y0_ + y);
        painter.drawPoint(x0_ - x, y0_ - y);

        x += 1;

        if (f > 0)
        {
            y -= 1;
            delta_f_pr += aa2;

            f += delta_f_pr;
        }

        df_pr += bb2;

        f += df_pr + bb;
    }

    delta_f_pr = bb2 * x;
    f += 0.75 * (aa - bb) - aa * y - bb * x;
    df_pr = -aa2 * y;

    while (y >= 0)
    {
        painter.drawPoint(x0_ + x, y0_ + y);
        painter.drawPoint(x0_ + x, y0_ - y);
        painter.drawPoint(x0_ - x, y0_ + y);
        painter.drawPoint(x0_ - x, y0_ - y);

        y -= 1;

        if (f < 0)
        {
            x += 1;
            delta_f_pr += bb2;

            f += delta_f_pr;
        }

        df_pr += aa2;

        f += df_pr + aa;
    }
}
