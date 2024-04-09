/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 8 Apr 2023                 *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : MemeoryManager.h           *****************/
/****************************************************************/
/**-----------------< Includes section -----------------*/
#include "uapi_mm.h"
#include <stdint.h>

/**-----------------< User defined data types section -----------------*/
typedef struct emp_ {
	char name[32];
	uint32_t emp_id;
} emp_t;

typedef struct student_ {
	char name[32];
	uint32_t roll_no;
	uint32_t marks_phys;
	uint32_t marks_chem;
	uint32_t marks_maths;
	struct student_ *next;
} student_t;

/**-----------------< Business logic -----------------*/
/**
 * @brief Entry point of the program.
 * 
 * This function serves as the entry point of the program. It initializes the memory manager,
 * registers page families for the 'emp_t' and 'student_t' structures using the `MM_REG_STRUCT` macro,
 * prints all registered page families using the `mm_print_registered_page_families()` function, and
 * then returns 0 to indicate successful execution.
 * 
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 * 
 * @return 0 on successful execution.
 * 
 * @note This function should be invoked to start the program. It relies on the initialization
 *       of the memory manager (`mm_init()`) and the proper registration of page families using
 *       the `MM_REG_STRUCT` macro before printing the registered page families.
 * 
 * @see mm_init
 * @see MM_REG_STRUCT
 * @see mm_print_registered_page_families
 */
int main(int argc, char *argv[])
{
    // Initialize the memory manager
    mm_init();

    // Register page families for 'emp_t' and 'student_t' structures
    MM_REG_STRUCT(emp_t);
    MM_REG_STRUCT(student_t);

    // Print all registered page families
    mm_print_registered_page_families();

    return 0; // Indicate successful execution
}

