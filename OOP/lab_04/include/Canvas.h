#ifndef CANVAS_H_
#define CANVAS_H_

#include <QWidget>

#include <QPoint>
#include <QPixmap>
#include <QPainter>

#include "BufferManager.h"

class Canvas : public QWidget
{
    Q_OBJECT;

public:
    explicit Canvas(QWidget *parent = nullptr);

    void drawLine(QPoint p1, QPoint p2);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QColor bgColor;
    QPixmap buffer;

    BufferManager *bufferManager;

    void updateBufferSize();
};

#endif // CANVAS_H_

