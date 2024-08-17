#include "dynamic_logger.h"
#include "command_processor.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Helper function to convert a string to an integer
int parse_int(const char *str) {
    return atoi(str);
}

// Function to print usage information
void print_usage(const char *program_name) {
    printf("Usage: %s <command> <arg1> <arg2> ...\n", program_name);
    printf("Commands:\n");
    printf("  sum <num1> <num2> ...   - Calculate the sum of the provided numbers\n");
    printf("  max <num1> <num2> ...   - Find the maximum value among the provided numbers\n");
    printf("  min <num1> <num2> ...   - Find the minimum value among the provided numbers\n");
    printf("Type 'exit' to quit the program.\n");
}

int main(int argc, char *argv[]) {
    // Mark unused parameters
    (void)argc;
    (void)argv;

    char input[256];
    char command[50];
    int command_args[10];
    int command_argc;

    // Initialize the logger
    init_logger();

    // Register commands
    register_command("sum", print_sum);
    register_command("max", print_max);
    register_command("min", print_min);

    // Print initial usage information
    print_usage(argv[0]);

    // Main loop to keep the program running until "exit" is typed
    while (1) {
        printf("\nEnter command: ");
        fgets(input, sizeof(input), stdin);

        // Remove trailing newline character from input
        input[strcspn(input, "\n")] = 0;

        // Check if the user wants to exit
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Parse the command and arguments
        command_argc = sscanf(input, "%s %d %d %d %d %d %d %d %d %d %d",
                              command,
                              &command_args[0], &command_args[1], &command_args[2],
                              &command_args[3], &command_args[4], &command_args[5],
                              &command_args[6], &command_args[7], &command_args[8],
                              &command_args[9]);

        // Adjust command_argc to only count arguments (subtract 1 for the command itself)
        command_argc -= 1;

        // Execute the command
        if (command_argc > 0) {
            execute_command(command, command_argc, command_args[0], command_args[1], command_args[2],
                            command_args[3], command_args[4], command_args[5], command_args[6],
                            command_args[7], command_args[8], command_args[9]);
        } else if (command_argc == 0) {
            printf("No arguments provided for the command.\n");
            log_message("No arguments provided for the command.");
        } else {
            printf("Invalid command format.\n");
        }
    }

    // Cleanup the logger before exiting
    cleanup_logger();

    printf("Exiting the program. Goodbye!\n");

    return 0;
}

