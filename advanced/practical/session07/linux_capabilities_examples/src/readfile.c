/**
 * @file readfile.c
 * @brief Program to change file ownership and read a file.
 *
 * This program changes the ownership of a file and reads its contents.
 */

#include <fcntl.h> // File control options
#include <stdio.h> // Standard input/output library
#include <stdlib.h> // Standard library for memory allocation, process control, etc.
#include <sys/stat.h>  // Definitions for file status
#include <sys/types.h> // Data types used in system calls
#include <unistd.h>    // Standard symbolic constants and types

#define BUFSIZE 1000 // Define buffer size for reading file

/**
 * @brief Main function of readfile program.
 *
 * This function changes the ownership of a file and reads its contents.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Exit status of the program.
 */
int main(int argc, char **argv) {
  int fd, n;         // File descriptor and read byte count
  char buf[BUFSIZE]; // Buffer to store file content

  // Change the ownership of the file specified in argv[1] to user ID 1000 and
  // group ID 1000
  if (chown(argv[1], 1000, 1000)) {
    // If chown fails, print an error message
    printf("Couldn't change owner\n");
  } else {
    // If chown succeeds, print a success message
    printf("change owner succeeded\n");
  }

  // Open the file specified in argv[2] in read-only mode
  if ((fd = open(argv[2], O_RDONLY)) == -1) {
    // If open fails, print an error message and exit
    printf("Error opening %s\n", argv[2]);
    exit(1);
  }

  // Read the file in chunks of BUFSIZE and write to standard output (usually
  // the terminal)
  while ((n = read(fd, buf, BUFSIZE)) > 0) {
    // Write the read bytes to standard output
    write(1, buf, n);
  }

  // If there was an error reading the file, print an error message
  if (n < 0) {
    printf("error reading input file\n");
  }

  // Close the file descriptor
  close(fd);

  return 0; // Return 0 to indicate successful completion
}

