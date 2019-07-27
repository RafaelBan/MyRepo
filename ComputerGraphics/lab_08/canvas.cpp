#include "canvas.h"

#include <cmath>
#include <QTest>
#include <QGuiApplication>
#include <QMessageBox>

using namespace std;

Canvas::Canvas(QWidget *parent) :
    QWidget (parent),

    type(InputType::Line),
    state(InputState::Undefined),

    _cutColor(MyColors::pink),
    _cutterColor(MyColors::blue),
    _backGroundColor(MyColors::white),
    _foreGroundColor(MyColors::black),

    cutterPoints({}),
    edgeIsSelected(false)
{
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);

    qDebug() << vmul({1, 2}, {3, 4});
}

QColor Canvas::cutColor()
{
    return _cutColor;
}

QColor Canvas::cutterColor()
{
    return _cutterColor;
}

QColor Canvas::backGroundColor()
{
    return _backGroundColor;
}

QColor Canvas::foreGroundColor()
{
    return _foreGroundColor;
}

void Canvas::setCutColor(QColor color)
{
    _cutColor = color;
}

void Canvas::setCutterColor(QColor color)
{
    _cutterColor = color;
}

void Canvas::setBackGroundColor(QColor color)
{
    _backGroundColor = color;
}

void Canvas::setForeGroundColor(QColor color)
{
    _foreGroundColor = color;
}

void Canvas::setType(InputType type)
{
    this->type = type;
    state = InputState::Undefined;

    if (cutterPoints.count() < 3)
    {
        cutterPoints.clear();
    }
    else if (cutterPoints.first() != cutterPoints.back())
    {
        QMessageBox::critical(this, "Ошибка", "Введён незамкнутый отсекатель");
        cutterPoints.clear();
    }

    update();
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    painter.fillRect(0, 0, width(), height(), backGroundColor());

    if (underMouse())
    {
        if (type == InputType::Line)
        {
            painter.setPen(foreGroundColor());
        }
        if (type == InputType::Cutter)
        {
            painter.setPen(cutterColor());
        }

        for (auto edge: tempEdges)
        {
            drawAlgo::draw_line_bresenham_i(edge.first, edge.second, painter);
        }
    }

    painter.setPen(cutterColor());
    for (auto it = cutterPoints.begin(); it != cutterPoints.end();)
    {
        auto prev = it++;

        if (it != cutterPoints.end())
        {
            painter.drawLine(*prev, *it);
        }
    }

    for (auto edge: edges)
    {
        painter.setPen(foreGroundColor());
        painter.drawLine(edge.first, edge.second);
        draw_line(edge.first, edge.second, painter);
    }

    if (edgeIsSelected)
    {
        painter.setPen(QPen(cutterColor(), 3));
        painter.drawLine(selectedEdge.first, selectedEdge.second);
    }
}

void Canvas::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);
    update();
}

void Canvas::clear()
{
    edges.clear();
    doCutting.clear();
    tempEdges.clear();
    cutterPoints.clear();

    state = InputState::Undefined;

    update();
}

