# Converting Executable to Assembly in Linux

### Overview

Converting an executable to assembly code is useful for understanding how high-level code is translated to machine instructions. This guide covers the steps to compile a simple C/C++ program, generate an executable, and then disassemble it to view the corresponding assembly code. Additionally, it covers using NASM (Netwide Assembler) for writing and compiling assembly code directly.

## Table of Contents

1. [Overview](#overview)
2. [Prerequisites](#prerequisites)
3. [Step-by-Step Guide](#step-by-step-guide)
   - [Step 1: Write a Simple C/C++ Program](#step-1-write-a-simple-cc-program)
   - [Step 2: Compile the Program to Generate an Executable](#step-2-compile-the-program-to-generate-an-executable)
   - [Step 3: Generate Assembly Code from the Executable](#step-3-generate-assembly-code-from-the-executable)
   - [Step 4: View the Assembly Code](#step-4-view-the-assembly-code)
4. [Generating Assembly Code from C/C++ Source Directly](#generating-assembly-code-from-cc-source-directly)
5. [Working with NASM](#working-with-nasm)
   - [Step 1: Write a Simple Assembly Program](#step-1-write-a-simple-assembly-program)
   - [Step 2: Compile the Assembly Program](#step-2-compile-the-assembly-program)
   - [Step 3: Link the Object File](#step-3-link-the-object-file)
   - [Step 4: Run the Executable](#step-4-run-the-executable)
6. [Explanation](#explanation)
7. [Conclusion](#conclusion)

---

### Prerequisites

Ensure you have the following tools installed:

1. **GCC (GNU Compiler Collection)**: To compile C/C++ code.
2. **objdump**: To disassemble the executable and view the assembly code.
3. **NASM (Netwide Assembler)**: To write and compile assembly code.

You can install these tools using:

```sh
sudo apt update
sudo apt install build-essential
sudo apt install binutils
sudo apt install nasm
```

### Step-by-Step Guide

#### Step 1: Write a Simple C/C++ Program

Create a simple C/C++ program. Save the following code in a file named `example.c`:

```c
#include <stdio.h>

int main() {
    int a = 5;
    int b = 10;
    int sum = a + b;
    printf("Sum: %d\n", sum);
    return 0;
}
```

#### Step 2: Compile the Program to Generate an Executable

Compile the C/C++ program using GCC. This will produce an executable file named `example`:

```sh
gcc -o example example.c
```

#### Step 3: Generate Assembly Code from the Executable

Use `objdump` to disassemble the executable and produce the assembly code. The `-d` option disassembles the executable, and `-Mintel` specifies Intel syntax (optional, use `-M att` for AT&T syntax):

```sh
objdump -d -Mintel example > example.asm
```

#### Step 4: View the Assembly Code

Open the generated `example.asm` file to view the assembly code:

```sh
less example.asm
```

The assembly code will look something like this:

```assembly
example:     file format elf64-x86-64

Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    rsp,0x8
    1008:	48 8b 05 f1 2f 00 00 	mov    rax,QWORD PTR [rip+0x2ff1]        # 4000 <__gmon_start__>
    100f:	48 85 c0             	test   rax,rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   rax
    1016:	48 83 c4 08          	add    rsp,0x8
    101a:	c3                   	ret    

...

Disassembly of section .text:

0000000000001139 <main>:
    1139:	f3 0f 1e fa          	endbr64 
    113d:	55                   	push   rbp
    113e:	48 89 e5             	mov    rbp,rsp
    1141:	89 7d ec             	mov    DWORD PTR [rbp-0x14],edi
    1144:	48 89 75 e0          	mov    QWORD PTR [rbp-0x20],rsi
    1148:	c7 45 fc 05 00 00 00 	mov    DWORD PTR [rbp-0x4],0x5
    114f:	c7 45 f8 0a 00 00 00 	mov    DWORD PTR [rbp-0x8],0xa
    1156:	8b 55 fc             	mov    edx,DWORD PTR [rbp-0x4]
    1159:	8b 45 f8             	mov    eax,DWORD PTR [rbp-0x8]
    115c:	01 d0                	add    eax,edx
    115e:	89 45 f4             	mov    DWORD PTR [rbp-0xc],eax
    1161:	8b 55 f4             	mov    edx,DWORD PTR [rbp-0xc]
    1164:	48 8d 3d 7e 0e 00 00 	lea    rdi,[rip+0xe7e]        # 2000 <_IO_stdin_used+0x1>
    116b:	b8 00 00 00 00       	mov    eax,0x0
    1170:	e8 eb fe ff ff       	call   1060 <printf@plt>
    1175:	b8 00 00 00 00       	mov    eax,0x0
    117a:	5d                   	pop    rbp
    117b:	c3                   	ret    
```

### Generating Assembly Code from C/C++ Source Directly

You can also generate assembly code directly from the C/C++ source code using GCC:

```sh
gcc -S -o example.s example.c
```

This will produce a file named `example.s` containing the assembly code for the `example.c` program.

### Working with NASM

#### Step 1: Write a Simple Assembly Program

Create a simple assembly program. Save the following code in a file named `example.asm`:

```assembly
section .data
    msg db 'Hello, World!', 0

section .text
    global _start

_start:
    ; Write the message to stdout
    mov eax, 4          ; syscall number for sys_write
    mov ebx, 1          ; file descriptor (stdout)
    mov ecx, msg        ; pointer to message
    mov edx, 13         ; message length
    int 0x80            ; make syscall

    ; Exit the program
    mov eax, 1          ; syscall number for sys_exit
    xor ebx, ebx        ; return 0 status
    int 0x80            ; make syscall
```

#### Step 2: Compile the Assembly Program

Compile the assembly program using NASM. This will produce an object file named `example.o`:

```sh
nasm -f elf32 example.asm -o example.o
```

#### Step 3: Link the Object File

Link the object file using GCC. This will produce an executable file named `example`:

```sh
gcc -m32 example.o -o example
```

#### Step 4: Run the Executable

Run the executable to see the output:

```sh
./example
```

You should see the message "Hello, World!" printed to the terminal.

### Explanation

- **Assembly Code**: The disassembled output shows the low-level assembly instructions corresponding to the high-level C/C++ code.
- **Sections**: The disassembly is organized into sections, such as `.init` and `.text`. The `.text` section contains the executable instructions, including the `main` function.
- **Instructions**: Each line represents an assembly instruction. For example, `mov    eax,0x0` moves the immediate value `0x0` into the `eax` register.

### Conclusion

By following these steps, you can compile a C/C++ program, generate an executable, and disassemble it to view the corresponding assembly code. Additionally, you can write and compile assembly code directly using NASM. This process helps in understanding how high-level code is translated into machine instructions and can be useful for debugging and optimization purposes.
