CC := gcc
CFLAGS := -Wall -g

# Define the source files
SOURCES := $(wildcard src/*.c)
# Define the object files directly in the 'obj/' directory
OBJECTS := $(patsubst src/%.c,obj/%.o,$(SOURCES))
# Define the executables
EXECUTABLES := $(patsubst src/%.c,bin/%,$(SOURCES))

# Default target
all: directories $(EXECUTABLES)

# Rule to create directories
directories:
	@mkdir -p obj bin

# Rule to create object files directly in the 'obj/' directory
obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to create executables
bin/%: obj/%.o
	$(CC) $(CFLAGS) $< -o $@

# Clean target to remove all binaries and object files
clean:
	rm -rf bin obj

# Clean target to remove only object files
clean-obj:
	rm -f obj/*

# Clean target to remove only bin files
clean-bin:
	rm -f bin/*

# Declare object files as secondary to prevent automatic deletion
.PHONY: all clean clean-obj clean-bin directories
.SECONDARY: $(OBJECTS)

