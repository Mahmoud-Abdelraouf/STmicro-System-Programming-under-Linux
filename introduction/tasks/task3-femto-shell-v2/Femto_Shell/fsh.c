#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"  /**< Include the commands header */ 
#include "fsh.h" /**< Include the Femto Shell (fsh) header */

#define COMMAND_COUNT 4  /**< Number of supported commands */ 

/**< Array of supported commands */ 
char *supportedCommands[COMMAND_COUNT] = {"echo", "pwd", "cd", "exit"};

int main(int argc, char **argv) {
    char inputBuffer[100];

    while (1) {
        /**< Prompt user to enter a command */ 
        printf("Enter a command: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);

        /**< Remove the trailing newline character from the input */ 
        inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

        /**< Split the input into command and arguments */ 
        char *command = strtok(inputBuffer, " ");
        char *args[10];
        int i = 0;
        while (i < 10 && (args[i] = strtok(NULL, " ")) != NULL) {
            i++;
        }
        
        /**< Execute the command */ 
        executeCommand(command, args);
    }

    return 0;
}

/**< Function to execute the command based on the input */ 
void executeCommand(char *command, char *args[]) {
    if (strcmp(command, "pwd") == 0) {
        pwd();
    } else if (strcmp(command, "echo") == 0) {
        echo(args);
    } else if (strcmp(command, "cd") == 0) {
        if (args[0] != NULL) {
            cd(args[0]);
        } else {
            printf("cd: missing argument\n");
        }
    } else if (strcmp(command, "exit") == 0) {
        printf("Goodbye :)\n");
        exit(0);
    } else {
        printf("%s: command not found\n", command);
    }
}

