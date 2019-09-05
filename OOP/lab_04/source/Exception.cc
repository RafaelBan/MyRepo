#include <Exception.h>

Exception::Exception(std::string mainInfo, std::string optInfo) :
    message(mainInfo + "\n")
{
    if (optInfo != "")
    {
        message += optInfo + "\n";
    }
}

Exception::Exception(std::string optInfo) :
    Exception("Unknown exception", optInfo)
{
}

const char *Exception::what() const noexcept
{
    return message.c_str();
}

