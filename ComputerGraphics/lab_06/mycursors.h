#ifndef MYCURSORS_H
#define MYCURSORS_H

#include <QPixmap>
#include <QCursor>

namespace MyCursors
{
    static inline QCursor
    pencil()
    {
        QPixmap cursor_pixmap(":/base/pencil.png");
        QCursor cursor(cursor_pixmap, 0, cursor_pixmap.height() - 1);

        return cursor;
    }

    static inline QCursor
    paintbucket()
    {
        QPixmap cursor_pixmap(":/base/paintbucket.png");
        QCursor cursor(cursor_pixmap, cursor_pixmap.width() - 2, cursor_pixmap.height() - 1);

        return cursor;
    }

    static inline QCursor
    cross()
    {
        QCursor cursor;
        cursor.setShape(Qt::CrossCursor);

        return cursor;
    }
}

#endif // MYCURSORS_H
