/**
 * @file createfile.c
 * @brief A program to create a file with a specified size.
 */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 

/**
 * @brief Main function of the program.
 * 
 * This function creates a file with the specified size.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return 0 if the program exits successfully, -1 otherwise.
 */
int main(int argc, char *argv[]) {
    /**< Check if the number of command-line arguments is correct */ 
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <size> OR %s <size> <filename>\n", argv[0], argv[0]);
        return -1;
    }

    off_t size;
    const char *filename;

    /**< Check if the size is the first argument */ 
    if (atoi(argv[1]) > 0) {
        size = atoi(argv[1]);
        filename = argv[2];
    }
    /**< Check if the size is the second argument */ 
    else if (atoi(argv[2]) > 0) {
        size = atoi(argv[2]);
        filename = argv[1];
    }
    else {
        fprintf(stderr, "Invalid size: %s\n", argv[1]);
        return -1;
    }

    /**< Check if the size is valid */ 
    if (size <= 0) {
        fprintf(stderr, "Invalid size: %ld\n", (long)size);
        return -1;
    }

    /**< Open the file for writing (or create if it doesn't exist) */
    int fd = open(filename, O_WRONLY | O_CREAT, 0644);
    if(fd == -1) {
        perror("open");
        return -1;
    }

    /**< Set the size of the file using the truncate system call */
    if (ftruncate(fd, size) == -1) {
        perror("ftruncate");
        close(fd);
        return -1;
    }

    /**< Close the file */
    close(fd);

    printf("File '%s' created with size %ld bytes\n", filename, (long)size);

    return 0;
}

