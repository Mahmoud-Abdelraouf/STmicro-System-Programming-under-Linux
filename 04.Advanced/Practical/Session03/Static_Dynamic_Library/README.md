## Static and Shared Libraries in C

This README provides instructions for creating and using static and shared libraries in C programming.

### Static Library:

To create a static library, follow these steps:

1. Compile all source files (*.c) into object files (*.o):
   ```bash
   gcc -c *.c
   ```

2. Create the static library (*.a) using `ar`:
   ```bash
   ar -rs libfoo.a *.o
   ```

3. Compile the main program (main.c) with the static library:
   ```bash
   gcc -c main.c -I./mylib
   gcc -o main main.o -L./mylib -lfoo
   ```

### Shared Library:

To create a shared library, follow these steps:

1. Compile all source files (*.c) into position-independent code (PIC) object files (*.o):
   ```bash
   gcc -c -fPIC *.c
   ```

2. Create the shared library (*.so) using `gcc`:
   ```bash
   gcc -shared -o libfoo.so *.o
   ```

3. Compile the main program (main.c) with the shared library:
   ```bash
   gcc -o main main.c -I./mylib/ -L./mylib/ -lfoo
   ```

4. Set the `LD_LIBRARY_PATH` environment variable to the directory containing the shared library:
   ```bash
   LD_LIBRARY_PATH=./mylib ./main
   ```

These instructions provide a clear pathway for creating and using both static and shared libraries in C programming. Static libraries are linked directly into the main program, while shared libraries are dynamically loaded at runtime, offering flexibility and efficiency in code management.