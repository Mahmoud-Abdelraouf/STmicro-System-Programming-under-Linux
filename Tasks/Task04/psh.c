#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "psh.h"

int main() {
    char *inputBuffer = NULL;
    size_t bufferSize = 0;

    while (1) {
        /**< Prompt user to enter a command */ 
        getUserInput(&inputBuffer, &bufferSize);

        /**< Skip processing if input is empty. */
        if (strlen(inputBuffer) == 0) {
            continue;
        }

        /**< Extract the command and arguments */ 
        char **args = NULL;
        int argCount = 0;
        parseInput(inputBuffer, &args, &argCount);

        /**< Execute the command with the arguments */ 
        int ret_val = executeCommand(args[0], args);
        /**< This Command Not Internal */
        if(ret_val != 0) {
            /**< Fork a new process to execute the command. */
            pid_t returned_pid = fork();

            if (returned_pid > 0) { /**< Parent process. */
            int wstatus;

            /**< Wait for the child process to finish. */
            wait(&wstatus);
            } else if (returned_pid == 0) { /**< Child process. */
                /**< Execute the specified command. */
                if (execvp(args[0], args) == -1) {
                    /**< Exec failed. Print an error message and return. */
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
            } else {
                /**< Fork failed. Print an error message. */
                printf("ERROR: I could not get a child\n");
            }

        } else {
            printf("%s: command not found\n", args[0]);
            return -1;
        }
        
        /**< Free the allocated memory for arguments */ 
        for (int i = 0; i < argCount; i++) {
            free(args[i]);
        }
        free(args);
    }

    /**< Free the allocated memory for inputBuffer */ 
    free(inputBuffer);

    return 0;
}

/**< Function to parse the input string and tokenize it into arguments */ 
void parseInput(char *input, char ***args, int *argCount) {
    *argCount = 0;
    int inArgument = 0;

    /**< Count the number of arguments */ 
    for (size_t i = 0; i < strlen(input); i++) {
        if (input[i] == ' ') {
            /**< If currently in an argument, increment the counter */ 
            inArgument = 0;
        } else {
            /**< If not in an argument, set the flag */ 
            if (!inArgument) {
                inArgument = 1;
                (*argCount)++;
            }
        }
    }

    /**< Allocate memory for the array of arguments */ 
    *args = malloc((*argCount + 1) * sizeof(char *));
    if (*args == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    /**< Tokenize the input and store the arguments */ 
    int argIndex = 0;
    char *token = strtok(input, " ");
    while (token != NULL) {
        (*args)[argIndex] = strdup(token);
        if ((*args)[argIndex] == NULL) {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        argIndex++;
        token = strtok(NULL, " ");
    }
    (*args)[argIndex] = NULL; /**< Null-terminate the array */ 
}

/**< Function to execute the command based on the input */ 
int executeCommand(char *command, char *args[]) {
    if (strcmp(command, "pwd") == 0) {
        pwd();
    } else if (strcmp(command, "echo") == 0) {
        echo(args);
    } else if (strcmp(command, "cd") == 0) {
        if (args[1] != NULL) {
            cd(args[1]);
        } else {
            printf("cd: missing argument\n");
        }
    } else if (strcmp(command, "exit") == 0) {
        printf("Goodbye :)\n");
        exit(0);
    } else {
        return -1;
    }
    return 0;
}

/**< Function to ask the user to enter the commands (Prompt) */
void getUserInput(char **inputBuffer, size_t *bufferSize) {
    printf("Enter a command: ");
    ssize_t inputSize = getline(inputBuffer, bufferSize, stdin);
    if (inputSize == -1) {
        perror("getline");
        exit(EXIT_FAILURE);  /**< Exit if getline fails */ 
    }
    (*inputBuffer)[strcspn(*inputBuffer, "\n")] = '\0';  /**< Remove newline character */ 
}
