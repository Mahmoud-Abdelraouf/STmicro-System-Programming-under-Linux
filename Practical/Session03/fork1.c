#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/** 
 * @brief The main function takes command-line arguments.
 * @param argc Number of arguments, including the program name.
 * @param current_prog_argv Array of strings containing the arguments.
 */
int main(int argc, char* current_prog_argv[])
{
    /**< Print the number of command-line arguments. */
    printf("Num of args = %d\n", argc);

    /**< Iterate through the command-line arguments and print each one. */
    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, current_prog_argv[i]);
    }

    /**< Wait for user input (press Enter). */
    getchar();

    /**< Fork the process to create a new child process. */
    pid_t returned_pid = fork();

    /**< Check the return value of fork to determine if it's the parent or child. */
    if (returned_pid > 0)
    {
        /**< Parent process: */
        printf("PARENT: My PID = %d, I have a new child, and his PID = %d\n", getpid(), returned_pid);

        /**< Wait for user input (press Enter). */
        getchar();
    }
    else if (returned_pid == 0)
    {
        /**< Child process: */
        printf("CHILD: My PID = %d, My parent PID = %d\n", getpid(), getppid());

        /**< Wait for user input (press Enter). */
        getchar();
    }
    else
    {
        /**< Fork failed: */
        printf("ERROR: I could not get a child\n");
    }

    /**< Return 0 to indicate successful execution. */
    return 0;
}
