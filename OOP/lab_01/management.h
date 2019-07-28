#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include "exit.h"
#include "object.h"
#include "handler.h"

#define DO_LEAVING      0
#define DO_LOADING      1
#define DO_SAVING       2
#define DO_TRASNLATE    3
#define DO_SCALING      4
#define DO_ROTATION     5
#define DO_RENDERING     6

typedef unsigned short hcommand_t;

int handle(Handler &handler, hcommand_t command);

int handle_load(Object &object, Handler &handler);

int handle_save(Object &object, Handler &handler);

int handle_translate(Object &object, Handler &handler);

int handle_scaling(Object &object, Handler &handler);

int handle_rotation(Object &object, Handler &handler);

int handle_render(Object &object, Handler &handler);

int handle_leave(Object &object);

#endif // MANAGEMENT_H
