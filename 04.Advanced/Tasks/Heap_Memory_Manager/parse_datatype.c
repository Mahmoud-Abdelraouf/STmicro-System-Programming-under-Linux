/**
 * @file extract_data_type.c
 * @brief Extracts a data type name from a string containing the sizeof
 * operator.
 *
 * This program demonstrates how to extract a data type name from a string
 * containing the sizeof operator using the sscanf function in C.
 */

#include "parse_datatype.h"

char *parse_struct_name(char *struct_name, char *buffer, uint8_t *error_flag) {
  // Extract data type from size_str
  if (sscanf(struct_name, "sizeof(%49[^)])", buffer) != 1) {
    // Set the flag that indicates the struct isn't in the form of
    // sizeof(datatype)
    *error_flag = 1;
    return NULL;
  } else {
    // Reset the error flag
    *error_flag = 0;
    // Return a pointer to the extracted data type string
    return buffer;
  }
}
