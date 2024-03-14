/**
 * @file open_get_different_file_desc.c
 * @brief Demonstrates that opening the same file with the same flags using two separate `open()` calls results in different file descriptors.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define RET_STATUS 0 /**< Return status code indicating success. */

/**
 * @brief Main function
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return RET_STATUS indicating success or failure.
 */
int main(int argc, char* argv[]) {
    int fd, num_write, fd2; /**< File descriptors and number of bytes written. */
    unsigned char buf[10] = {66, 67, 68, 69, 66, 67, 68, 69, 66, 67}; /**< Data buffer. */

    // Open the file specified by the user's command-line argument in write-only mode
    fd = open(argv[1], O_WRONLY);
    if (fd < 0) {
        printf(">> Could not open the file\n");
        return -1;
    }
    printf(">> the file opened with fd = %d\n", fd);

    // Open the same file again using a different file descriptor
    fd2 = open(argv[1], O_WRONLY);
    if (fd2 < 0) {
        printf(">> Could not open the file\n");
        return -1;
    }
    printf(">> the file opened with fd2 = %d\n", fd2);

    // Set the file offset to a large value (100000 bytes from the end of the file) using the first file descriptor
    off_t newoff = lseek(fd, 100000, SEEK_END);

    // Duplicate the first file descriptor, obtaining a new file descriptor (new_fd) pointing to the same open file description
    int new_fd = dup(fd);

    // Retrieve the current file offset for the duplicated file descriptor (new_fd)
    off_t offset_from_newfd = lseek(new_fd, 0, SEEK_CUR);

    // Print the offset from the duplicated file descriptor and the offset set using lseek() with the first file descriptor
    printf("offset_from_newfd = %ld, newofffest = %ld\n", offset_from_newfd, newoff);

    // Retrieve the current file offset for the second file descriptor (fd2)
    off_t offset_from_fd2 = lseek(fd2, 0, SEEK_CUR);

    // Print the offset from the second file descriptor and the offset set using lseek() with the first file descriptor
    printf("offset_from_fd2 = %ld, newofffest = %ld\n", offset_from_fd2, newoff);

    // Write data to the file using the first file descriptor
    num_write = write(fd, buf, 10);
    printf(">> the file is written with %u bytes\n", num_write);

    // Close both file descriptors
    close(fd);
    close(fd2);

    return RET_STATUS;
}
