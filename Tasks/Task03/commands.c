#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "commands.h"

void echo(char *args[]) {
    /**< Print each argument separated by a space */ 
    for (int i = 0; args[i] != NULL; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");
}

void pwd() {
    /**< Buffer to store the current working directory */ 
    char buf[100];

    /**< Get the current working directory and print it */ 
    if (getcwd(buf, sizeof(buf)) != NULL) {
        printf("%s\n", buf);
    } else {
        perror("getcwd");
    }
}

void cd(char *path) {
    /**< Change the current working directory */ 
    if (chdir(path) != 0) {
        perror("chdir");
    }
}
