/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 8 Apr 2023                 *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : MemeoryManager.h           *****************/
/****************************************************************/
#ifndef MM_H_
#define MM_H_
/**-----------------< Includes section -----------------*/
#include <stdint.h> 

/**-----------------< Macros section -----------------*/
#define MM_MAX_STRUCT_NAME 32

/**-----------------< user defined data type section -----------------*/
/**
 * @brief Structure representing a family of memory structures.
 */
typedef struct vm_page_family_ {
  char struct_name[MM_MAX_STRUCT_NAME]; /**< Name of the structure. */
  uint32_t struct_size;                 /**< Size of the structure. */
} vm_page_family_t;

/**
 * @brief Structure representing a virtual memory page containing families of
 * memory structures.
 */
typedef struct vm_page_for_families_ {
  struct vm_page_for_families_ *next; /**< Pointer to the next virtual memory page. */
  vm_page_family_t vm_page_family[0]; /**< Array of variable size storing memory
                                         structure families. */
} vm_page_for_families_t;

/**-----------------< Function-like macro section -----------------*/
/**
 * @brief Macro defining the maximum number of families that can be stored in a
 * single virtual memory page.
 */
#define MAX_FAMILIES_PER_VM_PAGE                                               \
  (SYSTEM_PAGE_SIZE - sizeof(vm_page_family_t *) / sizeof(vm_page_family_t))

/**
 * @brief Macro for iterating over families stored within a virtual memory page.
 *
 * @param vm_page_for_families_ptr Pointer to the virtual memory page.
 * @param curr Pointer to the current family being iterated.
 */
#define ITERATE_PAGE_FAMILIES_BEGIN(vm_page_for_families_ptr, curr)             \
{                                                                               \
  uint32_t count = 0;                                                           \
  for (curr = (vm_page_family_t *)&vm_page_for_families_ptr->vm_page_family[0]; \
       curr->struct_size && count < MAX_FAMILIES_PER_VM_PAGE;                   \
       curr++, count++) {

/**
 * @brief Macro marking the end of the iteration over families within a virtual
 * memory page.
 *
 * @param vm_page_for_families_ptr Pointer to the virtual memory page.
 * @param curr Pointer to the current family being iterated.
 */
#define ITERATE_PAGE_FAMILIES_END(vm_page_for_families_ptr, curr)              \
  }                                                                            \
}

/**-----------------< Public functions interfacce -----------------*/
/**
 * @brief Initializes the memory manager.
 * 
 * This function initializes the memory manager. It sets up necessary configurations
 * and parameters for memory management operations within the program. It specifically
 * determines the system page size using the `getpagesize()` system call and assigns
 * it to the global variable `SYSTEM_PAGE_SIZE`.
 * 
 * @note This function should be called before any memory management operations are performed
 *       within the program. It is typically called at the beginning of the program execution
 *       to ensure proper initialization of memory management functionalities.
 * 
 * @warning This function relies on the `getpagesize()` system call to determine the system page size.
 *           Therefore, it may not be portable across all platforms. It is primarily intended for use
 *           in Unix-like systems where `getpagesize()` is available.
 * 
 * @see getpagesize()
 */
void mm_init();

/**
 * @brief Instantiates a new page family for a memory structure.
 * 
 * This function creates a new page family for a memory structure identified by its name
 * and size. It allocates memory for the page family and adds it to the existing virtual
 * memory pages if necessary. Each page family can contain multiple memory structures of
 * the same type.
 * 
 * @param struct_name The name of the memory structure.
 * @param struct_size The size of the memory structure.
 * 
 * @note If the size of the memory structure exceeds the system page size, an error message
 *       is printed, and the function returns without creating the page family.
 * 
 * @note This function maintains a linked list of virtual memory pages (`first_vm_page_for_families`)
 *       to store the page families. If there are no existing pages, it allocates a new page and
 *       initializes it with the first page family. If the existing pages are full, it allocates
 *       a new page and adds it to the beginning of the linked list.
 * 
 * @note If a page family with the same name already exists, an assertion error is triggered, indicating
 *       a conflict in page family instantiation.
 * 
 * @warning This function relies on the `mm_get_new_vm_page_from_kernel()` function to allocate
 *           memory from the kernel for the page family. Improper use or misuse of this function
 *           can lead to memory leaks or system instability.
 * 
 * @see mm_get_new_vm_page_from_kernel()
 */
void mm_instantiate_new_page_family(char *struct_name, uint32_t struct_size);

/**-----------------< Private functions interfacce -----------------*/
/**
 * @brief Allocates a new virtual memory page from the kernel.
 * 
 * This function allocates a new virtual memory page from the kernel and returns a pointer
 * to the allocated memory block. It uses the `mmap()` system call to request the allocation
 * of memory from the kernel.
 * 
 * @param units The number of memory pages to allocate.
 * @return A pointer to the allocated memory block, or NULL if the allocation fails.
 * 
 * @note The size of the allocated memory block is determined by multiplying the specified
 *       number of units by the system page size (defined by `SYSTEM_PAGE_SIZE`).
 * 
 * @warning This function should be used with caution as it interacts directly with the kernel
 *           to allocate memory. Improper use or misuse of this function can lead to memory
 *           leaks or system instability.
 * 
 * @see man mmap()
 */
static void *mm_get_new_vm_page_from_kernel(int units);

/**
 * @brief Returns a virtual memory page to the kernel.
 * 
 * This function returns a virtual memory page previously allocated from the kernel
 * back to the kernel. It uses the `munmap()` system call to release the memory.
 * 
 * @param vm_page A pointer to the memory block to be returned to the kernel.
 * @param units The number of memory pages to return to the kernel.
 * 
 * @note The size of the memory block to be returned is determined by multiplying
 *       the specified number of units by the system page size (defined by `SYSTEM_PAGE_SIZE`).
 * 
 * @warning This function should be used with caution as it interacts directly with the kernel
 *           to release memory. Improper use or misuse of this function can lead to memory
 *           leaks or system instability.
 * 
 * @see man munmap()
 */
static void mm_return_page_to_kernel(void *vm_page, int units);

#endif /**< MM_H_ */
