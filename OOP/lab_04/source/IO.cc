#include "IO.h"

IO::IO() :
    IOstream(nullptr),
    isError(false)
{
}

IO::IO(FILE *stdStream) :
    IO()
{
    IOstream = stdStream;
}

IO &IO::STDInputStream()
{
    static IO inputs = IO(stdin);
    return inputs;
}

IO &IO::STDOutputStream()
{
    static IO outputs = IO(stdout);
    return outputs;
}

bool IO::isValid()
{
    return !isError && IOstream;
}

bool IO::isEOF()
{
    return feof(IOstream);
}

IOBase &IO::operator>>(int &var)
{
    if (!isValid())
    {
        return *this;
    }

    int rc;
    int temp;

    rc = fscanf(IOstream, "%d", &temp);

    if (rc != 1)
    {
        isError = true;
    }
    else
    {
        var = temp;
    }

    return *this;
}

IOBase &IO::operator>>(double &var)
{
    if (!isValid())
    {
        return *this;
    }

    int rc;
    double temp;

    rc = fscanf(IOstream, "%lf", &temp);

    if (rc != 1)
    {
        isError = true;
    }
    else
    {
        var = temp;
    }

    return *this;
}

IOBase &IO::operator<<(const int &var)
{
    if (!isValid())
    {
        return *this;
    }

    fprintf(IOstream, "%d", var);

    return *this;
}

IOBase &IO::operator<<(const double &var)
{
    if (!isValid())
    {
        return *this;
    }

    fprintf(IOstream, "%lf", var);

    return *this;
}

IOBase &IO::operator<<(const char *var)
{
    if (!isValid())
    {
        return *this;
    }

    fprintf(IOstream, "%s", var);

    return *this;
}

void IO::rewind()
{
    ::rewind(IOstream);
}

