# Linux Capabilities Examples

This repository contains example codes that demonstrate various Linux capabilities and their management in C programs. It includes source files, a Makefile, and test files to illustrate capability manipulation and usage.

## Directory Structure

```plaintext
linux_capabilities_examples/
├── .editorconfig
├── .gitignore
├── Makefile
├── README.md
├── src/
│   ├── driver1.c
│   ├── driver2.c
│   ├── readfile.c
│   ├── service1.c
│   └── service2.c
├── obj/
│   ├── driver1.o
│   ├── driver2.o
│   ├── service1.o
│   ├── service2.o
│   └── readfile.o
├── bin/
│   ├── driver1
│   ├── driver2
│   ├── service1
│   ├── service2
│   └── readfile
└── test_files/
    ├── test1.txt
    └── test2.txt
```

## Table of Contents

1. [Overview](#overview)
2. [Directory Structure](#directory-structure)
3. [Source Files](#source-files)
   - [driver1.c](#driver1c)
   - [driver2.c](#driver2c)
   - [service1.c](#service1c)
   - [service2.c](#service2c)
   - [readfile.c](#readfilec)
4. [Makefile](#makefile)
5. [Building and Cleaning](#building-and-cleaning)
6. [Test Files](#test-files)
7. [Problem and Solution](#problem-and-solution)
8. [Additional Resources](#additional-resources)

## Overview

This directory contains example codes that demonstrate the use of Linux capabilities in C programs. Each source file in the `src` directory showcases different aspects of capability manipulation and management.

## Source Files

### `driver1.c`

`driver1.c` demonstrates how to retrieve and display the current capabilities of a process.

#### Code

```c
// File: driver1.c
// Description: Demonstrates setting and using capabilities.

#include <stdio.h>
#include <stdlib.h>
#include <sys/capability.h>
#include <unistd.h>

/**
 * Main function to retrieve and print process capabilities.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int Exit status.
 */
int main(int argc, char **argv) {
    // Get the current process capabilities.
    cap_t caps = cap_get_proc();
    if (caps == NULL) {
        perror("cap_get_proc");
        exit(EXIT_FAILURE);
    }
    
    // Print the current capabilities.
    printf("Current capabilities: %s\n", cap_to_text(caps, NULL));
    
    // Free the capability structure.
    cap_free(caps);
    return 0;
}
```

### `driver2.c`

`driver2.c` demonstrates how to modify the capabilities of a process and set them as effective.

#### Code

```c
// File: driver2.c
// Description: Demonstrates manipulating capabilities and inheriting them.

#include <stdio.h>
#include <stdlib.h>
#include <sys/capability.h>
#include <unistd.h>

/**
 * Main function to retrieve, modify, and print process capabilities.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int Exit status.
 */
int main(int argc, char **argv) {
    // Get the current process capabilities.
    cap_t caps = cap_get_proc();
    if (caps == NULL) {
        perror("cap_get_proc");
        exit(EXIT_FAILURE);
    }
    printf("Current capabilities: %s\n", cap_to_text(caps, NULL));

    // Define a list of capabilities to set.
    cap_value_t cap_list[2] = {CAP_CHOWN, CAP_DAC_OVERRIDE};
    if (cap_set_flag(caps, CAP_EFFECTIVE, 2, cap_list, CAP_SET) == -1) {
        perror("cap_set_flag");
        exit(EXIT_FAILURE);
    }

    // Set the process capabilities.
    if (cap_set_proc(caps) == -1) {
        perror("cap_set_proc");
        exit(EXIT_FAILURE);
    }
    printf("Modified capabilities: %s\n", cap_to_text(caps, NULL));

    // Free the capability structure.
    cap_free(caps);
    return 0;
}
```

### `service1.c`

`service1.c` is a simple service that retrieves and prints the current capabilities of the process.

#### Code

```c
// File: service1.c
// Description: Simple service demonstrating capability usage.

#include <stdio.h>
#include <stdlib.h>
#include <sys/capability.h>
#include <unistd.h>

/**
 * Main function to retrieve and print service capabilities.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int Exit status.
 */
int main(int argc, char **argv) {
    // Get the current process capabilities.
    cap_t caps = cap_get_proc();
    if (caps == NULL) {
        perror("cap_get_proc");
        exit(EXIT_FAILURE);
    }
    
    // Print the current capabilities.
    printf("Service 1 capabilities: %s\n", cap_to_text(caps, NULL));
    
    // Free the capability structure.
    cap_free(caps);
    return 0;
}
```

### `service2.c`

`service2.c` demonstrates advanced capability manipulation, including setting additional capabilities.

#### Code

```c
// File: service2.c
// Description: Another service demonstrating advanced capability manipulation.

#include <stdio.h>
#include <stdlib.h>
#include <sys/capability.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * Main function to retrieve, modify, and print service capabilities.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int Exit status.
 */
int main(int argc, char **argv) {
    // Get the current process capabilities.
    cap_t caps = cap_get_proc();
    if (caps == NULL) {
        perror("cap_get_proc");
        exit(EXIT_FAILURE);
    }
    printf("Service 2 capabilities: %s\n", cap_to_text(caps, NULL));

    // Define a list of capabilities to set.
    cap_value_t cap_list[2] = {CAP_CHOWN, CAP_DAC_OVERRIDE};
    if (cap_set_flag(caps, CAP_EFFECTIVE, 2, cap_list, CAP_SET) == -1) {
        perror("cap_set_flag");
        exit(EXIT_FAILURE);
    }

    // Set the process capabilities.
    if (cap_set_proc(caps) == -1) {
        perror("cap_set_proc");
        exit(EXIT_FAILURE);
    }
    printf("Modified capabilities: %s\n", cap_to_text(caps, NULL));

    // Free the capability structure.
    cap_free(caps);
    return 0;
}
```

### `readfile.c`

`readfile.c` is used to change file ownership and read the file content.

#### Code

```c
// File: readfile.c
// Description: Program to change file ownership and read a file.

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define  BUFSIZE 1000

/**
 * Main function to change file ownership and read its contents.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int Exit status.
 */
int main(int argc, char **argv) {

   int fd,n;
   char buf[BUFSIZE];

   // Change the ownership of the file specified in argv[1] to user ID 1000 and group ID 1000
   if( chown(argv[1], 1000, 1000) ){
        printf("Couldn't change owner\n");
   } 
   else {
        printf("change owner succeeded\n");
   }
        
   // Open the file specified in argv[2] in read-only mode
   if((fd=open(argv[2],O_RDONLY))== -1){
       printf("Error opening %s\n",argv[2]);
       exit(1);
   }

   // Read the file in chunks of BUFSIZE and write to standard output (usually the terminal)
   while((n=read(fd,buf,BUFSIZE))>0){
     write(1,buf,n);
   }

   // If there was an error reading the file, print an error message
   if( n < 0 ) {
        printf("error reading input file\n");
   }

   // Close the file descriptor
   close(fd);
}
```

## Makefile

The Makefile automates the building process, creating directories for object files and executables, and providing clean targets to remove generated files.

#### Code

```makefile
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

# Rule to create

 executables
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
```

### Explanation

1. **Variables**:
   - `CC`: Specifies the compiler to use (`gcc`).
   - `CFLAGS`: Specifies the compiler flags (`-Wall` for all warnings, `-g` for debugging information).
   - `SOURCES`: List of all source files in the `src/` directory.
   - `OBJECTS`: List of object files to be created in the `obj/` directory.
   - `EXECUTABLES`: List of executable files to be created in the `bin/` directory.

2. **Targets**:
   - `all`: Default target that builds the directories and executables.
   - `directories`: Creates the `obj/` and `bin` directories if they don't exist.
   - `obj/%.o`: Compiles source files into object files in the `obj/` directory.
   - `bin/%`: Links object files to create executables in the `bin/` directory.
   - `clean`: Removes all binaries and object files.
   - `clean-obj`: Removes only the object files.
   - `clean-bin`: Removes only the executables.

3. **Special Targets**:
   - `.PHONY`: Specifies that certain targets are not actual files and should always be executed.
   - `.SECONDARY`: Prevents Make from automatically deleting intermediate files.

## Building and Cleaning

### Building

To build the example programs, run the following command:

```sh
make
```

### Cleaning

To clean up the build artifacts, you can use one of the following commands:

```sh
make clean      # Remove all binaries and object files
make clean-obj  # Remove only object files
make clean-bin  # Remove only executables
```

## Test Files

The `test_files` directory contains text files used for testing the example programs. The files `test1.txt` and `test2.txt` contain some text to demonstrate file operations.

## Problem and Solution

If you encounter the following error:

```sh
gcc -Wall -g -c src/driver1.c -o obj/driver1.o
src/driver1.c:12:10: fatal error: sys/capability.h: No such file or directory
   12 | #include <sys/capability.h>
      |          ^~~~~~~~~~~~~~~~~~
compilation terminated.
```

This means that the `libcap` development library is not installed on your system. On Ubuntu/Debian-based systems, you can install it using:

```sh
sudo apt-get update
sudo apt-get install libcap-dev
```

After installing the library, you should be able to compile the source files without errors.

## Additional Resources

- [Linux Capabilities (man 7 capabilities)](https://man7.org/linux/man-pages/man7/capabilities.7.html)
- [PR_SET_KEEPCAPS Documentation](https://man7.org/linux/man-pages/man2/prctl.2.html)
- [Capability Bounding Set](https://www.kernel.org/doc/html/latest/userspace-api/capabilities.html)
