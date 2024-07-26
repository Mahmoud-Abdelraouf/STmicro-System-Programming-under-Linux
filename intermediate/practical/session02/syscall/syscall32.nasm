section .data                           ; Data segment
   userMsg db 'Please enter a number: ' ; Ask the user to enter a number
   lenUserMsg equ $-userMsg             ; Calculate the length of the message
   dispMsg db 'You have entered: '
   lenDispMsg equ $-dispMsg                 

section .bss           ; Uninitialized data
   num resb 5          ; Reserve space for storing the user input (5 bytes)

section .text          ; Code Segment
   global _start
	
_start:                ; Entry point
   ; Display prompt to the user
   mov eax, 4          ; Syscall number for sys_write
   mov ebx, 1          ; File descriptor 1 (stdout)
   mov ecx, userMsg    ; Message to display
   mov edx, lenUserMsg ; Length of the message
   int 80h             ; Invoke syscall
   
   ; Read and store the user input
   mov eax, 3          ; Syscall number for sys_read
   mov ebx, 2          ; File descriptor 2 (stdin)
   mov ecx, num        ; Address to store the input
   mov edx, 5          ; Maximum bytes to read
   int 80h             ; Invoke syscall
	
   ; Output the message 'You have entered: '
   mov eax, 4          ; Syscall number for sys_write
   mov ebx, 1          ; File descriptor 1 (stdout)
   mov ecx, dispMsg    ; Message to display
   mov edx, lenDispMsg ; Length of the message
   int 80h             ; Invoke syscall  

   ; Output the number entered by the user
   mov eax, 4          ; Syscall number for sys_write
   mov ebx, 1          ; File descriptor 1 (stdout)
   mov ecx, num        ; Address of the number
   mov edx, 5          ; Number of bytes to write
   int 80h             ; Invoke syscall
    
   ; Exit the program
   mov eax, 1          ; Syscall number for sys_exit
   mov ebx, 0          ; Exit code 0
   int 80h             ; Invoke syscall