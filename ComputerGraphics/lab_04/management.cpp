#include "management.h"
#include <QDebug>

void handle()
{
    control::hcommand_t command = control::Handler::getCommand();
    control::Handler::setCommand(control::DO_WAITING);

    switch (command)
    {
    case control::DO_WAITING:
        break;

    case control::DO_CIRCLE:
        break;

    case control::DO_CCONC:
        break;

    case control::DO_ELLIPSE:
        break;

    case control::DO_ECONC:
        break;

    default:
        qDebug() << "Unknown command";
        break;
    }
}
