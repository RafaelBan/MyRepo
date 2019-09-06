#ifndef IO_FILE_H_
#define IO_FILE_H_

#include "IO.h"
#include <cstdio>

class IOFile : public IO
{
public:
    IOFile();
    IOFile(const char *filename, const char *mode);
    ~IOFile() override;

    bool open(const char *filename, const char *mode);
    bool close();

    bool isOpened();
};

#endif //IO_FILE_H_

