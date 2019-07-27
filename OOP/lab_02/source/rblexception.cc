#include "rblexception.h"


rbl::UnknownException::UnknownException(std::string mainInfo, std::string optionalInfo) :
    message(mainInfo)
{
    if (optionalInfo != "")
    {
        message += "\n";
        message += optionalInfo;
    }
}

const char *
rbl::UnknownException::what() const noexcept
{
    return message.c_str();
}
