#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <exception>
#include <string>

class Exception : public std::exception
{
private:
    std::string message;

protected:
    Exception(std::string mainInfo, std::string optInfo);

public:
    Exception(std::string optInfo = "");
    virtual ~Exception() = default;

    virtual const char *
    what() const noexcept;
};

#define _EXCEPTION_FORK(NAME, MAIN_INFO) \
class NAME : public Exception \
{ \
public: \
    NAME(const char *optInfo) : \
        Exception(MAIN_INFO, optInfo) \
    {} \
}

#endif //EXCEPTION_H_

