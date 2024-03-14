/**
 * @file variadic_functions.c
 * @brief Demonstrates variadic functions in C.
 * @see https://www.geeksforgeeks.org/variadic-functions-in-c/
 */

#include <stdarg.h>
#include <stdio.h>

/**
 * @brief Variadic function to add numbers.
 * @param n The number of arguments.
 * @param ... The variable number of integer arguments to be added.
 * @return The sum of the provided integers.
 */
int AddNumbers(int n, ...) {
    int Sum = 0;

    /**< Declaring pointer to the argument list */ 
    va_list ptr;

    /**< Initializing argument to the list pointer */ 
    va_start(ptr, n);

    for (int i = 0; i < n; i++)

        /**< Accessing current variable */ 
        /**< and pointing to the next one */ 
        Sum += va_arg(ptr, int);

    /**< Ending argument list traversal */ 
    va_end(ptr);

    return Sum;
}

/**
 * @brief Main function to demonstrate variadic functions.
 * @return Returns 0 upon successful execution.
 */
int main() {
    printf("\n\n Variadic functions: \n");

    /**< Variable number of arguments */ 
    printf("\n 1 + 2 = %d ", AddNumbers(2, 1, 2));

    printf("\n 3 + 4 + 5 = %d ", AddNumbers(3, 3, 4, 5));

    printf("\n 6 + 7 + 8 + 9 = %d ", AddNumbers(4, 6, 7, 8, 9));

    printf("\n");

    return 0;
}
