Create a static library:
gcc -c *.c
ar -rs libfoo.a *.o
gcc -c main.c -I./mylib
gcc -o main main.o -L./mylib -lfoo

Create a dynamic library:
gcc -c -fPIC *.c
gcc -shared -o libfoo.so *.o
gcc -o main main.c -I ./mylib/ -L ./mylib/ -lfoo
LD_LIBRARY_PATH=./mylib ./main



