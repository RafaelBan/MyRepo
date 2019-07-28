#ifndef EXIT_H
#define EXIT_H

#define __nedd_size_t
#include <stddef.h>

#define __EXIT_SUCCESS          0
#define __EXIT_OPEN_ERR         1
#define __EXIT_CLOSE_ERR        2
#define __EXIT_MEM_ERR          3
#define __EXIT_READ_ERR         4
#define __EXIT_WRITE_ERR        5
#define __EXIT_NULL_REQ         6

#define __EXIT_INVALID_DX       7
#define __EXIT_INVALID_DY       8
#define __EXIT_INVALID_DZ       9
#define __EXIT_INVALID_KX       10
#define __EXIT_INVALID_KY       11
#define __EXIT_INVALID_KZ       12
#define __EXIT_INVALID_AX       13
#define __EXIT_INVALID_AY       14
#define __EXIT_INVALID_AZ       15

#define __EXIT_EMPTY_DX         16
#define __EXIT_EMPTY_DY         17
#define __EXIT_EMPTY_DZ         18
#define __EXIT_EMPTY_KX         19
#define __EXIT_EMPTY_KY         20
#define __EXIT_EMPTY_KZ         21
#define __EXIT_EMPTY_AX         22
#define __EXIT_EMPTY_AY         23
#define __EXIT_EMPTY_AZ         24

#define __EXIT_EMPTY_INPUT      25
#define __EXIT_INVALID_INPUT    26

#define __EXIT_NULL_OBJECT      27

const char *error_string(int exit_code);

static const char* unknown_error = "Неизвестная ошибка";

static const char* error_strings[] = {
    "Неверная обработка кода ошибки",
    "Ошибка открытия потока",
    "Ошибка закрытия потока",
    "Некорректное обращение к памяти",
    "Нечитаемые данные",
    "Ошибка записи в поток",
    "Ошибка сегментации",

    "Заданное значение dx не является действительным числом",
    "Заданное значение dy не является действительным числом",
    "Заданное значение dz не является действительным числом",
    "Заданное значение kx не является действительным числом",
    "Заданное значение ky не является действительным числом",
    "Заданное значение kz не является действительным числом",
    "Заданное значение αx не является действительным числом",
    "Заданное значение αy не является действительным числом",
    "Заданное значение αz не является действительным числом",

    "Значение dx не задано",
    "Значение dy не задано",
    "Значение dz не задано",
    "Значение kx не задано",
    "Значение ky не задано",
    "Значение kz не задано",
    "Значение αx не задано",
    "Значение αy не задано",
    "Значение αz не задано",

    "Пустой ввод",
    "Некорректный ввод",

    "Объект не задан"
};

#endif // EXIT_H
