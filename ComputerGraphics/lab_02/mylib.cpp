#include "mylib.h"

bool isDouble(QString str)
{
    bool result;

    (void)str.toDouble(&result);

    return result;
}
