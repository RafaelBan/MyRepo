#ifndef MYLIB_H
#define MYLIB_H

#include <QString>
#include <QList>

#include "geometry.h"

bool isDouble(QString str);
triangle_t findTriangle(QList<triangle_t> triangles);
QList<triangle_t> makeTriangels(QList<point_t> points, bool *isOK = nullptr);

#endif // MYLIB_H
