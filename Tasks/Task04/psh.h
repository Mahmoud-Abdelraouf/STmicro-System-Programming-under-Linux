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
 *
 * Example usage:
 * @code{.c}
 * char *inputString = "command arg1 arg2 arg3";
 * char **args = NULL;
 * int argCount = 0;
 * parseInput(inputString, &args, &argCount);
 * /// Use args and argCount to process the parsed arguments...
 * /// Don't forget to free the allocated memory for args...
 * freeArgs(args, argCount);
 * /// Free the allocated memory for arguments 
 * for (int i = 0; i < argCount; i++) {
 *     free(args[i]);
 * }
 * free(args);
 * @endcode
 */
void parseInput(char *input, char ***args, int *argCount);

/**
 * @brief Prompts the user to enter a command and reads the input into a buffer.
 * 
 * @param[in,out] inputBuffer A pointer to a pointer to the buffer where the input will be stored.
 * @param[in,out] bufferSize A pointer to the size of the buffer.
 * 
 * @note The function allocates memory for the input buffer if it's NULL or insufficient.
 * @warning The function exits with failure if `getline` fails to read input.
 * 
 * Example usage:
 * @code{.c}
 * char *inputBuffer = NULL;
 * size_t bufferSize = 0;
 * getUserInput(&inputBuffer, &bufferSize);
 * /// Use inputBuffer to process user input...
 * /// Don't forget to free the allocated memory for inputBuffer...
 * free(inputBuffer);
 * @endcode
 */
void getUserInput(char **inputBuffer, size_t *bufferSize);


#endif /**< PSH_H */