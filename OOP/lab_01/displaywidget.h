#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>

#include <QPair>
#include <QList>
#include <QPainter>

#include "mycolors.h"

class DisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayWidget(QWidget *parent = nullptr);
    ~DisplayWidget();

    void drawLine(QPoint first, QPoint second);
    void drawLines();
    void clear();

    double scalingRatio();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QList< QPair< QPoint, QPoint > > lines;

    QColor foregroundColor;
    QColor backgroundColor;

    double _scalingRatio;

    void drawProcess();
};

#endif // DISPLAYWIDGET_H
