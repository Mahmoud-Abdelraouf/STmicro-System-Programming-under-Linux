#include "utils.h"
#include "dynamic_logger.h"

void print_sum(int argc, va_list args) {
    int sum = 0;
    for (int i = 0; i < argc; i++) {
        sum += va_arg(args, int);
    }
    log_message("Sum: %d", sum);
}

void print_max(int argc, va_list args) {
    int max = va_arg(args, int);
    for (int i = 1; i < argc; i++) {
        int value = va_arg(args, int);
        if (value > max) {
            max = value;
        }
    }
    log_message("Max: %d", max);
}

void print_min(int argc, va_list args) {
    int min = va_arg(args, int);
    for (int i = 1; i < argc; i++) {
        int value = va_arg(args, int);
        if (value < min) {
            min = value;
        }
    }
    log_message("Min: %d", min);
}
