global main

SECTION .data
msg: db "Hello World from x86_64 machine", 0Ah, 0h  ; Define the message with newline and null terminator
len_msg: equ $ - msg                                ; Calculate the length of the message

SECTION .text
main:
	mov rax, 1         ; Syscall number for sys_write
	mov rdi, 1         ; File descriptor 1 (stdout)
	mov rsi, msg       ; Address of the message
	mov rdx, len_msg   ; Length of the message
	syscall            ; Invoke syscall to write message to stdout (1)

	mov r15, rax       ; Save the return value (number of bytes written)

	mov rax, 60        ; Syscall number for sys_exit
	mov rdi, r15       ; Exit code (number of bytes written)
	syscall            ; Invoke syscall to exit program
