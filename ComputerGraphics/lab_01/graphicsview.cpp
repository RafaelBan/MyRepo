#include "graphicsview.h"

#include <cmath>

GrapicsView::GrapicsView(QWidget *parent)
    : QWidget (parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->xMax = +5;
    this->xMin = -5;
    this->yMax = +5;
    this->yMin = -5;

    this->xRange = this->xMax - this->xMin;
    this->yRange = this->yMax - this->yMin;

    this->imageOffset = 50;
}

GrapicsView::~GrapicsView()
{

}

void GrapicsView::setPoints(QList<point_t> points)
{
    this->points.clear();

    for (int i = 0, len = points.count(); i < len; i++)
    {
        this->points.append(points[i].copy());
    }
}

void GrapicsView::setTriangles(triangle_t triangle)
{
    this->triangles.clear();

    this->triangles.append(triangle.copy());
}

void GrapicsView::setTriangles(QList<triangle_t> triangles)
{
    this->triangles.clear();

    for (int i = 0, len = triangles.count(); i < len; i++)
    {
        this->triangles.append(triangles[i].copy());
    }
}

double GrapicsView::xCartToDisp(double xC)
{
    return this->imageOffset + (xC * this->scalingK);
}

double GrapicsView::yCartToDisp(double yC)
{
    return this->imageOffset - (yC * this->scalingK);
}

void GrapicsView::setDisplayRange(QList<point_t> workPoints)
{
    if (workPoints.count() <= 0)
        return;

    double maxX = workPoints[0].x;
    double minX = workPoints[0].x;
    double maxY = workPoints[0].y;
    double minY = workPoints[0].y;

    for (int i = 1, len = workPoints.count(); i < len; i++)
    {
        if (maxX < workPoints[i].x)
        {
            maxX = workPoints[i].x;
        }
        if (minX > workPoints[i].x)
        {
            minX = workPoints[i].x;
        }

        if (maxY < workPoints[i].y)
        {
            maxY = workPoints[i].y;
        }
        if (minY > workPoints[i].y)
        {
            minY = workPoints[i].y;
        }
    }

    this->xMax = maxX;
    this->xMin = minX;
    this->yMax = maxY;
    this->yMin = minY;

    this->xRange = this->xMax - this->xMin;
    this->yRange = this->yMax - this->yMin;
}

void GrapicsView::setScalingK()
{
    double kx = (this->width() - 2 * this->imageOffset) / (this->xRange);
    double ky = (this->height() - 2 * this->imageOffset) / (this->yRange);

    this->scalingK = fmin(kx, ky);
}

