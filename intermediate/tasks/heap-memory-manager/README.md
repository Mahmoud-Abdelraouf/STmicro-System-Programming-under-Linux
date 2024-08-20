# Linux Memory Manager

This project provides a comprehensive and optimized memory management solution tailored for Linux systems. It implements a custom heap memory manager, offering enhanced control over memory allocation and deallocation processes, which is critical for high-performance and resource-constrained applications.

## Table of Contents
1. [Introduction](#introduction)
2. [Linux Memory Management Overview](#linux-memory-management-overview)
   - [Why Custom Memory Management?](#why-custom-memory-management)
3. [Project Features](#project-features)
4. [Project Structure](#project-structure)
5. [Building the Project](#building-the-project)
   - [Building the Library](#building-the-library)
   - [Running Tests](#running-tests)
   - [Integration with Applications](#integration-with-applications)
6. [Documentation](#documentation)
7. [Contributing](#contributing)
8. [License](#license)
9. [Acknowledgments](#acknowledgments)

---

## Introduction

Memory management is a critical aspect of system programming, particularly in environments where resource efficiency and performance are paramount. This project presents a custom Heap Memory Manager (HMM) designed specifically for Linux systems, offering an alternative to the standard `malloc` and `free` functions with more efficient, flexible, and robust memory management capabilities.

## Linux Memory Management Overview

### Why Custom Memory Management?

In typical Linux applications, memory management is handled by the system's allocator, which uses functions like `malloc`, `calloc`, and `free`. While these standard functions are sufficient for many applications, they may not provide the level of control, efficiency, or customization required for certain high-performance or specialized applications. This project addresses these limitations by offering:

- **Improved Performance:** Custom memory allocation algorithms can reduce fragmentation and enhance performance.
- **Thread Safety:** The GLib Thread (GLThread) module provides a thread-safe linked list implementation, essential for concurrent applications.
- **Memory Usage Optimization:** The HMM system is designed to make better use of available memory, reducing wastage and improving overall application efficiency.

## Project Features

- **Heap Memory Manager (HMM):** A robust memory management system that replaces the standard dynamic memory allocation functions with custom, optimized alternatives.
- **GLib Thread (GLThread):** A generic, thread-safe linked list implementation built using GLib, facilitating safe and efficient multi-threaded operations.
- **Memory Manager Test Suite:** A comprehensive test suite that rigorously tests the memory manager's functionality and performance across various scenarios, ensuring reliability and robustness.
- **Support for Static and Shared Libraries:** The project can be built as either a static library (`.a`) or a shared library (`.so`), providing flexibility in how it can be integrated into different applications.

## Project Structure

The project is organized into several directories, each serving a specific purpose:

```
.
├── src/                    # Source files containing the core logic of the project
│   ├── datatype_size_lookup.c  # Handles datatype size lookups
│   ├── glthread.c              # GLib-based thread-safe linked list implementation
│   ├── memory_manager.c        # Core heap memory manager implementation
│   ├── memory_manager_test.c   # Test suite for the memory manager
│   ├── parse_datatype.c        # Utilities for parsing datatypes
├── include/                # Header files defining interfaces and structures
│   ├── colors.h                # Utilities for color-coded terminal output
│   ├── datatype_size_lookup.h  # Header for datatype size lookup functions
│   ├── glthread.h              # Header for GLib thread-safe linked list
│   ├── memory_manager.h        # Header for heap memory manager
│   ├── memory_manager_api.h    # API definitions for memory management
│   ├── parse_datatype.h        # Header for datatype parsing utilities
├── lib/                    # Compiled libraries (static and shared)
│   ├── libhmm.a                # Static library for HMM
│   ├── libhmm.so               # Shared library for HMM
├── bin/                    # Compiled executables and object files
│   ├── hmm                     # Executable test suite for the memory manager
│   ├── *.o                     # Object files generated during compilation
├── docs/                   # Documentation and Doxygen configuration
│   ├── Doxyfile                # Configuration file for generating project documentation
├── Makefile                # Makefile for automating build and test processes
├── LICENSE                 # License file outlining the terms of use
└── README.md               # This README file
```

## Building the Project

### Building the Library

To build the project, ensure that you have `gcc` and `make` installed on your system. You can then use the following commands:

- **Build Everything:**  
  ```sh
  make all
  ```
  This command compiles all source files, creates object files, and links them to produce the `hmm` executable, as well as the static and shared libraries.

- **Build Static Library Only:**  
  ```sh
  make static
  ```
  This builds only the static library (`libhmm.a`).

- **Build Shared Library Only:**  
  ```sh
  make shared
  ```
  This builds only the shared library (`libhmm.so`).

### Running Tests

After building, you can run the test suite to verify the memory manager's functionality:

- **Run All Tests:**  
  ```sh
  ./bin/hmm
  ```
  The test suite is comprehensive and covers a wide range of scenarios, ensuring the robustness of the memory manager.

### Integration with Applications

To use the memory manager in your application, link your application with the generated library:

- **Static Linking:**  
  Include the static library `libhmm.a` in your build process.
  
- **Shared Linking:**  
  Include the shared library `libhmm.so` and ensure it is in your system's library path.

```sh
gcc -o myapp myapp.c -Llib -lhmm
```

This command compiles `myapp.c` and links it with the `hmm` library.

## Documentation

Detailed documentation is generated using Doxygen and is available in the `docs/` directory. You can also access the documentation online at the [Linux Memory Manager Documentation](https://mahmoud-abdelraouf.github.io/STM_System-Programming-under-Linux/).

To generate the documentation locally, run:

```sh
make doc
```

This will produce HTML documentation that can be viewed in any web browser.

## Contributing

We welcome contributions from the community! Here’s how you can contribute:

1. **Fork the Repository:** Start by forking the project repository.
2. **Create a Branch:** Develop your feature or fix in a new branch.
3. **Submit a Pull Request:** Once your changes are ready, submit a pull request for review.
4. **Report Issues:** If you find any bugs or have suggestions, please open an issue on GitHub.

### Coding Standards

Please adhere to the coding standards outlined in the `.editorconfig` file to ensure consistency across the project.

## License

This project is licensed under the MIT License. See the [LICENSE](../../../LICENSE) file for more details.

## Acknowledgments

This project is a part of the Linux System Programming course offered by STMicroelectronics Egypt. Special thanks to the course instructors and contributors for their valuable input and guidance.
