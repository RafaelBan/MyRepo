#ifndef CANVAS_H_
#define CANVAS_H_

#include <QWidget>

#include <QPoint>
#include <QPixmap>
#include <QPainter>

#include <QList>
#include "DrawObject.h"
#include "CanvasLine.h"

#include <memory>

class Canvas : public QWidget
{
    Q_OBJECT;

public:
    explicit Canvas(QWidget *parent = nullptr);

    void drawLine(QPoint p1, QPoint p2, QColor color = "#000000");
    void setBackgroundColor(QColor color);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QColor bgColor;

    QList< std::shared_ptr<DrawObject> > drawObjects;
};

#endif // CANVAS_H_

