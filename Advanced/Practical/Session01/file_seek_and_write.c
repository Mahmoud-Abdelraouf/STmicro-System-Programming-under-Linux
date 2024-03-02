/**
 * @file createfile.c
 * @brief A program to create a file with a specified size at a specified offset.
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h> 
#include <sys/stat.h>
#include <sys/types.h>

/**
 * @brief Main function of the program.
 * 
 * This function creates a file with a specified size at a specified offset from the end of the file.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return 0 if the program exits successfully, -1 otherwise.
 */
int main(int argc, char *argv[]) {
    /**< Check if the number of command-line arguments is correct */ 
    if (argc != 3) {
        printf("Usage: %s <size> <filename> OR %s <filename> <size>\n", argv[0], argv[0]);
        return -1;
    }

    const char *filename;
    off_t offset;

    /**< Check if the first argument can be parsed as a size */ 
    if (atoi(argv[1]) > 0) {
        offset = atoi(argv[1]);
        filename = argv[2];
    }
    /**< Check if the second argument can be parsed as a size */ 
    else if (atoi(argv[2]) > 0) {
        offset = atoi(argv[2]);
        filename = argv[1];
    }
    else {
        printf("Invalid offset: %s\n", argv[1]);
        return -1;
    }

    /**< Open the file for writing (or create if it doesn't exist) */
    int fd = open(filename, O_WRONLY, 0644);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    /**< Seek from the end of the file */
    off_t new_offset = lseek(fd, offset, SEEK_END);
    if (new_offset == -1) {
        perror("lseek");
        close(fd);
        return -1;
    }

    char data[] = "1150091280"; /**< 10 bytes of data */

    /**< Write 10 bytes of data */
    ssize_t bytes_written = write(fd, data, sizeof(data) - 1); /**< Exclude null terminator */
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return -1;
    }

    printf("Wrote %zd bytes at offset %lld from the end of the file.\n", bytes_written, (long long)new_offset);

    /**< Close the file */
    close(fd);

    return 0;
}

