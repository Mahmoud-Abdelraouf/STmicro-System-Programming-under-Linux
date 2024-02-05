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

    /**< Prepare arrays for the new program's arguments and environment variables. */
    char *new_program_argv[] = {NULL};
    char *new_program_envp[] = {NULL};

    /**< Wait for user input (press Enter). */
    getchar();

    /**< Execute the new program using execve. */
    execve(current_prog_argv[1], new_program_argv, new_program_envp);

    /**< If execve fails, print an error message. */
    printf("I am not in the mode of execution. Exec failed\n");

    /**< Return 0 to indicate successful execution. */
    return 0;
}
