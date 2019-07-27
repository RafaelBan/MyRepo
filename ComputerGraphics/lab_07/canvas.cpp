#include "canvas.h"

#include <cmath>
#include <QTest>
#include <QGuiApplication>

using namespace std;

Canvas::Canvas(QWidget *parent) :
    QWidget (parent),

    type(InputType::Line),
    state(InputState::Undefined),

    _cutColor(MyColors::pink),
    _cutterColor(MyColors::blue),
    _backGroundColor(MyColors::white),
    _foreGroundColor(MyColors::black),

    cutterDefined(false)
{
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
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
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    painter.fillRect(0, 0, width(), height(), backGroundColor());

    if (cutterDefined)
    {
        painter.setPen(cutterColor());
        drawAlgo::draw_line_bresenham_i(cp1, cp2, painter);
        drawAlgo::draw_line_bresenham_i(cp2, cp3, painter);
        drawAlgo::draw_line_bresenham_i(cp3, cp4, painter);
        drawAlgo::draw_line_bresenham_i(cp4, cp1, painter);
    }

    for (auto edge: edges)
    {
        painter.setPen(foreGroundColor());
//        drawAlgo::draw_line_bresenham_i(edge.first, edge.second, painter);
        painter.drawLine(edge.first, edge.second);
        painter.setPen(cutColor());
        draw_line(edge.first, edge.second, painter);
    }

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
    cutterDefined = false;

    state = InputState::Undefined;

    update();
}

