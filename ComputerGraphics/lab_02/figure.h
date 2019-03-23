#ifndef FIGURE_H
#define FIGURE_H

#include "geometry.h"

#include <QList>
#include <QPainter>

#include <cmath>

class Figure
{
private:
    QList<point_t> points;

public:
    Figure(QList<point_t> points = {});

    QList<point_t> Points();

    static QList<Figure> initPicture(double k = 1);
};

static inline double degToRad(double degrees)
{
    return (M_PI / 180) * degrees;
}

static inline double radToDeg(double radians)
{
    return (180 / M_PI) * radians;
}

#endif // FIGURE_H
