#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {

    /**< File descriptors, number of bytes read, number of bytes written */
    int fd_src, fd_dest, num_read, num_write;

    /**< Buffer to store read data */
    unsigned char buf[100];

    /**< Check if the correct number of arguments is provided */
    if (argc != 3) {
        printf("Usage: %s file_src file_dest\n", argv[0]);
        return -1;
    }

    /**< Open the source file in read-only mode and store the file descriptor */
    fd_src = open(argv[1], O_RDONLY);

    /**< Check if the source file is opened successfully */
    if (fd_src < 0) {
        printf("Could not open the source file\n");
        return -1;
    }

    /**< Open the destination file in write-only mode, create if not exists, truncate if exists, and store the file descriptor */
    fd_dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    /**< Check if the destination file is opened successfully */
    if (fd_dest < 0) {
        printf("Could not open the destination file\n");
        close(fd_src);
        return -1;
    }

    /**< Loop to read from the source file and write to the destination file */
    while ((num_read = read(fd_src, buf, 100)) != 0) {
        /**< Check if there is an error in reading from the source file */
        if (num_read < 0) {
            printf("Could not read from the source file\n");
            close(fd_src);
            close(fd_dest);
            return -1;
        }

        /**< Write the read data to the destination file */
        num_write = write(fd_dest, buf, num_read);

        /**< Check if there is an error in writing to the destination file */
        if (num_write < 0) {
            printf("Could not write to the destination file\n");
            close(fd_src);
            close(fd_dest);
            return -1;
        }
    }

    /**< Close the source and destination files */
    close(fd_src);
    close(fd_dest);

    return 0;
}

