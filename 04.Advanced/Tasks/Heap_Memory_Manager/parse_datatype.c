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
  // Extract data type from struct_name
  if (sscanf(struct_name, "sizeof(%49[^)])", buffer) != 1) {
    // Check if the struct name is a number
    if (is_number(struct_name)) {
      // Reset the error flag
      *error_flag = 2;
      // Copy the string "int" into the buffer
      strncpy(buffer, "int", MAX_STRUCT_NAME_LEN);
      // Return "int" directly
      return buffer;
    } else {
      // Set the error flag to indicate the struct isn't in the form of
      // sizeof(datatype)
      *error_flag = 1;
      return NULL;
    }
  } else {
    // Reset the error flag
    *error_flag = 0;
    // Return a pointer to the extracted data type string
    return buffer;
  }
}

static bool is_number(const char *str) {
  int i = 0;
  bool has_dot = false;
  bool has_suffix = false;

  // Check if the string is empty
  if (str[0] == '\0') {
    return false;
  }

  // Check each character in the string
  while (str[i] != '\0') {
    if (!isdigit(str[i])) {
      if (str[i] == '.' && !has_dot) {
        has_dot = true;
      } else if ((str[i] == 'f' || str[i] == 'F') && !has_suffix) {
        has_suffix = true;
      } else {
        return false;
      }
    }
    i++;
  }
  // Check if the string has a digit before the suffix 'f' or 'F'
  if (has_suffix && !isdigit(str[i - 1])) {
    return false;
  }
  return true;
}

int convert_to_int(const char *str) { return atoi(str); }
