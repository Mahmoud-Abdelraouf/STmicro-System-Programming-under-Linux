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
	
	/**< Check if the first input equal to exit or not */
	if(strcmp(str, "exit") == 0) {
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
