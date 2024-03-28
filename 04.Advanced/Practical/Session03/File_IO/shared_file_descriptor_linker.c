/**
 * @file SharedFileDescriptorLinker.c
 * @brief Implements a program that manages shared file descriptors between parent and child processes.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Main function
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return 0 on success, -1 on failure.
 */
int main(int argc, char *argv[]) {
    printf("Number of arguments: %d\n", argc); // Print the number of command-line arguments

    // Print command-line arguments
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]); // Print each command-line argument
    }

    getchar(); // Pause execution until Enter is pressed

    char *cmd = NULL; // Pointer to store user input
    size_t n = 0; // Size of the input buffer

    // Main shell loop
    while (1) {
        printf(">>>>>>> "); // Print the shell prompt
        int size = getline(&cmd, &n, stdin); // Read user input from stdin
        cmd[size - 1] = '\0'; // Remove newline character at the end of the input

        if (strlen(cmd) == 0) { // Skip empty commands
            continue;
        }

        // Open a file named "test.txt" for writing
        int fd = open("test.txt", O_WRONLY);
        if (fd < 0) {
            printf(">> Could not open the file\n"); // Print error message if file opening fails
            return -1; // Return failure code
        }
        printf(">> The file opened with fd = %d\n", fd); // Print file descriptor after successful opening

        // Set the file offset to a large value (100000 bytes from the end of the file)
        off_t newoff = lseek(fd, 100000, SEEK_END);
        write(fd, "Hello\n", 7); // Write "Hello" to the file

        // Fork a child process
        pid_t returned_pid = fork();
        if (returned_pid > 0) { // Parent process
            int wstatus;
            printf("PARENT: My PID = %d, I have a new child and his PID = %d\n", getpid(), returned_pid); // Print parent and child process IDs
            off_t offset_from_parent = lseek(fd, 0, SEEK_CUR);
            printf("PARENT: offset_from_parent = %ld, new offset = %ld\n", offset_from_parent, newoff); // Print file offsets

            wait(&wstatus); // Wait for the child process to terminate
            
            offset_from_parent = lseek(fd, 0, SEEK_CUR);
            printf("PARENT: after wait: offset_from_parent = %ld, new offset = %ld\n", offset_from_parent, newoff); // Print file offsets after waiting
        } else if (returned_pid == 0) { // Child process
            printf("CHILD: My PID = %d, My parent PID = %d\n", getpid(), getppid()); // Print child and parent process IDs

            getchar(); // Pause execution until Enter is pressed

            off_t offset_from_child = lseek(fd, 0, SEEK_CUR);
            printf("CHILD: offset_from_child = %ld, new offset = %ld\n", offset_from_child, newoff); // Print file offsets from child process

            // Prepare arguments for the new program (currently disabled)
            char *new_program_argv[] = { NULL };
            char *new_program_envp[] = { NULL };

            // Perform another seek operation in the file
            off_t newoff = lseek(fd, 5000, SEEK_END);
            offset_from_child = lseek(fd, 0, SEEK_CUR);
            printf("CHILD: another seek: offset_from_child = %ld, new offset = %ld\n", offset_from_child, newoff); // Print file offsets after seek
            
            return -1; // Return failure code
        } else { // Error handling
            printf("ERROR: Could not create a child process\n"); // Print error message if fork fails
        }

        free(cmd); // Free allocated memory
        cmd = NULL; // Reset pointer
        n = 0; // Reset size
    
    return 0; // Return success code
}
