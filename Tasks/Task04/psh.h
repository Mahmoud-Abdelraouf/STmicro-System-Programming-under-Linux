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

/**
 * @brief Parse the input string and tokenize it into arguments.
 *
 * This function parses the input string and tokenizes it into arguments based on spaces.
 * It dynamically allocates memory for the array of arguments and individual argument strings.
 *
 * @param input The input string to be parsed.
 * @param args Pointer to a pointer to store the array of arguments.
 * @param argCount Pointer to an integer to store the number of arguments.
 */
void parseInput(char *input, char ***args, int *argCount);

#endif /**< PSH_H */