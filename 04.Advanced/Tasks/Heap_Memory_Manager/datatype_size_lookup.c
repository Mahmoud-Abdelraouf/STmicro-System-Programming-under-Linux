#include "datatype_size_lookup.h"

// Define a lookup table for data type mappings
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

// int main() {
//   char size_str[] = "sizeof(int)";
//   char data_type[MAX_STRUCT_NAME_LEN];
//
//   // Extract data type from size_str
//   if (sscanf(size_str, "sizeof(%49[^)])", data_type) == 1) {
//     // Get the size of the data type
//     size_t size = getSizeOfDataType(data_type);
//     if (size != 0) {
//       printf("Size of %s: %zu\n", data_type, size);
//     } else {
//       fprintf(stderr, "Error: Unknown data type\n");
//     }
//   } else {
//     fprintf(stderr, "Error: Invalid struct size format\n");
//   }
//
//   return 0;
// }