void Canvas::addPoint(int x, int y)
{
    switch (type)
    {
    case InputType::Cutter:
        if (QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier) && cutterPoints.count() > 0)
        {
            int last_x = cutterPoints.back().x();
            int last_y = cutterPoints.back().y();

            if (fabs(last_x - x) < fabs(last_y - y))
            {
                x = last_x;
            }
            else
            {
                y = last_y;
            }
        }

        cutterPoints.append({x, y});
        tempPoint = cutterPoints.back();
        break;

    case InputType::Line:
        if (edgeIsSelected)
        {
            auto point = toParallelPoint({(double)x, (double)y}, tempPoint,
                                         selectedEdge.first, selectedEdge.second).toPoint();
            x = point.x();
            y = point.y();
        }
        else if (QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
        {
            int last_x = tempPoint.x();
            int last_y = tempPoint.y();

            if (fabs(last_x - x) < fabs(last_y - y))
            {
                x = last_x;
            }
            else
            {
                y = last_y;
            }
        }
        else if (QGuiApplication::keyboardModifiers().testFlag(Qt::AltModifier))
        {
            QPoint temp = toParallelPoint({(double)x, (double)y}, tempPoint).toPoint();
            x = temp.x();
            y = temp.y();
        }

        edges.append({tempPoint, QPoint(x, y)});
        doCutting.append(false);
        state = InputState::Undefined;
        break;

    default:
        qDebug() << "Unexpected input type";
        break;
    }
    if (QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
    {
    }

    tempEdges.clear();
}

void Canvas::touchPoint(int x, int y)
{
    switch (state)
    {
    case InputState::Undefined:

        if (QGuiApplication::keyboardModifiers().testFlag(Qt::AltModifier))
        {
            selectEdge(x, y);
            return;
        }

        tempPoint = {x, y};
        state = InputState::Entering;

        if (type == InputType::Cutter)
        {
            cutterPoints.clear();
            unselectEdge();
            addPoint(x, y);
        }

        break;

    case InputState::Entering:
        addPoint(x, y);
        break;

    default:
        qDebug() << "Unexpected input state";
        break;
    }

    update();
}

void Canvas::lockPoint(int x, int y)
{
    if (type == InputType::Cutter && state == InputState::Entering)
    {
        if (cutterPoints.first() != cutterPoints.back())
        {
            cutterPoints.append(cutterPoints.first());
            qDebug() << isConvex(cutterPoints);
            state = InputState::Undefined;

            if (!isConvex(cutterPoints))
            {
                QMessageBox::critical(this, "Ошибка", "Введён невыпуклый отсекатель");
                cutterPoints.clear();
            }

            tempEdges.clear();
            update();
        }
    }
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    int x = event->localPos().toPoint().x();
    int y = event->localPos().toPoint().y();

    if (event->button() == Qt::LeftButton)
    {
        touchPoint(x, y);
    }
    if (event->button() == Qt::RightButton)
    {
        if (type == InputType::Cutter)
        {
            lockPoint(x, y);
        }
        if (type == InputType::Line)
        {
        }
        if (QGuiApplication::keyboardModifiers().testFlag(Qt::AltModifier))
        {
            unselectEdge();
        }
    }

    update();
}

void Canvas::selectEdge(int x, int y)
{
    if (cutterPoints.count() < 2)
    {
        return;
    }

    QPointF srch = {(double)x, (double)y};

    QPointF A = cutterPoints[0];
    QPointF B = cutterPoints[1];
    double minDist = pointLineDist(srch, A, B);

    for (int i = 0; i < cutterPoints.count() - 1; i++)
    {
        QPointF tempA = cutterPoints[i];
        QPointF tempB = cutterPoints[i + 1];
        double tempDist = pointLineDist(srch, tempA, tempB);

        if (minDist > tempDist)
        {
            A = tempA;
            B = tempB;
            minDist = tempDist;
        }
    }

    edgeIsSelected = true;
    selectedEdge = {A.toPoint(), B.toPoint()};
}

void Canvas::unselectEdge()
{
    edgeIsSelected = false;
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    update();
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);

    tempEdges.clear();

    int x = event->localPos().toPoint().x();
    int y = event->localPos().toPoint().y();

    if (state == InputState::Entering)
    {
        QPoint p1, p2;

        switch (type)
        {
        case InputType::Cutter:
            {
                p1 = cutterPoints.back();
                p2 = {x, y};
            }
            break;

        case InputType::Line:
            {
                p1 = tempPoint;
                p2 = {x, y};
            }
            break;

        default:
            qDebug() << "Unexpected temp figure";
            break;
        }

        if (edgeIsSelected)
        {
            p2 = toParallelPoint(p2, p1, selectedEdge.first, selectedEdge.second).toPoint();
        }
        else if (QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
        {
            if (fabs(p1.x() - x) < fabs(p1.y() - y))
            {
                x = p1.x();
            }
            else
            {
                y = p1.y();
            }

            p2 = {x, y};
        }
        else if (QGuiApplication::keyboardModifiers().testFlag(Qt::AltModifier))
        {
            p2 = toParallelPoint(p2, tempPoint).toPoint();
        }

        tempEdges.append({p1, p2});
    }

    update();
}

void Canvas::draw_line(QPointF P1, QPointF P2, QPainter &painter)
{
    if (cutterPoints.count() < 3)
    {
        return;
    }
    else if (cutterPoints.first() != cutterPoints.back())
    {
        return;
    }

    int sign = 1;

    (void) isConvex(cutterPoints, &sign);

    QPointF D = P2 - P1;

    double tl = 0;
    double th = 1;

    bool visible = true;

    for (int i = 0; i < cutterPoints.count() - 1; i++)
    {
        QPointF edge = cutterPoints[i + 1] - cutterPoints[i];

        QPointF n = {-edge.y(), edge.x()};
        n *= sign;

        QPointF f = cutterPoints[i];

        QPointF w = P1 - f;

        double sw = smul(w, n);
        double sd = smul(D, n);

        if (fabs(sd) >= EPSILON)
        {
            double t = -1 * sw/sd;

            if (sd > 0)
            {
                if (t > 1)
                {
                    visible = false;
                    break;
                }
                else
                {
                    tl = std::max(t, tl);
                }
            }

            if (sd < 0)
            {
                if (t < 0)
                {
                    visible = false;
                    break;
                }
                else
                {
                    th = std::min(t, th);
                }
            }
        }
        else if (sw < 0)
        {
            visible = false;
            break;
        }
    }

    if (visible && (tl <= th))
    {
        painter.setPen(QPen(cutColor(), 2));
        painter.drawLine(P1 + (P2 - P1) * tl, P1 + (P2 - P1) * th);
    }
}

double Canvas::pointDist(QPointF p1, QPointF p2)
{
    return sqrt( pow((p1 - p2).x(), 2) + pow((p1 - p2).y(), 2));
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);

    if (edgeIsSelected)
    {
        return;
    }

    if (state == InputState::Entering)
    {
        if (event->key() == Qt::Key_Control)
        {
            int x = cursor().pos().x() - mapToGlobal(pos()).x() + pos().x();
            int y = cursor().pos().y() - mapToGlobal(pos()).y() + pos().y();
            QPoint curPoint;

            int last_x = tempPoint.x();
            int last_y = tempPoint.y();

            if (fabs(last_x - x) < fabs(last_y - y))
            {
                x = last_x;
            }
            else
            {
                y = last_y;
            }

            curPoint = {x, y};

            tempEdges.clear();
            tempEdges.append({ tempPoint, curPoint });
        }
        if (event->key() == Qt::Key_Alt)
        {
            if (type == InputType::Line)
            {
                int x = cursor().pos().x() - mapToGlobal(pos()).x() + pos().x();
                int y = cursor().pos().y() - mapToGlobal(pos()).y() + pos().y();
                QPoint curPoint;

                curPoint = {x, y};
                curPoint = toParallelPoint(curPoint, tempPoint).toPoint();

                tempEdges.clear();
                tempEdges.append({ tempPoint, curPoint });
            }
        }
    }

    update();
}

