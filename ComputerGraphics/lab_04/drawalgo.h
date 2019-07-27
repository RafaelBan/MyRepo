#ifndef DRAWALGO_H
#define DRAWALGO_H

#include "geometry.h"
#include "QPainter"

namespace drawAlgo
{
    static const char *names[] = {
        "Каноническое уравнение",
        "Параметрическое уравнение",
        "Метод Брезенхема",
        "Метод средней точки",
        "Библиотечный метод"
    };

    void draw_circle_canonical(double x0, double y0, double R, QPainter &painter);
    void draw_circle_parametric(double x0, double y0, double R, QPainter &painter);
    void draw_circle_bresenham(double x0, double y0, double R, QPainter &painter);
    void draw_circle_midpoint(double x0, double y0, double R, QPainter &painter);

    void draw_ellipse_canonical(double x0, double y0, double a, double b, QPainter &painter);
    void draw_ellipse_parametric(double x0, double y0, double a, double b, QPainter &painter);
    void draw_ellipse_bresenham(double x0, double y0, double a, double b, QPainter &painter);
    void draw_ellipse_midpoint(double x0, double y0, double a, double b, QPainter &painter);
}

#endif // DRAWALGO_H
