32-bit version:
---------------
```bash
nasm -f elf32 syscall32.nasm 
ld -m elf_i386 syscall32.o -o my32syscall
```

System call numbers are located in `/usr/include/x86_64-linux-gnu/asm/unistd_32.h`.

64-bit version:
---------------
```bash
nasm -f elf64 syscall64.nasm
ld syscall64.o --entry main -o my64syscall
```

System call numbers are located in `/usr/include/x86_64-linux-gnu/asm/unistd_64.h`.