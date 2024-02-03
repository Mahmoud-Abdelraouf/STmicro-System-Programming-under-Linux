#include <stdio.h>
#include <string.h>

int main(void) {
    /**< Variable to store the string from the user */
    char str[1000] = {0};

    do {
        /**< Prompt the user to enter something */
        printf("Enter anything > ");

        /**< Read from the stdin using fgets() function */
        fgets(str, sizeof(str), stdin);

        /**< Remove the newline character from the input */
        str[strcspn(str, "\n")] = '\0';

        /**< Check if the input is equal to "exit" */
        if (strcmp(str, "exit") == 0) {
            /**< If so, print a farewell message */
            printf("Good Bye :)\n");
        } else {
            /**< If not, print the input */
            printf("%s\n", str);
        }

    /**< Continue the loop while the input is not equal to "exit" */
    } while (strcmp(str, "exit") != 0);

    return 0;
}
