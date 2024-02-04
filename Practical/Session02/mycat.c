#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{

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
