#ifndef CHECK_ENTRY_H
#define CHECK_ENTRY_H

#include "exit.h"

#include <QLineEdit>

int entry_check_double(QLineEdit *entry);

int convert_exit_input_code(int exit_code, int empty_code, int invalid_code);

#endif // CHECK_ENTRY_H
