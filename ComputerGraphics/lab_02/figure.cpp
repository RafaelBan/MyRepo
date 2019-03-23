#include "figure.h"
#include <QDebug>

Figure::Figure(QList<point_t> points)
{
    this->points = points;
}

QList<point_t> Figure::Points()
{
    return this->points;
}

QList<Figure> Figure::initPicture(double k)
{
    Figure arc1;
    Figure arc2;
    Figure arc3;
    Figure square;
    Figure trianlge;
    QList<Figure> picture;

    QList<point_t> arc1Base;
    QList<point_t> arc2Base;
    QList<point_t> arc3Base;

    double edge = 10;
    double height = edge * tan(degToRad(60));
    double step = 1 / (k * edge);

    point_t c1Center(-(edge), +(1 / 4.0 * height));
    point_t c2Center(+(edge), +(1 / 4.0 * height));
    point_t c3Center(0, -(3 / 4.0 * height));

    point_t tNode1((c2Center.x + c3Center.x) / 2, (c2Center.y + c3Center.y) / 2);
    point_t tNode2((c1Center.x + c3Center.x) / 2, (c1Center.y + c3Center.y) / 2);
    point_t tNode3((c2Center.x + c1Center.x) / 2, (c2Center.y + c1Center.y) / 2);

    double t1s = +acos((c1Center.x - tNode2.x) / edge);
    double t2s = -acos((c2Center.x - tNode3.x) / edge);
    double t3s = -acos((c3Center.x - tNode1.x) / edge);

    double t1f = +acos((c1Center.x - tNode3.x) / edge);
    double t2f = +acos((c2Center.x - tNode1.x) / edge);
    double t3f = -acos((c3Center.x - tNode2.x) / edge);

    while (t1s < t1f)
    {
        double x1 = c1Center.x - edge * cos(t1s);
        double y1 = c1Center.y - edge * sin(t1s);

        arc1Base.append(point_t(x1, y1));

        t1s += step;
    }
    {
        double x1 = c1Center.x - edge * cos(t1f);
        double y1 = c1Center.y - edge * sin(t1f);

        arc1Base.append(point_t(x1, y1));
    }

    while (t2s < t2f)
    {
        double x2 = c2Center.x - edge * cos(t2s);
        double y2 = c2Center.y - edge * sin(t2s);

        arc2Base.append(point_t(x2, y2));

        t2s += step;
    }
    {
        double x2 = c2Center.x - edge * cos(t2f);
        double y2 = c2Center.y - edge * sin(t2f);

        arc2Base.append(point_t(x2, y2));
    }

    while (t3s < t3f)
    {
        double x3 = c3Center.x - edge * cos(t3s);
        double y3 = c3Center.y - edge * sin(t3s);

        arc3Base.append(point_t(x3, y3));

        t3s += step;
    }
    {
        double x3 = c3Center.x - edge * cos(t3f);
        double y3 = c3Center.y - edge * sin(t3f);

        arc3Base.append(point_t(x3, y3));
    }

    square = Figure({tNode1, tNode2,
                     point_t(+tNode2.x, -tNode2.y),
                     point_t(+tNode1.x, -tNode1.y)});
    trianlge = Figure({tNode1, tNode2, tNode3});
    arc1 = Figure(arc1Base);
    arc2 = Figure(arc2Base);
    arc3 = Figure(arc3Base);

    picture.append(arc1);
    picture.append(arc2);
    picture.append(arc3);
    picture.append(square);
    picture.append(trianlge);

    return picture;
}
