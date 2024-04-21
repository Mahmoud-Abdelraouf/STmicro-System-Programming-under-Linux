/*****************************************************************/
/******* \Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* \Date      : 8 Apr 2023                 *****************/
/******* \Version   : 0.1                        *****************/
/******* \File Name : parse_datatype.h           *****************/
/*****************************************************************/
#ifndef PARSE_DATATYPE_H_
#define PARSE_DATATYPE_H_

#include <stdint.h>
#include <stdio.h>

#define MAX_STRUCT_NAME_LEN 50 /**< Maximum length of the data type name */

/**
 * @brief Parses the name of a struct from a string.
 *
 * This function extracts the name of a struct from a string
 * formatted as "sizeof(datatype)" and stores it in the provided buffer.
 *
 * @param struct_name The string containing the sizeof expression.
 * @param buffer Pointer to a buffer where the extracted struct name will be
 * stored.
 * @param error_flag Pointer to a uint8_t variable to indicate any errors
 * encountered.
 * @return Pointer to the extracted struct name in the buffer, or NULL if an
 * error occurs.
 */
char *parse_struct_name(char *struct_name, char *buffer, uint8_t *error_flag);

#endif /**< PARSE_DATATYPE_H_ */
