#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {

    /**< Buffer to store the current working directory */
    char *buf = NULL;

    /**< Pointer to store the return value of getcwd */
    char *ret_add = NULL;

    /**< Check if the program is called with no command-line arguments */
    if (argc != 1) {
        /**< Print a usage message */
        printf("Usage: %s only, no args needed\n", argv[0]);
        return -1;
    }

    /**< Determine the required buffer size for the current working directory */
    long size = pathconf(".", _PC_PATH_MAX);

    /**< Allocate memory for the buffer based on the determined size */
    if ((buf = (char *)malloc((size_t)size)) != NULL) {
        /**< Get the current working directory and store it in the buffer */
        ret_add = getcwd(buf, (size_t)size);

        /**< Check if getcwd failed */
        if (ret_add == NULL) {
            /**< Print an error message and free the allocated memory */
            perror("getcwd");
            free(buf);
            return -1;
        }

        /**< Print the current working directory */
        printf("%s\n", ret_add);

        /**< Free the allocated memory */
        free(buf);
    } else {
        /**< Print an error message if memory allocation fails */
        perror("malloc");
        return -1;
    }

    return 0;
}

