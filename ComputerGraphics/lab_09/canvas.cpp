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

    bool isCr;
    qDebug() << _cross({100, 100}, {100, 400}, {200, 50}, {500, 370}, &isCr);
    qDebug() << isCr;
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

    for (auto figure: figures)
    {
        for (int i = 0; i < figure.count() - 1; i++)
        {
            painter.setPen(foreGroundColor());
            painter.drawLine(figure[i], figure[i + 1]);
//            draw_line(figure[i], figure[i + 1], painter);
        }
        draw_figure(figure, painter);
    }

    for (int i = 0; i < tempFigure.count() - 1; i++)
    {
        painter.setPen(foreGroundColor());
        painter.drawLine(tempFigure[i], tempFigure[i + 1]);
//        draw_line(tempFigure[i], tempFigure[i + 1], painter);
    }

    if (edgeIsSelected)
    {
        painter.setPen(QPen(cutterColor(), 3));
        painter.drawLine(selectedEdge.first, selectedEdge.second);
    }

    for (auto p: vericesPoints)
    {
        painter.setPen(foreGroundColor());
        painter.setBrush(Qt::SolidPattern);
        painter.drawEllipse(p.x() - 5/2, p.y() - 5/2, 5, 5);
    }

    for (auto p: cvericesPoints)
    {
        painter.setPen(cutterColor());
        painter.setBrush(Qt::SolidPattern);
        painter.drawEllipse(p.x() - 5/2, p.y() - 5/2, 5, 5);
    }

    for (auto figure: figures)
    {
        draw_figure(figure, painter);
    }

    painter.setPen(foreGroundColor());
    vericesPoints.clear();
    cvericesPoints.clear();
}

void Canvas::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);
    update();
}

void Canvas::clear()
{
    edges.clear();
    tempEdges.clear();
    cutterPoints.clear();

    figures.clear();
    tempFigure.clear();

    vericesPoints.clear();
    cvericesPoints.clear();

    state = InputState::Undefined;

    update();
}

bool Canvas::isOnLSegment(QPointF p0, QPointF p1, QPointF p2)
{
    if (!isInSquare(p0, p1, p2))
    {
        return false;
    }

    if (fabs(p1.x() - p2.x()) < EPSILON)
    {
        return (fabs(p0.x() - p2.x()) < EPSILON);
    }

    double k = (p2.y() - p1.y()) / (p2.x() - p1.x());

    return (fabs((p0.y() + p1.y()) - (p0.x() + p1.x()) * k) < EPSILON);
}

bool Canvas::isInSquare(QPointF p0, QPointF p1, QPointF p2)
{
    if (!(std::min(p1.x(), p2.x()) <= p0.x() && p0.x() <= max(p1.x(), p2.x())))
    {
        return false;
    }

    if (!(std::min(p1.y(), p2.y()) <= p0.y() && p0.y() <= max(p1.y(), p2.y())))
    {
        return false;
    }

    return true;
}

