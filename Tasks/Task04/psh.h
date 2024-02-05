#ifndef PSH_H
#define PSH_H

/**
 * @brief Function to execute the command based on the input.
 *
 * This function searches for the command in the sorted array of supported commands
 * and executes the corresponding function if the command is found.
 *
 * @param command The command to be executed.
 * @param args An array of command arguments.
 */
void executeCommand(char *command, char *args[]);

void parseInput(char *input, char ***args, int *argCount);


#endif /**< PSH_H */