void Canvas::addPoint(int x, int y)
{
    switch (type)
    {
    case InputType::Cutter:
        cutterDefined = true;
        cp1 = tempPoint;
        cp3 = {x, y};
        cp2 = {cp1.x(), cp3.y()};
        cp4 = {cp3.x(), cp1.y()};
        break;

    case InputType::Line:
        if (QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
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

        edges.append({tempPoint, QPoint(x, y)});
        doCutting.append(false);
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
        tempPoint = {x, y};
        state = InputState::Entering;
        break;

    case InputState::Entering:
        addPoint(x, y);
        state = InputState::Undefined;
        break;

    default:
        qDebug() << "Unexpected input state";
        break;
    }

    update();
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    int x = event->localPos().toPoint().x();
    int y = event->localPos().toPoint().y();

    if (event->button() == Qt::LeftButton)
    {
        touchPoint(x, y);
    }

    update();
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
        switch (type)
        {
        case InputType::Cutter:
            {
                QPoint p1 = tempPoint;
                QPoint p3 = {x, y};
                QPoint p2 = {p1.x(), p3.y()};
                QPoint p4 = {p3.x(), p1.y()};

                tempEdges.append({p1, p2});
                tempEdges.append({p2, p3});
                tempEdges.append({p3, p4});
                tempEdges.append({p4, p1});
            }
            break;

        case InputType::Line:
            {
                QPoint p1 = tempPoint;
                QPoint p2 = {x, y};

                if (QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
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

                tempEdges.append({p1, p2});
            }
            break;

        default:
            qDebug() << "Unexpected temp figure";
            break;
        }
    }

    update();
}

int Canvas::left()
{
    return std::min(std::min(cp1.x(), cp2.x()), std::min(cp3.x(), cp4.x()));
}

int Canvas::right()
{
    return std::max(std::max(cp1.x(), cp2.x()), std::max(cp3.x(), cp4.x()));
}

int Canvas::bottom()
{
    return std::min(std::min(cp1.y(), cp2.y()), std::min(cp3.y(), cp4.y()));
}

int Canvas::top()
{
    return std::max(std::max(cp1.y(), cp2.y()), std::max(cp3.y(), cp4.y()));
}

bool Canvas::sumCode(QBitArray code)
{
    return  code[0] | code[1] | code[2] | code[3];
}

QBitArray Canvas::getPointCode(QPointF p)
{
    QBitArray code(4);

    code[0] = p.x() < left();
    code[1] = p.x() > right();
    code[2] = p.y() < bottom();
    code[3] = p.y() > top();

    return code;
}

void Canvas::draw_line(QPointF p1, QPointF p2, QPainter &painter)
{
    if (!cutterDefined)
    {
        return;
    }

    int i = 1;

C:
    QBitArray T1 = getPointCode(p1);
    QBitArray T2 = getPointCode(p2);
    bool S1 = sumCode(T1);
    bool S2 = sumCode(T2);
    bool P = sumCode(T1 & T2);

    if (!S1 && !S2)
    {
        painter.setPen(cutColor());
        painter.drawLine(p1, p2);
        return;
    }

    if (P)
    {
        return;
    }

    QPointF R = p1;

    if (i > 2)
    {
        if (!P)
        {
            painter.setPen(cutColor());
            painter.drawLine(p1, p2);
        }

        return;
    }

    if (S2)
    {
        while (fabs(pointDist(p1, p2)) >= EPSILON)
        {
            QPointF pm = (p1 + p2) / 2;
            QPointF temp = p1;

            p1 = pm;
            T1 = getPointCode(p1);

            if (sumCode(T1 & T2))
            {
                p1 = temp;
                p2 = pm;
            }
        }
    }

    p1 = p2;
    p2 = R;

    i++;

    goto C;
}

//void Canvas::draw_line(QPointF p1, QPointF p2, QPainter &painter)
//{
//    if (!cutterDefined)
//    {
//        return;
//    }

//    int i = 1;

//C:
//    QBitArray T1 = getPointCode(p1);
//    QBitArray T2 = getPointCode(p2);
//    bool S1 = sumCode(T1);
//    bool S2 = sumCode(T2);
//    bool P = sumCode(T1 & T2);

//    if (!S1 && !S2)
//    {
//        painter.setPen(cutColor());
//        painter.drawLine(p1, p2);
//        return;
//    }

//    if (P)
//    {
//        return;
//    }

//    QPointF R = p1;

//    if (i > 2)
//    {
//        if (!P)
//        {
//            painter.setPen(cutColor());
//            painter.drawLine(p1, p2);
//        }

//        return;
//    }

//    if (S2)
//    {
//        goto A;
//    }
//    else
//    {
//        goto B;
//    }
//A:
//    while (fabs(pointDist(p1, p2)) >= EPSILON)
//    {
//        QPointF pm = (p1 + p2) / 2;
//        QPointF temp = p1;

//        p1 = pm;
//        T1 = getPointCode(p1);

//        if (sumCode(T1 & T2))
//        {
//            p1 = temp;
//            p2 = pm;
//        }
//    }

//B:
//    p1 = p2;
//    p2 = R;

//    i++;

//    goto C;
//}

//void Canvas::draw_line(QPointF p1, QPointF p2, QPainter &painter)
//{
//    if (!cutterDefined)
//    {
//        return;
//    }

//    int i = 1;

//C:
//    QBitArray T1 = getPointCode(p1);
//    QBitArray T2 = getPointCode(p2);
//    bool S1 = sumCode(T1);
//    bool S2 = sumCode(T2);
//    bool P = sumCode(T1 & T2);

//    if (!S1 && !S2)
//    {
//        painter.setPen(cutColor());
//        painter.drawLine(p1, p2);
//        return;
//    }

//    if (P)
//    {
//        return;
//    }

//    QPointF R = p1;

//    if (i > 2)
//    {
//        if (!P)
//        {
//            painter.setPen(cutColor());
//            painter.drawLine(p1, p2);
//        }

//        return;
//    }

//    if (S2)
//    {
//        goto A;
//    }
//    else
//    {
//        goto B;
//    }

//A:
//    while (fabs(pointDist(p1, p2)) >= EPSILON)
//    {
//        QPointF pm = (p1 + p2) / 2;
//        QPointF temp = p1;

//        p1 = pm;
//        T1 = getPointCode(p1);

//        if (sumCode(T1 & T2))
//        {
//            p1 = temp;
//            p2 = pm;
//        }
//    }

//B:
//    p1 = p2;
//    p2 = R;
//    i++;

//    goto C;
//}

double Canvas::pointDist(QPointF p1, QPointF p2)
{
    return sqrt( pow((p1 - p2).x(), 2) + pow((p1 - p2).y(), 2));
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);

    if (event->key() == Qt::Key_Control)
    {
        if (state == InputState::Entering && type == InputType::Line)
        {
            int x = cursor().pos().x() - mapToGlobal(pos()).x() + pos().x();
            int y = cursor().pos().y() - mapToGlobal(pos()).y() + pos().y();
            QPoint curPoint;

            tempEdges.clear();

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

            tempEdges.append({ tempPoint, curPoint });
        }
    }

    update();
}

void Canvas::keyReleaseEvent(QKeyEvent *event)
{
    QWidget::keyReleaseEvent(event);

    if (event->key() == Qt::Key_Control)
    {
        if (state == InputState::Entering && type == InputType::Line)
        {
            int x = cursor().pos().x() - mapToGlobal(pos()).x() + pos().x();
            int y = cursor().pos().y() - mapToGlobal(pos()).y() + pos().y();
            QPoint curPoint(x, y);

            tempEdges.clear();

            tempEdges.append({ tempPoint, curPoint });

            update();
        }
    }
}
