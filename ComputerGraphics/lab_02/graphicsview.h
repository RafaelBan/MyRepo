#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QPainter>
#include <QPointF>
#include <QWidget>
#include <QList>

#include "figure.h"

class GraphicsView : public QWidget
{
    Q_OBJECT

private:

    double dx, dy;
    double scalingK;
    QList<Figure> figures;

    void draw();
    void drawFigure(Figure figure);
    void setScalingK();

public:
    explicit GraphicsView(QWidget *parent = nullptr);
    ~GraphicsView();

    void setFigures(QList<Figure>);
    QList<Figure> getFigures(void);

    double xCartToDisp(double xC);
    double yCartToDisp(double yC);
    double xDispToCart(double xD);
    double yDispToCart(double yD);

    double dX();
    double dY();
    double ScalingK();

protected:
    void paintEvent(QPaintEvent *event);
};

namespace MyColors
{
    const QColor gBackground = QColor("#eeeeee");
    const QColor red = QColor("#d50000");
    const QColor green = QColor("#00bc6c");
    const QColor blue = QColor("#2962ff");
    const QColor black = QColor("#000000");
    const QColor pink = QColor("#e91e63");
}

#endif // GRAPHICSVIEW_H
