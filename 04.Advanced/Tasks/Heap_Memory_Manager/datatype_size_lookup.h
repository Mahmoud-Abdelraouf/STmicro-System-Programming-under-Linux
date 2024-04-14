#ifndef DATATYPE_SIZE_LOOKUP_H_
#define DATATYPE_SIZE_LOOKUP_H_

#include <stdio.h>
#include <string.h>

#define MAX_STRUCT_NAME_LEN 50

// Define a structure to map data type strings to C data types
typedef struct datatype_mapping_ {
  char name[MAX_STRUCT_NAME_LEN];
  size_t size;
} DataTypeMapping_t;

/**
 * @brief Gets the size of a data type by its name.
 *
 * This function searches for the given data type name in a pre-defined
 * mapping table and returns the size of the data type if found.
 *
 * @param data_type The name of the data type to get the size of.
 * @return The size of the data type if found, otherwise 0.
 */
size_t getSizeOfDataType(const char *data_type);

#endif /**< DATATYPE_SIZE_LOOKUP_H_ */
