/**
 * @file datatype_size_lookup.c
 * @brief Implementation file for data type size lookup functionality.
 *
 * This file contains the implementation of functions related to retrieving the
 * size of data types.
 */

#include "datatype_size_lookup.h"

//-----------------< DatatypeMappings Datatype Mappings -----------------*/
/**
 * @brief Structure representing a data type mapping.
 *
 * This structure defines a mapping between a data type name and its
 * corresponding size.
 */
typedef struct {
  const char *name; /**< The name of the data type. */
  size_t size;      /**< The size of the data type in bytes. */
} datatype_mapping_t;

/**
 * @brief Array of data type mappings.
 *
 * This array contains mappings between data type names and their corresponding
 * sizes.
 */
datatype_mapping_t type_mappings[] = {
    {"int", sizeof(int)},
    {"char", sizeof(char)},
    {"float", sizeof(float)},
    {"double", sizeof(double)},
    {"short", sizeof(short)},
    {"long", sizeof(long)},
    {"long long", sizeof(long long)},
    {"unsigned int", sizeof(unsigned int)},
    {"unsigned char", sizeof(unsigned char)},
    {"unsigned short", sizeof(unsigned short)},
    {"unsigned long", sizeof(unsigned long)},
    {"unsigned long long", sizeof(unsigned long long)},
};

// TODO: Implement an efficient data type mapping lookup using a hash table.
//       Consider using a perfect hash function generator like gperf for optimal
//       performance.
// REFER_TO: gperf.md

size_t get_size_of_datatype(const char *data_type) {
  // Iterate over the mappings and find the matching data type
  for (size_t i = 0; i < sizeof(type_mappings) / sizeof(type_mappings[0]);
       ++i) {
    if (strcmp(data_type, type_mappings[i].name) == 0) {
      return type_mappings[i].size;
    }
  }
  return 0; // Return 0 if data type is not found
}