QPair<QPointF, QPointF> Canvas::getNearestLSeg(QList<QPoint> figure, QPointF point, bool *success)
{
    if (figure.count() < 2)
    {
        return {point, point};
    }

    QPair<QPointF, QPointF> res = {point, point};
    bool flag = false;
    double minDist = pointDist(point, pointProjection(point, figure[0], figure[1]));

    for (int i = 0; i < figure.count() - 1; i++)
    {
        QPointF pp = pointProjection(point, figure[i], figure[i + 1]);

        if (isInSquare(pp, figure[i], figure[i + 1]))
        {
            if (!flag || minDist > pointDist(point, pp))
            {
                flag = true;
                minDist = pointDist(point, pp);
                res = {figure[i], figure[i + 1]};
            }
        }
    }

    if (success)
    {
        *success = flag;
    }

    return res;
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
        else if (QGuiApplication::keyboardModifiers().testFlag(Qt::ShiftModifier) &&
                 QGuiApplication::keyboardModifiers().testFlag(Qt::AltModifier))
        {
            bool isOK;
            QPair<QPointF, QPointF> edge;
            int _x = x, _y = y;

            bool flag = false;
            double minDist = 0;
            for (auto f: figures)
            {
                edge = getNearestLSeg(f, {(double)x, (double)y}, &isOK);

                if (isOK)
                {
                    auto pp = pointProjection({(double)x, (double)y}, edge.first, edge.second).toPoint();

                    if (!flag || minDist > pointDist({(double)x, (double)y}, pp))
                    {
                        flag = true;
                        minDist = pointDist({(double)x, (double)y}, pp);

                        _x = pp.x();
                        _y = pp.y();
                    }
                }
            }

            x = _x; y = _y;
        }
        else if (QGuiApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))
        {
//            if (cutterPoints.count() > 1)
            {
                QPointF cur = {(double)x, (double)y};
                bool flag = false;
                double minDist = 0;
                QPoint pm;

                for (auto f: figures)
                {
                    for (auto p: f)
                    {
                        if (!flag || minDist > pointDist(p, cur))
                        {
                            flag = true;
                            minDist = pointDist(p, cur);

                            pm = p;
                            qDebug() << pm;
                        }
                    }
                }

                if (flag)
                {
                    x = pm.x();
                    y = pm.y();
                }
            }
        }

        cutterPoints.append({x, y});
        tempPoint = cutterPoints.back();
        break;

    case InputType::Line:
    {
        QPoint lastPoint = tempPoint;

        if (type == InputType::Line && !tempFigure.isEmpty())
        {
            lastPoint = tempFigure.back();
        }

        if (edgeIsSelected)
        {
            auto point = toParallelPoint({(double)x, (double)y}, lastPoint,
                                         selectedEdge.first, selectedEdge.second).toPoint();
            x = point.x();
            y = point.y();
        }
        else if (QGuiApplication::keyboardModifiers().testFlag(Qt::ShiftModifier) &&
                 QGuiApplication::keyboardModifiers().testFlag(Qt::AltModifier))
        {
            bool isOK;
            auto edge = getNearestLSeg(cutterPoints, {(double)x, (double)y}, &isOK);

            if (isOK)
            {
                auto pp = pointProjection({(double)x, (double)y}, edge.first, edge.second).toPoint();
                x = pp.x();
                y = pp.y();
            }
        }
        else if (QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
        {
            int last_x = tempFigure.back().x();
            int last_y = tempFigure.back().y();

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
            QPoint temp = toParallelPoint({(double)x, (double)y}, lastPoint).toPoint();
            x = temp.x();
            y = temp.y();
        }
        else if (QGuiApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))
        {
            if (cutterPoints.count() > 1)
            {
                QPointF cur = {(double)x, (double)y};
                double minDist = pointDist(cutterPoints.first(), cur);
                x = cutterPoints.first().x();
                y = cutterPoints.first().y();

                for (auto point: cutterPoints)
                {
                    if (minDist > pointDist(point, cur))
                    {
                        minDist = pointDist(point, cur);
                        x = point.x();
                        y = point.y();
                    }
                }
            }
        }

//        edges.append({tempPoint, QPoint(x, y)});
//        state = InputState::Undefined;
        tempFigure.append(QPoint(x, y));
        update();
    }
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

        if (QGuiApplication::keyboardModifiers().testFlag(Qt::AltModifier) &&
            !QGuiApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))
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

        if (type == InputType::Line)
        {
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

    if (type == InputType::Line && state == InputState::Entering)
    {
        tempFigure.append(tempFigure.first());
        figures.append(tempFigure);

        tempFigure.clear();
        tempEdges.clear();
        state = InputState::Undefined;
        update();
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
        if (QGuiApplication::keyboardModifiers().testFlag(Qt::AltModifier))
        {
            unselectEdge();
            return;
        }
        if (type == InputType::Cutter)
        {
            lockPoint(x, y);
        }
        if (type == InputType::Line)
        {
            lockPoint(x, y);
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
                p1 = tempFigure.back();
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
        else if (QGuiApplication::keyboardModifiers().testFlag(Qt::ShiftModifier) &&
                 QGuiApplication::keyboardModifiers().testFlag(Qt::AltModifier))
        {
            QList< QList<QPoint> > figures;

            if (type == InputType::Line)
            {
                figures = {cutterPoints};
            }
            if (type == InputType::Cutter)
            {
                figures = this->figures;
            }

            bool isOK;
            QPair<QPointF, QPointF> edge;

            bool flag = false;
            double minDist = 0;
            for (auto f: figures)
            {
                edge = getNearestLSeg(f, {(double)x, (double)y}, &isOK);

                if (isOK)
                {
                    auto pp = pointProjection({(double)x, (double)y}, edge.first, edge.second).toPoint();

                    if (!flag || minDist > pointDist({(double)x, (double)y}, pp))
                    {
                        flag = true;
                        minDist = pointDist({(double)x, (double)y}, pp);

                        p2 = pp;
                    }
                }
            }
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
            if (type == InputType::Line)
            {
                p2 = toParallelPoint(p2, p1).toPoint();
            }
        }

        tempEdges.append({p1, p2});
    }

    if (QGuiApplication::keyboardModifiers().testFlag(Qt::ShiftModifier) &&
        !QGuiApplication::keyboardModifiers().testFlag(Qt::AltModifier) &&
        !QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
    {
        QList< QList<QPoint> > figures;

        if (type == InputType::Line)
        {
            figures = {cutterPoints};
        }
        if (type == InputType::Cutter)
        {
            figures = this->figures;
        }

        bool flag = false;
        double minDist = 0;
        QPoint pm;

        for (auto f: figures)
        {
            for (auto p: f)
            {
                if (!flag || minDist > pointDist(p, event->localPos()))
                {
                    flag = true;
                    minDist = pointDist(p, event->localPos());

                    pm = p;
                }
            }
        }

        if (flag)
        {
            if (type == InputType::Line)
            {
                vericesPoints.append(pm);
            }
            if (type == InputType::Cutter)
            {
                cvericesPoints.append(pm);
            }
        }
    }

    update();
}

QPointF Canvas::_cross(QPointF line_p1, QPointF line_p2, QPointF p1, QPointF p2, bool *success)
{
    double x;
    double y;

    if (success)
    {
        *success = false;
    }

    if (fabs(p1.x() - p2.x()) < EPSILON)
    {
        if (fabs(line_p1.x() - line_p2.x()) > EPSILON)
        {
            x = p1.x();

            double k = (line_p2.y() - line_p1.y()) / (line_p2.x() - line_p1.x());
            double b = (line_p2.x() * line_p1.y() - line_p1.x() * line_p2.y()) / (line_p2.x() - line_p1.x());

            y = k * x + b;
        }
        else
        {
            return {0, 0};
        }
    }
    else if (fabs(line_p1.x() - line_p2.x()) < EPSILON)
    {
        x = line_p1.x();

        double k = (p2.y() - p1.y()) / (p2.x() - p1.x());
        double b = (p2.x() * p1.y() - p1.x() * p2.y()) / (p2.x() - p1.x());

        y = k * x + b;
    }
    else
    {
        double k1 = (p2.y() - p1.y()) / (p2.x() - p1.x());
        double b1 = (p2.x() * p1.y() - p1.x() * p2.y()) / (p2.x() - p1.x());

        double k2 = (line_p2.y() - line_p1.y()) / (line_p2.x() - line_p1.x());
        double b2 = (line_p2.x() * line_p1.y() - line_p1.x() * line_p2.y()) / (line_p2.x() - line_p1.x());

        if (fabs(k1 - k2) > EPSILON)
        {
            x = (b2 - b1) / (k1 - k2);
            y = k1 * x + b1;
        }
        else
        {
            return {0, 0};
        }
    }

    bool isOK;
    QPointF cr = {round(x), round(y)};

    if ((std::min(p1.x(), p2.x()) <= cr.x() && cr.x() <= std::max(p1.x(), p2.x())) &&
        (std::min(p1.y(), p2.y()) <= cr.y() && cr.y() <= std::max(p1.y(), p2.y())))
    {
        isOK = true;
    }
    else
    {
        isOK = false;
    }

    if (success)
    {
        *success = isOK;
    }

    return  cr;
}

QPointF Canvas::cross(QPointF line_p1, QPointF line_p2, QPointF p1, QPointF p2, bool *success)
{
    bool isOK = true;

    if (success)
    {
        *success = false;
    }

    QPointF r1 = ratios(line_p1, line_p2, &isOK);
    if (!isOK)
    {
        return {0, 0};
    }

    QPointF r2 = ratios(p1, p2, &isOK);
    if (!isOK)
    {
        return {0, 0};
    }

    QPointF cr = coordinates(r1, r2, success);

//    qDebug() << r1 << r2 << cr;

    if (std::min(p1.x(), p2.x()) <= cr.x() <= std::max(p1.x(), p2.x()))
    {
        if (std::min(p1.y(), p2.y()) <= cr.y() <= std::max(p1.y(), p2.y()))
        {
            isOK = true;
        }
        else
        {
            isOK = false;
        }
    }
    else
    {
        isOK = false;
    }

    if (success)
    {
        *success = isOK;
    }

    return  cr;
}

QPointF Canvas::ratios(QPointF p1, QPointF p2, bool *success)
{
    if (success)
    {
        *success = true;
    }

    double x1 = p1.x();
    double y1 = p1.y();
    double x2 = p2.x();
    double y2 = p2.y();

    double denom = x2 - x1;

    if (fabs(denom) < EPSILON)
    {
        if (success)
        {
            *success = false;
        }

        return {x1, y1};
    }

    double k = (y2 - y1) / (denom);
    double b = y1 - k * x1;

    return {k, b};
}

QPointF Canvas::coordinates(QPointF r1, QPointF r2, bool *success)
{
    if (success)
    {
        *success = true;
    }

    double k1 = r1.x();
    double b1 = r1.y();
    double k2 = r2.x();
    double b2 = r2.y();

    double denom = k1 - k2;

    if (fabs(denom) < EPSILON)
    {
        if (success)
        {
            *success = false;
        }

        return {0, 0};
    }

    double x = (b2 - b1) / (denom);
    double y = k1 * x + b1;

    return {x, y};
}

void Canvas::draw_figure(QList<QPoint> figure, QPainter &painter)
{
    if (cutterPoints.count() < 2 || cutterPoints.first() != cutterPoints.back())
    {
        return;
    }

    QList<QPointF> fig;
    for (auto p: figure)
    {
        fig.append(p);
    }
//    qDebug() << "***";
//    qDebug() << "Current figure:" << fig;

    bool visible = true;
    int sign = 1;

    (void) isConvex(cutterPoints, &sign);

    QPointF f = {0, 0};
    QPointF s = {0, 0};

    QList<QPointF> cutFigure;
    for (int i = 0; i < cutterPoints.count() - 1; i++)
    {

        QPointF edge = cutterPoints[i + 1] - cutterPoints[i];
        QPointF n = {-edge.y(), edge.x()};
        n *= sign;
//        qDebug() << "Current cutter edge:" << cutterPoints[i] << cutterPoints[i + 1];
//        qDebug() << "n =" << n;

        for (int j = 0; j < fig.count(); j++)
        {
//            qDebug() << "Current point:" << fig[j];
            if (j == 0)
            {
                f = fig[0];
//                qDebug() << "first: " << f;
            }
            else
            {
                bool isCrossing;

                QPointF L = _cross(cutterPoints[i], cutterPoints[i + 1], s, fig[j], &isCrossing);

//                qDebug() << s << fig[j] << L << isCrossing;

                if (isCrossing)
                {
                    cutFigure.append(L);
                }
            }

            s = fig[j];

//            qDebug() << "scalar" << smul(n, s - cutterPoints[i]);

            if (smul(n, s - cutterPoints[i]) >= 0 || isOnLSegment(s,
                                                                  cutterPoints[i],
                                                                  cutterPoints[i + 1]))
            {
                cutFigure.append(s);
//                qDebug() << s << "is not cut";
            }
            else
            {
//                qDebug() << s << "is cut";
            }
        }

        if (cutFigure.count() == 0)
        {
//            qDebug() << cutFigure;
            visible = false;
            break;
        }
//        qDebug() << cutFigure;

        bool isCrossing;
        QPointF L = _cross(cutterPoints[i], cutterPoints[i + 1], s, f, &isCrossing);
//        qDebug() << cutterPoints[i] << cutterPoints[i + 1] << s << f << isCrossing;

        if (isCrossing)
        {
            cutFigure.append(L);
        }

        fig = cutFigure;
        cutFigure.clear();
    }

    if (visible)
    {
        if (fig.count() > 0 && fig.first() != fig.back())
        {
            fig.append(fig.first());
        }

        painter.setPen(QPen(cutColor(), 2));
        for (int i = 0; i < fig.count() - 1; i++)
        {
            painter.drawLine(fig[i], fig[i + 1]);
        }
    }
//    qDebug() << "***";
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
        painter.setPen(cutColor());
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
        if (QGuiApplication::keyboardModifiers().testFlag(Qt::ShiftModifier) &&
              QGuiApplication::keyboardModifiers().testFlag(Qt::AltModifier))
        {
            int x = cursor().pos().x() - mapToGlobal(pos()).x() + pos().x();
            int y = cursor().pos().y() - mapToGlobal(pos()).y() + pos().y();

            QPoint lastpoint;
            QList< QList<QPoint> > figures;

            if (type == InputType::Line)
            {
                lastpoint = tempFigure.back();
                figures = {cutterPoints};
            }
            if (type == InputType::Cutter)
            {
                lastpoint = cutterPoints.back();
                figures = this->figures;
            }

            bool isOK;
            QPair<QPointF, QPointF> edge;

            for (auto f: figures)
            {
                edge = getNearestLSeg(f, {(double)x, (double)y}, &isOK);
            }

            if (isOK)
            {
                auto pp = pointProjection({(double)x, (double)y}, edge.first, edge.second).toPoint();
                x = pp.x();
                y = pp.y();
            }

            if (type == InputType::Line)
            {
                tempEdges.clear();
                tempEdges.append({ lastpoint, {x, y}});
            }
            if (type == InputType::Cutter)
            {
                tempEdges.clear();
                tempEdges.append({ lastpoint, {x, y}});
            }

            update();
            return;
        }
        if (event->key() == Qt::Key_Control)
        {
            int x = cursor().pos().x() - mapToGlobal(pos()).x() + pos().x();
            int y = cursor().pos().y() - mapToGlobal(pos()).y() + pos().y();
            QPoint curPoint;
            QPoint lastPoint;

            if (type == InputType::Line)
            {
                lastPoint = tempFigure.back();
            }
            if (type == InputType::Cutter)
            {
                lastPoint = cutterPoints.back();
            }

            int last_x = lastPoint.x();
            int last_y = lastPoint.y();

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
            tempEdges.append({ lastPoint, curPoint });
        }
        if (event->key() == Qt::Key_Alt)
        {
            if (type == InputType::Line)
            {
                QPoint lastPoint = tempFigure.back();

                int x = cursor().pos().x() - mapToGlobal(pos()).x() + pos().x();
                int y = cursor().pos().y() - mapToGlobal(pos()).y() + pos().y();
                QPoint curPoint;

                curPoint = {x, y};
                curPoint = toParallelPoint(curPoint, lastPoint).toPoint();

                tempEdges.clear();
                tempEdges.append({ lastPoint, curPoint });
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
            QPoint lastPoint;

            if (type == InputType::Line)
            {
                lastPoint = tempFigure.back();
            }
            if (type == InputType::Cutter)
            {
                lastPoint = cutterPoints.back();
            }

            tempEdges.clear();
            tempEdges.append({ lastPoint, curPoint });
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

//        qDebug() << (p2 - p1) << (p3 - p2) << res;
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
