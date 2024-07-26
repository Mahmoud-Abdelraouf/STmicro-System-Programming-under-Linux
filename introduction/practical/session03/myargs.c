#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/** 
 * @brief The main function takes command-line arguments.
 * @param argc Number of arguments, including the program name.
 * @param argv Array of strings containing the arguments.
 */
int main(int argc, char* argv[])
{
    /**< Print the number of command-line arguments. */
    printf("Num of args = %d\n", argc);

    /**< Iterate through the command-line arguments and print each one. */
    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    /**< Return 0 to indicate successful execution. */
    return 0;
}
