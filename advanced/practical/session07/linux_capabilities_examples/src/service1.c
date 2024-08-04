/**
 * @file service1.c
 * @brief Example service program demonstrating Linux capabilities.
 *
 * This program is executed by driver1 or driver2 to demonstrate the effect of
 * capabilities on the executed process.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/capability.h>
#include <sys/types.h>
#include <unistd.h>

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
  capget(header, NULL);
  header->pid = 0;
  capget(header, capdata);

  // Print the current effective, permitted, and inheritable capabilities
  printf("effective=%x\n", capdata->effective);
  printf("permitted=%x\n", capdata->permitted);
  printf("inheritable=%x\n", capdata->inheritable);

  // Free allocated memory
  free(header);
  free(capdata);

  return 0;
}
