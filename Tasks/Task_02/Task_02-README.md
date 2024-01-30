# Task 02 README

## Description

This C program prompts the user to enter text until the user types "exit." It removes newline characters from the input, prints the input, and continues the loop until the user enters "exit," displaying "Good Bye :)" before termination.

## C Code (task_02.c)

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    /**< variable to store the string from the user in */
    char str[1000] = {0};

    /**< String will be appeared to the user */
    printf("Enter anything > ");

    /**< To read from the stdin using fgets() function */
    fgets(str, sizeof(str), stdin);

    /**< Remove the newline character from the input */
    str[strcspn(str, "\n")] = '\0';

    /**< Check if the first input is equal to exit or not */
    if (strcmp(str, "exit") == 0) {
        printf("Good Bye :)\n");
        return 0;
    }

    /**< print the input */
    printf("%s\n", str);

    /**< Execute while the input is not equal to exit */
    while (strcmp(str, "exit") != 0) {
        printf("Enter anything > ");
        fgets(str, sizeof(str), stdin);

        /**< Remove the newline character from the input */
        str[strcspn(str, "\n")] = '\0';

        printf("%s\n", str);
    }

    /**< Say 'Good Bye' before the program is terminated */
    printf("Good Bye :)\n");

    return 0;
}
```

## Compilation Commands

1. **Preprocess (Generate Preprocessed Code):**
   ```bash
   gcc task_02.c -E -o task_02.i
   ```
   - The `-E` flag instructs the compiler to stop after the preprocessing stage, producing the preprocessed code. The output is redirected to `task_02.i`.

2. **Compile Assembly Code (Generate Assembly Code):**
   ```bash
   gcc task_02.c -S -o task_02.s
   ```
   - The `-S` flag tells the compiler to stop after generating assembly code. The output is redirected to `task_02.s`.

3. **Compile Object File (Generate Object File):**
   ```bash
   gcc task_02.c -c -o task_02.o
   ```
   - The `-c` flag compiles the source code into an object file (`task_02.o`) without linking.

4. **Final Compilation (Generate Executable):**
   ```bash
   gcc task_02.c -o task_02
   ```
   - This command links the object file and generates the final executable named `task_02`.

## Execution

To run the compiled program:
```bash
./task_02
```

Enter text when prompted and type "exit" to terminate the program.