void Canvas::keyReleaseEvent(QKeyEvent *event)
{
    QWidget::keyReleaseEvent(event);

//    if (event->key() == Qt::Key_Control)
    if (!edgeIsSelected)
    {
        if (state == InputState::Entering)
        {
            int x = cursor().pos().x() - mapToGlobal(pos()).x() + pos().x();
            int y = cursor().pos().y() - mapToGlobal(pos()).y() + pos().y();
            QPoint curPoint(x, y);

            tempEdges.clear();
            tempEdges.append({ tempPoint, curPoint });
        }
    }

    update();
}

double Canvas::pointLineDist(QPointF p0, QPointF p1, QPointF p2)
{
    return pointDist(p0, pointProjection(p0, p1, p2));
}

QPointF Canvas::pointProjection(QPointF p0, QPointF p1, QPointF p2)
{
    double x1 = p1.x();
    double y1 = p1.y();

    double x2 = p2.x();
    double y2 = p2.y();

    double A = y1 - y2;
    double B = x2 - x1;
    double C = x1*y2 - x2*y1;

    return pointProjection(p0, p1, A, B, C);
}

QPointF Canvas::pointProjection(QPointF p0, QPointF p1, double A, double B, double C)
{
    double x0 = p0.x();
    double y0 = p0.y();

    double x1 = p1.x();
    double y1 = p1.y();

    if (fabs(B) < EPSILON)
    {
        return {x1, y0};
    }

    if (fabs(A) < EPSILON)
    {
        return {x0, y1};
    }

    double kb = A / -B;
    double bb = C / -B;

    double ka = -1 / kb;
    double ba = y0 - x0*ka;

    if (fabs(ka - kb) < EPSILON)
    {
        qDebug() << "Conflict: ka == kb";
    }

    double x = (bb - ba) / (ka - kb);
    double y = ka * x + ba;

    return {x, y};
}

