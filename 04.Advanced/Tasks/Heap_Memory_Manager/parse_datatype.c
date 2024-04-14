/**
 * @file extract_data_type.c
 * @brief Extracts a data type name from a string containing the sizeof
 * operator.
 *
 * This program demonstrates how to extract a data type name from a string
 * containing the sizeof operator using the sscanf function in C.
 */

#include <stdio.h>

#define MAX_STRUCT_NAME_LEN 50 /**< Maximum length of the data type name */

int main() {
  char size_str[] = "sizeof(int)";     /**< String containing sizeof operator */
  char data_type[MAX_STRUCT_NAME_LEN]; /**< Buffer to store data type name */

  // Attempt to extract data type from size_str
  if (sscanf(size_str, "sizeof(%49[^)])", data_type) == 1) {
    // Print the extracted data type
    printf("Data type: %s\n", data_type);
    return 0; // Return success
  } else {
    // Print error message if extraction fails
    fprintf(stderr, "Error: Invalid struct size format\n");
    return 1; // Return error
  }
}
