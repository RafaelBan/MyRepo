#ifndef GINDICATOR_H
#define GINDICATOR_H

#include <QWidget>
#include <QPainter>

class GIndicator : public QWidget
{
    Q_OBJECT

    enum State
    {
        DOWN = -1,
        NONE = 0,
        UP = 1
    };

public:
    GIndicator(QWidget *parent = nullptr);

    void setBackground(QColor color);
    QColor getBackground();

    void setForeground(QColor color);
    QColor getForeground();

    void setDirection(int dir);

private:
    State state;

    QColor background;
    QColor foreground;

    void paintEvent(QPaintEvent *e) override;
};

#endif // GINDICATOR_H