QPointF Canvas::toParallelPoint(QPointF p2, QPointF p1)
{
    if (cutterPoints.count() < 2)
    {
        return p2;
    }

    QPointF srch = (p1 + p2) / 2;

    QPointF A = cutterPoints[0];
    QPointF B = cutterPoints[1];
    double minDist = pointLineDist(srch, A, B);

    for (int i = 0; i < cutterPoints.count() - 1; i++)
    {
        QPointF tempA = cutterPoints[i];
        QPointF tempB = cutterPoints[i + 1];
        double tempDist = pointLineDist(srch, tempA, tempB);

        if (minDist > tempDist)
        {
            A = tempA;
            B = tempB;
            minDist = tempDist;
        }
    }

    return  toParallelPoint(p2, p1, A, B);
}

QPointF Canvas::toParallelPoint(QPointF p2, QPointF p1, QPointF A, QPointF B)
{
    double x1 = A.x();
    double y1 = A.y();

    double x2 = B.x();
    double y2 = B.y();

    double Ar = y1 - y2;
    double Br = x2 - x1;
    double Cr = -Ar * p1.x() + -Br * p1.y();

    return pointProjection(p2, p1, Ar, Br, Cr);
}

bool Canvas::isConvex(QList<QPoint> figure, int *sign)
{
    if (figure.count() < 3)
    {
        return false;
    }

    figure.append(figure[1]);

    bool isNotNull = false;
    bool isNeg = false;
    bool isPos = false;

    for (int i = 0; i < figure.count() - 2; i++)
    {
        QPointF p1 = figure[i];
        QPointF p2 = figure[i + 1];
        QPointF p3 = figure[i + 2];

        double res = vmul(p2 - p1, p3 - p2);

        if (abs(res) >= EPSILON)
        {
            isNotNull = true;

            if (res > 0)
            {
                isPos = true;
            }
            if (res < 0)
            {
                isNeg = true;
            }
        }

        qDebug() << (p2 - p1) << (p3 - p2) << res;
    }

    if (sign)
    {
        if (isPos)
        {
            *sign = 1;
        }
        if (isNeg)
        {
            *sign = -1;
        }
    }

    return isPos != isNeg;
}

double Canvas::smul(QPointF v1, QPointF v2)
{
    return (v1.x()*v2.x() + v1.y()*v2.y());
}

double Canvas::vmul(QPointF v1, QPointF v2)
{
    return (v1.x()*v2.y() - v1.y()*v2.x());
//    return sqrt((v1.x() * v1.x() + v1.y() * v1.y())*(v2.x() * v2.x() + v2.y() * v2.y()) - smul(v1, v2)*smul(v1, v2));
}
