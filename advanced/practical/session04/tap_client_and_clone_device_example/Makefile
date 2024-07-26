# Makefile for TAP Device Client Project

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -pedantic -std=c11

# Directories
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
INCLUDE_DIR = include

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Library
STATIC_LIB = $(LIB_DIR)/libtapclient.a

# Executable
EXECUTABLE = tap_device_client

# Default target
default: all

# Target to build the executable
all: $(EXECUTABLE)

# Link the object files to create the executable
$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Create object files and archive them into a static library
static_lib: $(STATIC_LIB)

$(STATIC_LIB): $(OBJ_FILES)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean object files
clear_obj:
	rm -rf $(OBJ_DIR)/*.o

# Clean all generated files
clear_all: clear_obj
	rm -rf $(EXECUTABLE) $(STATIC_LIB)

# Clean static library and remove the lib directory
clean_static:
	rm -rf $(LIB_DIR)

# Phony targets
.PHONY: all default clear_obj clear_all static_lib clean_static

# Include dependencies
-include $(OBJ_FILES:.o=.d)

