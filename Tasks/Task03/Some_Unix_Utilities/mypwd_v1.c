#include <stdio.h>
#include <unistd.h>


int main(int argc, char **argv)
{

    /**< Buffer to store the current working directory */
    char buf[100];

    /**< Pointer to store the return value of getcwd */
    char *ret_add = NULL;

    /**< Check if the program is called with no command-line arguments */
    if (argc != 1) {
	/**< Print a usage message */
	printf("Usage: %s only, no args needed\n", argv[0]);
	return -1;
    }

    /**< Get the current working directory and store it in the buffer */
    ret_add = getcwd(buf, sizeof(buf));

    /**< Check if getcwd failed */
    if (ret_add == NULL) {
	/**< Print an error message */
	perror("getcwd");
	return -1;
    }

    /**< Print the current working directory */
    printf("%s\n", ret_add);

    /**< Return success */
    return 0;
}
