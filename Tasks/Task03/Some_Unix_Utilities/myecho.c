#include <stdio.h>

int main(int argc, char **argv) {
    /**< Iterate through the command-line arguments starting from index 1 */
    for (int i = 1; i < argc; i++) {
        /**< Print each command-line argument followed by a space */
        printf("%s ", argv[i]);
    }

    /**< Print a newline character to separate the output */
    printf("\n");

    /**< Return 0 to indicate successful execution */
    return 0;
}

