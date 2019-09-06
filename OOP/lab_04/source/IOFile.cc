#include "IOFile.h"

IOFile::IOFile() :
    IO()
{
}

IOFile::IOFile(const char *filename, const char *mode) :
    IOFile()
{
    open(filename, mode);
}

IOFile::~IOFile()
{
    close();
}

bool IOFile::open(const char *filename, const char *mode)
{
    if (!IOstream)
    {
        IOstream = fopen(filename, mode);
        return IOstream != nullptr;
    }

    return false;
}

bool IOFile::close()
{
    if (IOstream)
    {
        int rc;

        rc = fclose(IOstream);
        if (rc != 0)
        {
            return false;
        }

        IOstream = nullptr;
        return true;
    }

    return false;
}

bool IOFile::isOpened()
{
    return IOstream;
}

