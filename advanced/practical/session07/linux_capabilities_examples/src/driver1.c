/**
 * @file driver1.c
 * @brief Example program demonstrating Linux capabilities.
 *
 * This program showcases how to use Linux capabilities to execute a service
 * with certain capabilities. It sets and gets capabilities for demonstration
 * purposes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/capability.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * @brief Main function of driver1 program.
 *
 * This function sets capabilities and then executes the service1 program.
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
  capget(header, NULL);
  header->pid = 0;
  capget(header, capdata);

  // Print the current effective, permitted, and inheritable capabilities
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
