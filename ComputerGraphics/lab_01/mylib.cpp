#include "mylib.h"

#include <cmath>

bool isDouble(QString str)
{
    bool result;

    (void)str.toDouble(&result);

    return result;
}

QList<triangle_t> makeTriangels(QList<point_t> points, bool *isOK)
{
    if (isOK != nullptr)
        *isOK = false;

    int len;
    QList<triangle_t> triangels;

    len = points.count();

    if (len < 3)
    {
        return triangels;
    }

    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            for (int k = j + 1; k < len; k++)
            {
                point_t &A = points[i];
                point_t &B = points[j];
                point_t &C = points[k];

                if (!isOnSingleStraight(A, B, C))
                {
                    triangels.append(triangle_t(A, B, C));
                }
            }
        }
    }

    if (isOK != nullptr)
        *isOK = true;

    return triangels;
}

triangle_t findTriangle(QList<triangle_t> triangles)
{
    triangle_t maxdTriangle = triangles[0];

    for (int i = 1, len = triangles.count(); i < len; i++)
    {
        double orthDistCatched = fabs(maxdTriangle.orthocenter().x) + fabs(maxdTriangle.orthocenter().y);
        double orthDistCurrent = fabs(triangles[i].orthocenter().x) + fabs(triangles[i].orthocenter().y);

        if (orthDistCatched < orthDistCurrent)
        {
            maxdTriangle = triangles[i];
        }
    }

    return maxdTriangle;
}
