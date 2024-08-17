#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

typedef void (*command_func)(int, va_list);

void register_command(const char *command_name, command_func func);
void execute_command(const char *command_name, int argc, ...);
void list_commands();

#endif /* COMMAND_PROCESSOR_H */
