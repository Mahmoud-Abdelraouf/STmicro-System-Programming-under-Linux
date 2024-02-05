#ifndef COMMANDS_H
#define COMMANDS_H

/**
 * @brief Execute the echo command.
 * @param args The arguments for the echo command.
 */
void echo(char *args[]);

/**
 * @brief Execute the pwd command.
 */
void pwd();

/**
 * @brief Execute the cd command.
 * @param path The path to change the current directory to.
 */
void cd(char *path);


#endif  /**< COMMANDS_H */ 

