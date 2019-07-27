#include "canvas.h"
#include <QCursor>
#include <cmath>
#include <QTest>
#include <QGuiApplication>
#include <QTest>

using namespace std;

Canvas::Canvas(QWidget *parent) :
    QWidget (parent),

    _paintColor(MyColors::pink),
    _backGroundColor(MyColors::softPink),
    _foreGroundColor(MyColors::black),

    locked(true),
    seedMarked(false),

    delayEnabled(false)
{
    setState(State::POINT);
    setFocusPolicy(Qt::StrongFocus);
}

void Canvas::setSeed(QPoint point)
{
    seed = point;
    seedMarked = true;
}

void Canvas::resetSeed()
{
    seedMarked = false;
}

bool Canvas::isSeedMarked()
{
    return seedMarked;
}

void Canvas::setState(State state)
{
    this->state = state;
    this->locked = true;
    this->tempEdges.clear();

    switch (state)
    {
    case State::POINT:
        setCursor(MyCursors::pencil());
        break;

    case State::LINE:
        setCursor(MyCursors::cross());
        break;

    case State::SEED:
        setCursor(MyCursors::paintbucket());
        break;

    default:
        qDebug() << "unexpected canvas state";
        break;
    }

    update();
}

QColor Canvas::backGroundColor()
{
    return _backGroundColor;
}

QColor Canvas::foreGroundColor()
{
    return _foreGroundColor;
}

QColor Canvas::paintColor()
{
    return _paintColor;
}

void Canvas::setBackGroundColor(QColor color)
{
    _backGroundColor = color;
}

void Canvas::setForeGroundColor(QColor color)
{
    _foreGroundColor = color;
}

void Canvas::setPaintColor(QColor color)
{
    _paintColor = color;
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    painter.fillRect(0, 0, width(), height(), backGroundColor());

    for (auto it = paintPixels.keyValueBegin(); it != paintPixels.keyValueEnd(); it++)
    {
        painter.setPen((*it).second);
        painter.drawPoint((*it).first.first, (*it).first.second);
    }

    if (underMouse())
    for (auto it = tempEdges.keyValueBegin(); it != tempEdges.keyValueEnd(); it++)
    {
        QPoint p1 = {(*it).first.first.first, (*it).first.first.second};
        QPoint p2 = {(*it).first.second.first, (*it).first.second.second};

        painter.setPen((*it).second);
        painter.drawLine(p1, p2);
    }

    if (seedMarked)
    {
        painter.setPen(QPen(foreGroundColor(), 5));
        painter.drawPoint(seed);
    }
}

void Canvas::clear()
{
    locked = true;
    paintPixels.clear();
    tempEdges.clear();
    resetSeed();

    update();
}

void Canvas::addBorderPixel(int x, int y)
{
    paintPixels.insert({x, y}, foreGroundColor());
}

void Canvas::drawLine(QPoint p1, QPoint p2)
{
    drawAlgo::draw_line_bresenham_i(p1.x(), p1.y(), p2.x(), p2.y(),
                                    paintPixels, foreGroundColor());
    update();
}

void Canvas::lock()
{
    if (state != State::SEED)
    {
        drawLine(lastPoint, firstPoint);

        this->locked = true;
        tempEdges.clear();
        update();
    }
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);

    if (event->key() == Qt::Key_Shift)
    {
        if (!locked && state == State::LINE)
        {
            int x = cursor().pos().x() - mapToGlobal(pos()).x() + pos().x();
            int y = cursor().pos().y() - mapToGlobal(pos()).y() + pos().y();
            QPair<int, int> curPoint;

            tempEdges.clear();

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

            tempEdges.insert({ QPair<int, int>(lastPoint.x(), lastPoint.y()), curPoint }, foreGroundColor());

            update();
        }
    }
}

