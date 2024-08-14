#include <stdio.h>
#include <stdlib.h>

/**< Main function to move a file or directory. */
int main(int argc, char *argv[]) {
    /**< Check the number of arguments */
    if (argc != 3) {
        /**< Print usage message and return -1 */
        printf("Usage: %s <source> <destination>\n", argv[0]);
        return -1;
    }

    /**< Extract source and destination paths from command-line arguments */
    const char *source = argv[1];
    const char *destination = argv[2];

    /**< Perform the move operation */
    if (rename(source, destination) != 0) {
        /**< Handle move operation failure */
        perror("Error moving file");
        return -1;
    }

    /**< Print success message */
    printf("Successfully moved %s to %s\n", source, destination);

    /**< Return success status */
    return 0;
}
