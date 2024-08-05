/**
 * @file driver2.c
 * @brief Example program demonstrating Linux capabilities with inheritance.
 *
 * This program showcases how to use Linux capabilities to execute a service
 * with certain capabilities and setting inheritable capabilities.
 */

#include <stdio.h> // Standard input/output library
#include <stdlib.h> // Standard library for memory allocation, process control, etc.
#include <sys/capability.h> // Library for manipulating POSIX capabilities
#include <sys/types.h>      // Data types used in system calls
#include <unistd.h>         // Standard symbolic constants and types

/**
 * @brief Main function of driver2 program.
 *
 * This function sets inheritable capabilities and then executes the service1
 * program.
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
  printf("----  Setting 2 Inheritable capabilities\n");
  // Add the CAP_CHOWN and CAP_DAC_OVERRIDE capabilities to the inheritable set
  capdata->inheritable |= ((1 << CAP_CHOWN) | (1 << CAP_DAC_OVERRIDE));
  header->pid = 0;
  // Set the new capabilities for the process
  if (capset(header, capdata) == -1)
    perror("capset1");

  // Get and print the new capabilities
  capget(header, capdata);
  printf("effective=%x\n", capdata->effective);
  printf("permitted=%x\n", capdata->permitted);
  printf("inheritable=%x\n", capdata->inheritable);

  // Execute the service1 program
  printf("----  Exec service1\n");
  execlp("service1", "service1", (char *)0);

  // Free allocated memory
  free(header);
  free(capdata);

  return 0;
}

