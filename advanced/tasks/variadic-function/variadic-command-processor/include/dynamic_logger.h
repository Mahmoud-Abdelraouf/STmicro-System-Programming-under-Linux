#ifndef DYNAMIC_LOGGER_H
#define DYNAMIC_LOGGER_H

#include <stdarg.h>
#include <stdio.h>
#include <pthread.h>

void init_logger();
void log_message(const char *format, ...);
void cleanup_logger();

#endif /* DYNAMIC_LOGGER_H */
