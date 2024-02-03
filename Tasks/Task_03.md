# Task 03 README

## Contents

1. **mypwdv1.c**
   - **Description:** This program (`mypwdv1.c`) prints the current working directory using the `getcwd` function and a fixed-size buffer.
   - **Usage:** Execute the program without any command-line arguments.
   - **Command:**
     ```bash
     ./mypwdv1
     ```
   - **Source Code:**
     ```c
     #include <stdio.h>
     #include <unistd.h>
     
     /**< Buffer to store the current working directory */
     char buf[100];
     
     /**< Pointer to store the return value of getcwd */
     char *ret_add = NULL;
     
     int main(int argc, char **argv) {
         /**< Check if the program is called with no command-line arguments */
         if (argc != 1) {
             /**< Print a usage message */
             printf("Usage: %s only, no args needed\n", argv[0]);
             return -1;
         }
     
         /**< Get the current working directory and store it in the buffer */
         ret_add = getcwd(buf, sizeof(buf));
     
         /**< Check if getcwd failed */
         if (ret_add == NULL) {
             /**< Print an error message */
             perror("getcwd");
             return -1;
         }
     
         /**< Print the current working directory */
         printf("%s\n", ret_add);
     
         /**< Return success */
         return 0;
     }
     ```

2. **mypwdv2.c**
   - **Description:** This program (`mypwdv2.c`) prints the current working directory using the `getcwd` function and dynamic memory allocation.
   - **Usage:** Execute the program without any command-line arguments.
   - **Command:**
     ```bash
     ./mypwdv2
     ```
   - **Source Code:**
     ```c
     #include <stdio.h>
     #include <stdlib.h>
     #include <unistd.h>
     
     int main(int argc, char **argv) {
         /**< Buffer to store the current working directory */
         char *buf = NULL;
     
         /**< Pointer to store the return value of getcwd */
         char *ret_add = NULL;
        
         /**< Check if the program is called with no command-line arguments */
         if (argc != 1) {
             /**< Print a usage message */
             printf("Usage: %s only, no args needed\n", argv[0]);
             return -1;
         }
     
         /**< Determine the required buffer size for the current working directory */
         long size = pathconf(".", _PC_PATH_MAX);
     
         /**< Allocate memory for the buffer based on the determined size */
         if ((buf = (char *)malloc((size_t)size)) != NULL) {
             /**< Get the current working directory and store it in the buffer */
             ret_add = getcwd(buf, (size_t)size);
     
             /**< Check if getcwd failed */
             if (ret_add == NULL) {
                 /**< Print an error message and free the allocated memory */
                 perror("getcwd");
                 free(buf);
                 return -1;
             }
     
             /**< Print the current working directory */
             printf("%s\n", ret_add);
     
             /**< Free the allocated memory */
             free(buf);
         } else {
             /**< Print an error message if memory allocation fails */
             perror("malloc");
             return -1;
         }
     
         return 0;
     }
     ```

3. **my_echo.c**
   - **Description:** This program (`my_echo.c`) echoes the command-line arguments, separating them with spaces.
   - **Usage:** Provide any number of arguments to echo.
   - **Command:**
     ```bash
     ./my_echo arg1 arg2 arg3
     ```
   - **Source Code:**
     ```c
     #include <stdio.h>
     
     int main(int argc, char **argv) {
         /**< Iterate through the command-line arguments starting from index 1 */
         for (int i = 1; i < argc; i++) {
             /**< Print each command-line argument followed by a space */
             printf("%s ", argv[i]);
         }
     
         /**< Print a newline character to separate the output */
         printf("\n");
     
         /**< Return 0 to indicate successful execution */
         return 0;
     }
     ```

4. **my_mv.c**
   - **Description:** This program (`my_mv.c`) moves a file or directory from a source to a destination.
   - **Usage:** Provide source and destination paths as command-line arguments.
   - **Command:**
     ```bash
     ./my_mv source_path destination_path
     ```
   - **Source Code:**
     ```c
     #include <stdio.h>
     #include <stdlib.h>
     
     int main(int argc, char *argv[]) {
         /**< Check the number of arguments */
         if (argc != 3) {
             /**< Print usage message and return -1 */
             printf("Usage: %s <src> <dest>\n", argv[0]);
             return -1;
         }
     
         /**< Extract source and destination paths from command-line arguments */
         const char *src = argv[1];
         const char *dest = argv[2];
     
         /**< Perform the move operation */
         if (rename(src, dest) != 0) {
            

         /**< Handle move operation failure */
             perror("Error moving file");
             return -1;
         }
     
         /**< Return success status */
         return 0;
     }
     ```

**Note:** Ensure executable permissions for each program before running.

**Building Instructions:**
- For each program, compile the source code using the `gcc` compiler:
  ```bash
  gcc -o mypwdv1 mypwdv1.c --save-temps
  gcc -o mypwdv2 mypwdv2.c --save-temps
  gcc -o my_echo my_echo.c --save-temps
  gcc -o my_mv my_mv.c --save-temps
  ```