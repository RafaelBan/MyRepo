#ifndef IO_H_
#define IO_H_

#include "IOBase.h"

#include <cstdio>

#define INPUTS IO::STDInputStream()
#define OUTPUTS IO::STDOutputStream()

class IO : public IOBase
{
public:
    virtual ~IO() = default;

    bool isValid() override;
    bool isEOF() override;

    IOBase &operator<<(const int &var) override;
    IOBase &operator<<(const double &var) override;
    IOBase &operator<<(const char *var) override;

    IOBase &operator>>(int &var) override;
    IOBase &operator>>(double &var) override;

    void rewind() override;

    static IO &STDInputStream();
    static IO &STDOutputStream();

protected:
    explicit IO();

    FILE *IOstream;

private:
    explicit IO(FILE *stdStream);

    bool isError;
};

#endif //IO_H_

