#ifndef CANVAS_H
#define CANVAS_H

#include <QPainter>
#include <QPointF>
#include <QWidget>
#include <QColor>
#include <QList>

#include <cmath>

class Canvas;

const double EPSILON = 10e-7;

static bool isEqual(double num1, double num2)
{
    return (abs(num1 - num2) < EPSILON);
}

namespace MyColors
{
    const QColor gBackground = QColor("#eeeeee");
    const QColor red = QColor("#d50000");
    const QColor green = QColor("#00bc6c");
    const QColor blue = QColor("#2962ff");
    const QColor black = QColor("#000000");
    const QColor pink = QColor("#e91e63");
}

namespace cartesian
{
    const int ILevels = 255;

    namespace straight
    {
        extern bool doFullSmooth;

        class drawTask
        {
        private:
            void (*drawLine)(QPoint p1, QPoint p2, QPainter &painter);
            int x1, y1;
            int x2, y2;

            QColor color;

        public:
            explicit drawTask(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0,
                              QColor color = MyColors::black,
                              QString method = "standard");

            void draw(QPainter &painter, Canvas *canvas = nullptr);
        };

        void standard(QPoint p1, QPoint p2, QPainter &painter);

        void dda(QPoint p1, QPoint p2, QPainter &painter);

        void bresenhamr(QPoint p1, QPoint p2, QPainter &painter);
        void bresenhami(QPoint p1, QPoint p2, QPainter &painter);
        void bresenhama(QPoint p1, QPoint p2, QPainter &painter);

        void wu(QPoint p1, QPoint p2, QPainter &painter);
    }
}

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    QColor getBGColor(void);
    void setBGColor(QColor);

    QColor getLineColor(void);
    void setLineColor(QColor);

    QPoint initQPoint(int cart_x, int cart_y);

    void addTask(cartesian::straight::drawTask task);
    void clearTasks();

    QPainter &getPainter();

private:
    QPainter *painterPTR;

    QColor bgColor;
    QColor lineColor;

    QList< cartesian::straight::drawTask > tasks;

    void draw();

protected:
    void paintEvent(QPaintEvent *);
};

static inline double degToRad(double degrees)
{
    return (M_PI / 180) * degrees;
}

static inline double radToDeg(double radians)
{
    return (180 / M_PI) * radians;
}

#endif // CANVAS_H
