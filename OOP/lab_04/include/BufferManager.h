#ifndef BUFFER_H_
#define BUFFER_H_

#include <QTimer>
#include <QColor>
#include <QPixmap>
#include <QObject>
#include <QWidget>
#include <QPainter>

#define DEFAULT_UPDATE_TIME 15 // msec
#define DEFAULT_MAX_REQUEST_QUANTITY 15 // times

class BufferManager : public QObject
{
    Q_OBJECT;

public:
    explicit BufferManager(QWidget *owner, QPixmap *buffer, QColor bufferColor);

    void updateBufferSize();

private:
    int maxRequestsQuantity;
    int requestsCounter;
    int updateTime;

    QWidget *owner;
    QPixmap *buffer;
    QColor bufferColor;

private slots:
    void _updateBufferSize();
};

#endif // BUFFER_H_

