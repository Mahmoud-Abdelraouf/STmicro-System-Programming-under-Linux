# Session 02 Practical: Building `mycat` and `mycp`

In this session, we'll be working on building two simple programs, `mycat` and `mycp`. These programs demonstrate file operations using system calls in C. The goal is to familiarize ourselves with using the `man` pages to choose the appropriate syscalls for different tasks.

## `mycat` Program

### Usage
```bash
./mycat file_name
```

### Description
`mycat` is a simple file reading program that opens a file in read-only mode, reads its content, and writes it to the standard output.

### Implementation

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {

    /**< File descriptor, number of bytes read, number of bytes written */
    int fd, num_read, num_write;

    /**< Buffer to store read data */
    unsigned char buf[100];

    /**< Check if the correct number of arguments is provided */
    if (argc != 2) {
        printf("Usage: %s file_name\n", argv[0]);
        return -1;
    }

    /**< Open a file in read-only mode and store the file descriptor */
    fd = open(argv[1], O_RDONLY);

    /**< Check if the file is opened successfully */
    if (fd < 0) {
        printf("Could not open the file\n");
        return -1;
    }

    /**< Loop to read from the file and write to stdout */
    while ((num_read = read(fd, buf, 100)) != 0) {
        /**< Check if there is an error in reading from the file */
        if (num_read < 0) {
            printf("Could not read from this file\n");
            return -1;
        }

        /**< Write the read data to stdout */
        num_write = write(1, buf, num_read);
        /**< Check if there is an error in writing to stdout */
        if (num_write < 0) {
            printf("Could not write to stdout\n");
            return -1;
        }
    }

    /**< Close the file */
    close(fd);

    return 0;
}
```

## `mycp` Program

### Usage
```bash
./mycp file_src file_dest
```

### Description
`mycp` is a basic file copy program that opens a source file in read-only mode, creates a destination file (or truncates if exists) in write-only mode, and copies the content from the source to the destination.

### Implementation

```c
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
```

## Using

 `man` Pages

During the development of these programs, the `man` pages for various syscalls were referenced to understand their usage and choose the appropriate ones for file operations. For example:

- `man 2 open`: Provides information about the `open` syscall used for opening files.
- `man 2 read`: Describes the `read` syscall for reading data from a file.
- `man 2 write`: Describes the `write` syscall for writing data to a file.
- `man 2 close`: Provides details about closing file descriptors.

Always refer to the `man` pages for accurate and detailed information on system calls.