void Canvas::keyReleaseEvent(QKeyEvent *event)
{
    QWidget::keyReleaseEvent(event);

    if (event->key() == Qt::Key_Shift)
    {
        if (!locked && state == State::LINE)
        {
            int x = cursor().pos().x() - mapToGlobal(pos()).x() + pos().x();
            int y = cursor().pos().y() - mapToGlobal(pos()).y() + pos().y();
            QPair<int, int> curPoint(x, y);

            tempEdges.clear();

            tempEdges.insert({ QPair<int, int>(lastPoint.x(), lastPoint.y()), curPoint }, foreGroundColor());

            update();
        }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);

    if ((event->buttons() & Qt::LeftButton))
    {
        if (state == State::POINT)
        {
            drawLine(lastPoint, event->localPos().toPoint());
            update();

            lastPoint = event->localPos().toPoint();
        }
    }
    if (state == State::LINE && !locked)
    {
        QPair<int, int> curPoint = {event->localPos().toPoint().x(), event->localPos().toPoint().y()};

        tempEdges.clear();

        if (QGuiApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))
        {
            int x = curPoint.first;
            int y = curPoint.second;
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
        }

        tempEdges.insert({ QPair<int, int>(lastPoint.x(), lastPoint.y()), curPoint }, foreGroundColor());

        update();
    }

    update();
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);

    int x = event->localPos().toPoint().x();
    int y = event->localPos().toPoint().y();

    if (event->button() == Qt::LeftButton)
    {
        touchPoint(x, y);
    }
    else if (event->button() == Qt::RightButton)
    {
        lock();
    }
}

void Canvas::touchPoint(int x, int y)
{
    if (state == State::POINT)
    {
        firstPoint = {x, y};
        lastPoint = firstPoint;
        drawLine(lastPoint, lastPoint);
    }
    if (state == State::LINE)
    {
        if (QGuiApplication::keyboardModifiers().testFlag(Qt::ShiftModifier) & !locked)
        {
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
        }

        if (locked)
        {
            firstPoint = {x, y};
            lastPoint = firstPoint;
            locked = false;
        }

        drawLine(lastPoint, QPoint(x, y));

        lastPoint = QPoint(x, y);
        tempEdges.clear();
    }
    if (state == State::SEED)
    {
        setSeed({x, y});
    }

    update();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    mouseMoveEvent(event);
}

void Canvas::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);
    update();
}

void Canvas::paint()
{
    if (!seedMarked)
    {
        return;
    }

//    if (isFGColor(seed.x(), seed.y()))
//    {
//        return;
//    }

    QStack<QPoint> stack;

    stack.push(seed);

    while (!stack.isEmpty())
    {
        auto pixel = stack.pop();

        int xl, xr;
        int x = pixel.x();
        int y = pixel.y();

        x++;
        while ((isBGColor(x, y) || isPaintColor(x, y))  && x < width())
        {
            paintPixels.insert({x, y}, paintColor());
            x++;
        }
        xr = x - 1;
        x = pixel.x();

        x--;
        while ((isBGColor(x, y) || isPaintColor(x, y))  && 0 <= x)
        {
            paintPixels.insert({x, y}, paintColor());
            x--;
        }
        xl = x + 1;

        if (delayEnabled)
        {
            QTest::qWait(1);
            update();
        }

        paintCheckLine(xl, pixel.y() + 1, xr, stack);
        paintCheckLine(xl, pixel.y() - 1, xr, stack);

        paintPixels.insert({pixel.x(), pixel.y()}, paintColor());
    }

    seedMarked = false;
}

void Canvas::paintCheckLine(int x, int y, int xr, QStack<QPoint> &stack)
{
    int xMax = width(),
        yMax = height();

    int xMin = 0,
        yMin = 0;

    if (!(xMin <= x && x <= xMax))
    {
        return;
    }

    if (!(yMin <= y && y <= yMax))
    {
        return;
    }

    while (x <= xr)
    {
        bool flag = false;

        while (isBGColor(x, y) && (x <= xr) && x < xMax)
        {
            flag = true;
            x++;
        }

        if (flag)
        {
            if (x == xr && isBGColor(x, y))
            {
                stack.push({x, y});
            }
            else
            {
                stack.push({x - 1, y});
            }

            flag = false;
        }

        int xEnter = x;
        while (!isBGColor(x, y) && x < xr && x < xMax)
        {
            x++;
        }

        if (x == xEnter)
        {
            break;
        }
    }
}

bool Canvas::isBGColor(int x, int y)
{
    auto it = paintPixels.find({x, y});

    if (it == paintPixels.end())
    {
        return true;
    }

//    return *it == backGroundColor();
    return *it != paintColor() and *it != foreGroundColor();
}

bool Canvas::isFGColor(int x, int y)
{
    auto it = paintPixels.find({x, y});

    if (it == paintPixels.end())
    {
        return false;
    }

//    return *it == foreGroundColor();
    return *it != backGroundColor() and *it != paintColor();
}

bool Canvas::isPaintColor(int x, int y)
{
    auto it = paintPixels.find({x, y});

    if (it == paintPixels.end())
    {
        return false;
    }

//    return *it == paintColor();
    return *it != backGroundColor() and *it != foreGroundColor();
}

void Canvas::setDelay(bool flag)
{
    delayEnabled = flag;
}
