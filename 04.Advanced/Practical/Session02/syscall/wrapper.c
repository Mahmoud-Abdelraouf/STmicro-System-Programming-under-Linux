/**
 * @file wrapper.c
 * @brief This file demonstrates the concept of a wrapper function for printing a string.
 */

#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>

/**
 * @brief Wrapper function to print a string using either printf or write system call.
 * @param str The string to be printed.
 */
void print_wrapper(const char *str) {
    // Call the write system call directly to print the string to standard output (file descriptor 1)
    // syscall() function is used to directly invoke a system call
    // The write system call takes three arguments:
    // 1. File descriptor (1 for standard output)
    // 2. Pointer to the string to be printed
    // 3. Length of the string
    syscall(SYS_write, 1, str, strlen(str));
}

int main() {
    // Call the print_wrapper function to print "Hello World"
    print_wrapper("Hello World\n");
    return 0;
}
