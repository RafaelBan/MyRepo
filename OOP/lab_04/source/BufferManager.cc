#include "BufferManager.h"
#include <memory>

BufferManager::BufferManager(QWidget *owner, QPixmap *buffer, QColor bufferColor) :
    maxRequestsQuantity(DEFAULT_MAX_REQUEST_QUANTITY),
    requestsCounter(0),
    updateTime(DEFAULT_UPDATE_TIME),

    owner(owner),
    buffer(buffer),
    bufferColor(bufferColor)
{
}

void BufferManager::updateBufferSize()
{
    requestsCounter++;

    if (requestsCounter == 1)
    {
        QTimer::singleShot(updateTime, this, SLOT(_updateBufferSize()));
    }

    if (requestsCounter > maxRequestsQuantity)
    {
        _updateBufferSize();
    }
}

void BufferManager::_updateBufferSize()
{
    requestsCounter = 0;

    QPixmap newBuffer(owner->size());

    if (newBuffer.isNull())
    {
        return;
    }

    auto painter = std::make_unique<QPainter>(&newBuffer);

    painter->fillRect(0, 0, owner->width(), owner->height(), bufferColor);
    painter->drawPixmap(0, 0, owner->width(), owner->height(), *buffer,
                        0, 0, owner->width(), owner->height());

    *buffer = newBuffer;

    owner->update();
}

