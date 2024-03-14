/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2023.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Supplementary program for Chapter 3 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef NOSYSCALL
/**
 * @brief A dummy function used for benchmarking when NOSYSCALL is defined.
 * @return Always returns 1.
 */
static int myfunc() { return 1; }
#endif

/**
 * @brief Main function to benchmark system calls.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return Returns EXIT_SUCCESS upon successful execution.
 */
int main(int argc, char *argv[])
{
    int numCalls = 10000000; // Number of times to call the system call or the dummy function

#ifdef NOSYSCALL
    printf("Calling normal function\n");
#else
    printf("Calling getppid()\n");
#endif

    // Loop to perform a large number of system calls or calls to the dummy function
    for (int j = 0; j < numCalls; j++)
#ifdef NOSYSCALL
        myfunc(); // Call the dummy function
#else
        getppid(); // Call the getppid() system call
#endif

    exit(EXIT_SUCCESS); // Exit the program with success status
}