/**
 * @file service2.c
 * @brief Example service program demonstrating advanced Linux capabilities.
 *
 * This program demonstrates the use of ambient capabilities and setting
 * capabilities during runtime.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/capability.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <unistd.h>

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
  capget(header, NULL);
  header->pid = 0;
  capget(header, capdata);

  // Print the current effective, permitted, and inheritable capabilities
  printf("effective=%x\n", capdata->effective);
  printf("permitted=%x\n", capdata->permitted);
  printf("inheritable=%x\n", capdata->inheritable);

  // Set inheritable capabilities
  capdata->inheritable |= ((1 << CAP_CHOWN) | (1 << CAP_DAC_OVERRIDE));
  header->pid = getpid() * (-1);
  capset(header, capdata);

  // Set ambient capabilities
  prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, CAP_CHOWN, 0, 0);
  prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, CAP_DAC_OVERRIDE, 0, 0);
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
  execlp("readfile", "readfile", "test1", "test2", (char *)0);

  // Free allocated memory
  free(header);
  free(capdata);

  return 0;
}
