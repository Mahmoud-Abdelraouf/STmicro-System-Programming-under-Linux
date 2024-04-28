# Linux Memory Manager

This project provides a comprehensive memory management solution for Linux systems. It includes various components and utilities to efficiently manage memory allocation and deallocation, optimizing memory usage in applications.

## Features
- **Heap Memory Manager (HMM)**: Implements a flexible and efficient heap memory management system, replacing standard `malloc` and `free` functions with optimized versions.
- **GLib Thread (GLThread)**: Offers a generic linked list implementation using GLib for thread-safe operations.
- **Memory Manager Test Suite**: Includes a test suite to validate the functionality and performance of the memory manager under various scenarios.
- **Shared and Static Libraries**: Supports building both shared and static libraries, providing flexibility in integration with different applications.

## Usage
1. **Building the Library**:
   - Run `make all` to build the library and test suite.
   - Use `make static` or `make shared` to build the library as a static or shared object, respectively.

2. **Running Tests**:
   - After building, execute the default test suite by running the `hmm` executable.
   - Optionally, run specific tests or modify the test suite according to your requirements.

3. **Integration with Applications**:
   - Link your application with the generated library (`libhmm.a` for static or `libhmm.so` for shared) to leverage the memory management features.

## Documentation
- Detailed documentation and API references are available in the project website: [Linux Memory Manager Documentation](https://mahmoud-abdelraouf.github.io/STM_System-Programming-under-Linux/)

## Contributing
- Contributions are welcome! Fork the repository, make your changes, and submit a pull request.
- Report any issues or suggestions by opening an issue on GitHub.

## License
This project is licensed under the MIT License. See the [LICENSE](../LICENSE) file for details.

---

*This project is part of the Linux System Programming course offered by STMicroelectronics Egypt.*
