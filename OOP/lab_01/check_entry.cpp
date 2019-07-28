#include "check_entry.h"

int entry_check_double(QLineEdit *entry)
{
    int rc = __EXIT_SUCCESS;

    bool is_double;
    QString text;

    text = entry->text().simplified();

    if (text == "")
    {
        rc = __EXIT_EMPTY_INPUT;
    }

    if (rc == __EXIT_SUCCESS)
    {
        (void) text.toDouble(&is_double);

        if (!is_double)
        {
            rc = __EXIT_INVALID_INPUT;
        }
    }

    return rc;
}

int convert_exit_input_code(int exit_code, int empty_code, int invalid_code)
{
    if (exit_code == __EXIT_EMPTY_INPUT)
    {
        exit_code = empty_code;
    }

    if (exit_code == __EXIT_INVALID_INPUT)
    {
        exit_code = invalid_code;
    }

    return exit_code;
}
