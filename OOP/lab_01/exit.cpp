#include "exit.h"

const char *error_string(int exit_code)
{
    if (size_t(exit_code) >= sizeof (error_strings) / sizeof (char *))
    {
        return unknown_error;
    }

    return error_strings[exit_code];
}
