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
 * @brief Parse the struct name to extract the data type.
 *
 * This function parses the struct name to extract the data type.
 * It sets the error flag to 1 if the struct name is not in the expected format.
 *
 * @param struct_name Pointer to the struct name string.
 * @param error_flag Pointer to the error flag variable to indicate parsing
 * error. If the value is 1, it indicates a parsing error.
 */
void parse_struct_name(char *struct_name, uint8_t *error_flag);

#endif /**< PARSE_DATATYPE_H_ */
