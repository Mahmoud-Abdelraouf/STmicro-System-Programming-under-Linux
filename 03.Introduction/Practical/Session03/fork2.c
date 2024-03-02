#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/**< Global variables */
int x = 5;
int y;

/** 
 * @brief The main function takes command-line arguments.
 * @param argc Number of arguments, including the program name.
 * @param current_prog_argv Array of strings containing the arguments.
 */
int main(int argc, char *current_prog_argv[])
{
    /**< Print the number of command-line arguments. */
    printf("Num of args = %d\n", argc);

    /**< Local variable */
    int z = 10;

    /**< Iterate through the command-line arguments and print each one. */
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, current_prog_argv[i]);
    }

    /**< Wait for user input (press Enter). */
    getchar();

    /**< Print values before fork */
    printf("Before Fork: x= %d, y=%d, z=%d\n", x, y, z);

    /**< Increment values before fork */
    x++;
    y++;
    z++;

    /**< Print values after incrementing but before fork */
    printf("Before Fork (edit): x= %d, y=%d, z=%d\n", x, y, z);

    /**< Fork a new process */
    pid_t returned_pid = fork();

    if (returned_pid > 0) {
        /**< Parent process */
        printf("PARENT: My PID = %d, I have a new child and his PID = %d\n", getpid(), returned_pid);
        printf("PARENT: x= %d, y=%d, z=%d\n", x, y, z);
        x++; y++; z++;
        printf("PARENT: x= %d, y=%d, z=%d\n", x, y, z);
        getchar();
    } else if (returned_pid == 0) {
        /**< Child process */
        printf("CHILD: My PID = %d, My parent PID = %d\n", getpid(), getppid());
        printf("CHILD: x= %d, y=%d, z=%d\n", x, y, z);
        x++; y++; z++;
        x++; y++; z++;
        x++; y++; z++;
        printf("CHILD: x= %d, y=%d, z=%d\n", x, y, z);
        getchar();
    } else {
        /**< Forking error */
        printf("ERROR: I could not get a child\n");
    }

    /**< Return 0 to indicate successful execution. */
    return 0;
}