void GrapicsView::draw()
{
    double dx;
    double dy;
    double rOffset;
    double xMaxPossible;
    double xMinPossible;
    double yMaxPossible;
    double yMinPossible;
    double xRangePossible;
    double yRangePossible;
    point_t imageCenter;
    QPainter painter(this);

    painter.fillRect(0, 0, this->width(), this->height(), MyColors::gBackground);

    imageCenter = point_t((this->xMax + this->xMin) / 2, (this->yMax + this->yMin) / 2);

    this->setScalingK();
    rOffset = this->imageOffset / this->scalingK;

    xRangePossible = (this->width() - 2 * this->imageOffset) / this->scalingK;
    yRangePossible = (this->height() - 2 * this->imageOffset) / this->scalingK;

    xMaxPossible = imageCenter.x + (xRangePossible);
    xMinPossible = imageCenter.x - (xRangePossible);
    yMaxPossible = imageCenter.y + (yRangePossible);
    yMinPossible = imageCenter.y - (yRangePossible);

    dx = (imageCenter.x - (+xRangePossible) / 2);
    dy = (imageCenter.y - (-yRangePossible) / 2);

    dx = -(dx * this->scalingK);
    dy = +(dy * this->scalingK);

    if (this->xRange < (200 + EPSILON) && this->yRange < (200 + EPSILON))
    {
        for (double curVal = round(xMinPossible - rOffset);
             curVal < round(xMaxPossible + rOffset);
             curVal += 1)
        {
            double x0;
            double y1, y2;

            x0 = this->xCartToDisp(curVal) + dx;
            y1 = this->yCartToDisp(yMinPossible - rOffset) + dy;
            y2 = this->yCartToDisp(yMaxPossible + rOffset) + dy;

            painter.setPen(QPen(MyColors::black, 0.1));
            painter.drawLine(QPointF(x0, y1), QPointF(x0, y2));
        }

        for (double curVal = round(yMinPossible - rOffset);
             curVal < round(yMaxPossible + rOffset);
             curVal += 1)
        {
            double x1, x2;
            double y0;

            x1 = this->xCartToDisp(xMinPossible - rOffset) + dx;
            x2 = this->xCartToDisp(xMaxPossible + rOffset) + dx;
            y0 = this->yCartToDisp(curVal) + dy;

            painter.setPen(QPen(MyColors::black, 0.1));
            painter.drawLine(QPointF(x1, y0), QPointF(x2, y0));
        }
    }

    {
        double x0;
        double y1, y2;

        x0 = this->xCartToDisp(0) + dx;
        y1 = this->yCartToDisp(yMinPossible - rOffset) + dy;
        y2 = this->yCartToDisp(yMaxPossible + rOffset) + dy;

        painter.setPen(QPen(MyColors::black, 3));
        painter.drawLine(QPointF(x0, y1), QPointF(x0, y2));
    }
    {
        double x1, x2;
        double y0;

        x1 = this->xCartToDisp(xMinPossible - rOffset) + dx;
        x2 = this->xCartToDisp(xMaxPossible + rOffset) + dx;
        y0 = this->yCartToDisp(0) + dy;

        painter.setPen(QPen(MyColors::black, 3));
        painter.drawLine(QPointF(x1, y0), QPointF(x2, y0));
    }

    foreach (triangle_t triangle, this->triangles)
    {
        double x, y;
        QPointF A, B, C;
        QPointF aH, bH, cH;
        QPointF Orthocenter, OrthP1, OrthP2;

        x = this->xCartToDisp(triangle.A().x) + dx;
        y = this->yCartToDisp(triangle.A().y) + dy;
        A = QPointF(x, y);

        x = this->xCartToDisp(triangle.B().x) + dx;
        y = this->yCartToDisp(triangle.B().y) + dy;
        B = QPointF(x, y);

        x = this->xCartToDisp(triangle.C().x) + dx;
        y = this->yCartToDisp(triangle.C().y) + dy;
        C = QPointF(x, y);

        x = this->xCartToDisp(triangle.orthocenter().x) + dx;
        y = this->yCartToDisp(triangle.orthocenter().y) + dy;
        Orthocenter = QPointF(x, y);

        x = this->xCartToDisp(triangle.orthocenter().x) + dx;
        y = this->yCartToDisp(0) + dy;
        OrthP1 = QPointF(x, y);

        x = this->xCartToDisp(0) + dx;
        y = this->yCartToDisp(triangle.orthocenter().y) + dy;
        OrthP2 = QPointF(x, y);

        x = this->xCartToDisp(triangle.aH().x) + dx;
        y = this->yCartToDisp(triangle.aH().y) + dy;
        aH = QPointF(x, y);

        x = this->xCartToDisp(triangle.bH().x) + dx;
        y = this->yCartToDisp(triangle.bH().y) + dy;
        bH = QPointF(x, y);

        x = this->xCartToDisp(triangle.cH().x) + dx;
        y = this->yCartToDisp(triangle.cH().y) + dy;
        cH = QPointF(x, y);

        painter.setPen(QPen(MyColors::red, 2.5));
        painter.drawLine(A, B);
        painter.drawLine(B, C);
        painter.drawLine(C, A);

        painter.setPen(QPen(MyColors::red, 1, Qt::DashLine));
        painter.drawLine(aH, B);
        painter.drawLine(aH, C);
        painter.drawLine(bH, A);
        painter.drawLine(bH, C);
        painter.drawLine(cH, A);
        painter.drawLine(cH, B);

        painter.setPen(QPen(MyColors::blue, 1));
        painter.drawLine(A, aH);
        painter.drawLine(B, bH);
        painter.drawLine(C, cH);

        painter.drawLine(A, Orthocenter);
        painter.drawLine(B, Orthocenter);
        painter.drawLine(C, Orthocenter);

        painter.setPen(QPen(MyColors::green, 0.75));
        painter.drawLine(Orthocenter, OrthP1);
        painter.drawLine(Orthocenter, OrthP2);

        QRect textRectA = QRect(static_cast<int>(A.x()) - TextRectL,
                                static_cast<int>(A.y()) - TextRectT,
                                TextRectW, TextRectH);
        QRect textRectB = QRect(static_cast<int>(B.x()) - TextRectL,
                                static_cast<int>(B.y()) - TextRectT,
                                TextRectW, TextRectH);
        QRect textRectC = QRect(static_cast<int>(C.x()) - TextRectL,
                                static_cast<int>(C.y()) - TextRectT,
                                TextRectW, TextRectH);
        QRect textRectOrth = QRect(static_cast<int>(Orthocenter.x()) - TextRectL,
                                   static_cast<int>(Orthocenter.y()) - TextRectT,
                                   TextRectW, TextRectH);

        painter.setPen(QPen(MyColors::black, 8));
        painter.drawPoint(A);
        painter.drawPoint(B);
        painter.drawPoint(C);

        painter.setPen(QPen(MyColors::pink, 8));
        painter.drawPoint(OrthP1);
        painter.drawPoint(OrthP2);
        painter.drawPoint(Orthocenter);

        painter.setPen(QPen(MyColors::pink, 8));
        painter.drawPoint(aH);
        painter.drawPoint(bH);
        painter.drawPoint(cH);

        painter.setPen(QPen(MyColors::black));
        painter.drawText(textRectA, triangle.A().toStr().c_str());
        painter.drawText(textRectB, triangle.B().toStr().c_str());
        painter.drawText(textRectC, triangle.C().toStr().c_str());
        painter.drawText(textRectOrth, triangle.orthocenter().toStr().c_str());
    }
}

void GrapicsView::paintEvent(QPaintEvent *event)
{
    this->draw();
}
