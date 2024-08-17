#include "command_processor.h"
#include "dynamic_logger.h"
#include "project_config.h"

typedef struct {
    char command_name[DEFAULT_COMMAND_NAME_LENGTH];
    command_func func;
} command_t;

static command_t commands[MAX_COMMANDS];
static int command_count = 0;

void register_command(const char *command_name, command_func func) {
    if (command_count < MAX_COMMANDS) {
        strncpy(commands[command_count].command_name, command_name, sizeof(commands[command_count].command_name));
        commands[command_count].func = func;
        command_count++;
        log_message("Command registered: %s", command_name);
    } else {
        log_message("Failed to register command: %s. Maximum number of commands reached.", command_name);
    }
}

void execute_command(const char *command_name, int argc, ...) {
    va_list args;
    va_start(args, argc);

    for (int i = 0; i < command_count; i++) {
        if (strcmp(commands[i].command_name, command_name) == 0) {
            commands[i].func(argc, args);
            va_end(args);
            return;
        }
    }

    log_message("Command not found: %s", command_name);
    va_end(args);
}

void list_commands() {
    log_message("Available commands:");
    for (int i = 0; i < command_count; i++) {
        log_message("- %s", commands[i].command_name);
    }
}
