#ifndef IO_BASE_H_
#define IO_BASE_H_

class IOBase
{
public:
    virtual ~IOBase() = default;

    virtual bool isValid() = 0;
    virtual bool isEOF() = 0;

    virtual IOBase &operator<<(const int &stdin) = 0;
    virtual IOBase &operator<<(const double &var) = 0;
    virtual IOBase &operator<<(const char *var) = 0;

    virtual IOBase &operator>>(int &var) = 0;
    virtual IOBase &operator>>(double &var) = 0;
};

#endif //IO_BASE_H_

