#include "displaywidget.h"\

DisplayWidget::DisplayWidget(QWidget *parent) :
    QWidget (parent),

    foregroundColor(MyColors::lightRed),
    backgroundColor(MyColors::lightBlack),

    _scalingRatio(500)
{

}

DisplayWidget::~DisplayWidget()
{

}

double DisplayWidget::scalingRatio()
{
    return  _scalingRatio;
}

void DisplayWidget::drawProcess()
{
    QPainter painter(this);

    painter.setPen(this->foregroundColor);
    painter.fillRect(0, 0, width(), height(), this->backgroundColor);

    for (auto line: this->lines)
    {
        painter.drawLine(line.first.x() + width() / 2, line.first.y() + height() / 2,
                         line.second.x() + width() / 2, line.second.y() + height() / 2);
    }
}

void DisplayWidget::clear()
{
    this->lines.clear();
}

void DisplayWidget::paintEvent(QPaintEvent *event)
{
    drawProcess();
}

void DisplayWidget::drawLine(QPoint first, QPoint second)
{
    this->lines.append({ first, second });
}
