/**
 * @file extract_data_type.c
 * @brief Extracts a data type name from a string containing the sizeof
 * operator.
 *
 * This program demonstrates how to extract a data type name from a string
 * containing the sizeof operator using the sscanf function in C.
 */

#include "parse_datatype.h"

void parse_struct_name(char *struct_name, uint8_t *error_flag) {
  // To store the name extracted from the sizeof()
  char data_type[MAX_STRUCT_NAME_LEN];

  // Extract data type from size_str
  if (sscanf(struct_name, "sizeof(%49[^)])", data_type) != 1) {
    // Set the flag that indicates the struct isn't in form of sizeof(datatype)
    *error_flag = 1;
  } else {
    // Reset the error flag
    *error_flag = 0;
  }
}
