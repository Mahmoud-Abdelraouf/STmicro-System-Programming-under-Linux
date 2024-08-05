/**
 * @file service1.c
 * @brief Example service program demonstrating Linux capabilities.
 *
 * This program is executed by driver1 or driver2 to demonstrate the effect of
 * capabilities on the executed process.
 */

#include <stdio.h> // Standard input/output library
#include <stdlib.h> // Standard library for memory allocation, process control, etc.
#include <sys/capability.h> // Library for manipulating POSIX capabilities
#include <sys/types.h>      // Data types used in system calls
#include <unistd.h>         // Standard symbolic constants and types

/**
 * @brief Main function of service1 program.
 *
 * This function retrieves and prints the current capabilities of the process.
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

  // Free allocated memory
  free(header);
  free(capdata);

  return 0;
}

