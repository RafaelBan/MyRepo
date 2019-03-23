#include "colorpicker.h"

QString ColorProcess::ColorButtonStyle(QString color)
{
    return "* {"
           "border-style: solid; "
           "border-color: #424242; "
           "border-width: 2px;"
           "border-radius: 0px;"
           "padding: 10px 4px;"
           "background: " + color +
           ";}";
}
