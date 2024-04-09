/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 8 Apr 2023                 *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : MemeoryManager.h           *****************/
/****************************************************************/
#ifndef __MM_H__
#define __MM_H__
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
  vm_page_family_t vm_page_family[0]; /**< Array of variable size storing memory structure families. */
} vm_page_for_families_t;

/**-----------------< Function-like macro section -----------------*/
/**
 * @brief Macro defining the maximum number of families that can be stored in a
 * single virtual memory page.
 */
#define MAX_FAMILIES_PER_VM_PAGE                                               \
  (SYSTEM_PAGE_SIZE - sizeof(vm_page_family_t *) / sizeof(vm_page_family_t))

/**
 * @brief Macro for beginning iteration over page families.
 * 
 * This macro is used to begin iteration over page families stored within a virtual memory page.
 * It initializes a loop for iterating over page families, using the provided pointers.
 * 
 * @param vm_page_for_families_ptr Pointer to the virtual memory page for families.
 * @param curr Pointer to the current page family being iterated.
 * 
 * @note This macro is typically used in conjunction with `ITERATE_PAGE_FAMILIES_END` to iterate
 *       over page families stored within a virtual memory page. The loop continues until all page
 *       families have been iterated or the maximum number of families per page is reached.
 * 
 * @warning This macro assumes that `vm_page_for_families_ptr` points to a valid virtual memory page
 *           structure containing page families, and `curr` is a valid pointer to iterate over
 *           these families. Improper usage may result in undefined behavior.
 * 
 * @see ITERATE_PAGE_FAMILIES_END
 */
#define ITERATE_PAGE_FAMILIES_BEGIN(vm_page_for_families_ptr, curr)             \
{                                                                               \
  uint32_t count = 0;                                                           \
  for (curr = (vm_page_family_t *)&vm_page_for_families_ptr->vm_page_family[0]; \
       curr->struct_size && count < MAX_FAMILIES_PER_VM_PAGE;                   \
       curr++, count++) {

/**
 * @brief Macro marking the end of iteration over families within a virtual memory page.
 * 
 * This macro is used to mark the end of iteration over families within a virtual memory page,
 * which was started with the `ITERATE_PAGE_FAMILIES_BEGIN` macro. It concludes the loop
 * for iterating over page families.
 * 
 * @param vm_page_for_families_ptr Pointer to the virtual memory page for families.
 * @param curr Pointer to the current family being iterated.
 * 
 * @note This macro should be used in conjunction with `ITERATE_PAGE_FAMILIES_BEGIN` to properly
 *       mark the end of the iteration loop over page families within a virtual memory page.
 * 
 * @warning The loop for iterating over families within a virtual memory page should be enclosed
 *          within curly braces `{}` to ensure proper scoping of loop variables and statements.
 *          Improper usage of this macro may lead to compilation errors or unexpected behavior.
 * 
 * @see ITERATE_PAGE_FAMILIES_BEGIN
 */
#define ITERATE_PAGE_FAMILIES_END(vm_page_for_families_ptr, curr)              \
  }                                                                            \
}

/**-----------------< Public functions interfacce -----------------*/
/**
 * @brief Looks up a page family by its name.
 * 
 * This function iterates over all virtual memory pages hosting page families
 * and returns a pointer to the page family object identified by the given struct_name.
 * If no such page family object is found, it returns NULL.
 * 
 * @param struct_name The name of the page family to look up.
 * 
 * @return Pointer to the page family object if found, otherwise NULL.
 * 
 * @note This function should be used to retrieve a page family object by its name
 *       after the page families have been registered and initialized using the
 *       appropriate functions and macros provided by the memory manager.
 * 
 * @see mm_init
 * @see MM_REG_STRUCT
 * @see vm_page_for_families_t
 * @see vm_page_family_t
 */
vm_page_family_t *lookup_page_family_by_name(char *struct_name);

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
