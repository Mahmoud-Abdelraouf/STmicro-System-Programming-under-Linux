/**
 * @file service2.c
 * @brief Example service program demonstrating advanced Linux capabilities.
 *
 * This program demonstrates the use of ambient capabilities and setting
 * capabilities during runtime.
 */

#include <stdio.h> // Standard input/output library
#include <stdlib.h> // Standard library for memory allocation, process control, etc.
#include <sys/capability.h> // Library for manipulating POSIX capabilities
#include <sys/prctl.h>      // Library for manipulating process attributes
#include <sys/types.h>      // Data types used in system calls
#include <unistd.h>         // Standard symbolic constants and types

/**
 * @brief Main function of service2 program.
 *
 * This function sets ambient capabilities and then executes another program.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Exit status of the program.
 */
int main(int argc, char **argv) {
  // Define capability header and data structures
  cap_user_header_t header;
  cap_user_data_t capdata;

  // Allocate memory for the header and data structures
  header = malloc(sizeof(*header));
  capdata = malloc(sizeof(*capdata));

  // Get current capabilities
  // The first call to capget initializes the header structure
  capget(header, NULL);
  // Set the PID to 0 to refer to the current process
  header->pid = 0;
  // The second call to capget retrieves the capabilities into capdata
  capget(header, capdata);

  // Print the current effective, permitted, and inheritable capabilities
  printf("effective=%x\n", capdata->effective);     // Effective capabilities
  printf("permitted=%x\n", capdata->permitted);     // Permitted capabilities
  printf("inheritable=%x\n", capdata->inheritable); // Inheritable capabilities

  // Set inheritable capabilities
  capdata->inheritable |= ((1 << CAP_CHOWN) | (1 << CAP_DAC_OVERRIDE));
  // Use the process ID (PID) as a negative value to set capabilities for the
  // current process
  header->pid = getpid() * (-1);
  // Set the new capabilities for the process
  capset(header, capdata);

  // Set ambient capabilities
  // Raise the CAP_CHOWN capability in the ambient set
  prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, CAP_CHOWN, 0, 0);
  // Raise the CAP_DAC_OVERRIDE capability in the ambient set
  prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, CAP_DAC_OVERRIDE, 0, 0);
  // Allow capabilities to be retained across execve system calls
  prctl(PR_SET_KEEPCAPS, 1);

  // Print capabilities after setting PR_SET_KEEPCAPS
  printf("-----------------  after PR_SET_KEEPCAPS\n");
  capget(header, capdata);
  printf("effective=%x\n", capdata->effective);
  printf("permitted=%x\n", capdata->permitted);
  printf("inheritable=%x\n", capdata->inheritable);

  // Fork and exit parent process
  if (fork())
    exit(0);

  // Print capabilities before exec
  printf("-----------------  before exec\n");
  capget(header, capdata);
  printf("effective=%x\n", capdata->effective);
  printf("permitted=%x\n", capdata->permitted);
  printf("inheritable=%x\n", capdata->inheritable);

  // Execute the readfile program
  execlp("../obj/readfile", "readfile", "../test_files/test1.txt",
         "../test_files/test2.txt", (char *)0);

  // Free allocated memory
  free(header);
  free(capdata);

  return 0;
}
