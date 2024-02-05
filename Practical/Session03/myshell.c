#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/** 
 * @brief The main function takes command-line arguments.
 * @param argc Number of arguments, including the program name.
 * @param current_prog_argv Array of strings containing the arguments.
 */
int main(int argc, char *current_prog_argv[])
{
    /**< Print the number of command-line arguments. */
    printf("Num of args = %d\n", argc);

    /**< Iterate through the command-line arguments and print each one. */
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, current_prog_argv[i]);
    }

    /**< Placeholder for command input. */
    char *cmd = NULL;
    /**< Placeholder for input buffer size. */
    size_t n = 0;

    /**< Infinite loop to get user input and execute commands. */
    while (1) {
        /**< Display prompt for command input. */
        printf(">>>>>>> ");
        
        /**< Read user input. */
        int size = getline(&cmd, &n, stdin);
        cmd[size - 1] = 0;
        
        /**< Skip processing if input is empty. */
        if (strlen(cmd) == 0)
            continue;

        /**< Fork a new process to execute the command. */
        pid_t returned_pid = fork();

        if (returned_pid > 0) {
            /**< Parent process. */
            int wstatus;
            printf("PARENT: My PID = %d, I have a new child and his PID = %d\n", getpid(), returned_pid);
            
            /**< Wait for the child process to finish. */
            wait(&wstatus);
        } else if (returned_pid == 0) {
            /**< Child process. */
            printf("CHILD: My PID = %d, My parent PID = %d\n", getpid(), getppid());
            getchar();

            /**< Placeholder for new program arguments and environment. */
            char *new_program_argv[] = {NULL};
            char *new_program_envp[] = {NULL};

            /**< Execute the specified command. */
            execve(cmd, new_program_argv, new_program_envp);

            /**< Exec failed. Print an error message and return. */
            printf("I am not in the mode of execution. Exec failed\n");

            return -1;
        } else {
            /**< Fork failed. Print an error message. */
            printf("ERROR: I could not get a child\n");
        }

        /**< Free the allocated memory for the command. */
        free(cmd);
        cmd = NULL;
        n = 0;
    }

    /**< Return 0 to indicate successful execution. */
    return 0;
}
