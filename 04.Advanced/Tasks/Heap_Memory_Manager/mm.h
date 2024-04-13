/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 8 Apr 2023                 *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : MemeoryManager.h           *****************/
/****************************************************************/
#ifndef __MM_H__
#define __MM_H__
/**-----------------< Includes section -----------------*/
/**< System includes */
#include <stdint.h>
/**< External includes */
#include "glthread.h"

/**-----------------< Macros section -----------------*/
#define MM_MAX_STRUCT_NAME 32

/**-----------------< user defined data type section -----------------*/
/**
 * @brief Represents a boolean value.
 *
 * The `vm_bool_t` type represents a boolean value, which can have one of two
 * states: `VM_TRUE` or `VM_FALSE`. It is used to store boolean values in the
 * program.
 */
typedef enum {
  MM_FALSE = 0, /**< Represents the false state. */
  MM_TRUE = 1   /**< Represents the true state. */
} vm_bool_t;

/**
 * @brief Structure representing metadata for a memory block.
 *
 * The `block_meta_data_t` structure represents metadata for a memory block.
 * It includes information such as whether the block is free or allocated,
 * its size, pointers to the previous and next blocks (if applicable), and
 * the offset within the memory region.
 */
typedef struct block_meta_data_ {
  vm_bool_t is_free;   /**< Flag indicating whether the block is free. */
  uint32_t block_size; /**< Size of the memory block. */
  struct block_meta_data_
      *prev_block; /**< Pointer to the previous memory block. */
  struct block_meta_data_ *next_block; /**< Pointer to the next memory block. */
  uint32_t offset;                     /**< Offset within the memory region. */
  glthread_t priority_thread_glue; /**< Priority thread glue for managing block
                                  priority. */
} block_meta_data_t;

/**
 * @brief Macro to declare a conversion function for converting a glthread_t
 * structure to a user-defined structure pointer.
 *
 * This macro simplifies the process of declaring a conversion function that
 * takes a glthread_t pointer and returns a pointer to a user-defined structure.
 * It is particularly useful when you have a glthread_t structure embedded
 * within a user-defined structure and need to access the user-defined data.
 *
 * @param fn_name The name of the conversion function to be declared.
 * @param struct_type The type of the user-defined structure.
 * @param glthread_member The name of the glthread_t member within the
 * user-defined structure.
 * @param glthread_ptr The name of the glthread_t pointer variable.
 *
 * Example usage:
 * Suppose we have a user-defined structure named block_meta_data_t that
 * contains a glthread_t member named priority_thread_glue. To declare a
 * conversion function named glthread_to_block_meta_data to convert a glthread_t
 * pointer to a block_meta_data_t pointer, we use the following declaration:
 *
 * GLTHREAD_TO_STRUCT(glthread_to_block_meta_data, block_meta_data_t,
 *                    priority_thread_glue, glthread_ptr);
 *
 * Now, we can use glthread_to_block_meta_data to convert glthread_t pointers to
 * block_meta_data_t pointers and access the metadata associated with memory
 * blocks.
 */
GLTHREAD_TO_STRUCT(glthread_to_block_meta_data, block_meta_data_t,
                   priority_thread_glue, glthread_ptr);

/**
 * @brief Structure representing a virtual memory page.
 *
 * This structure represents a virtual memory page used in memory management
 * systems. It contains metadata for managing memory blocks within the page, as
 * well as the actual memory region allocated for storing data blocks.
 */
typedef struct vm_page_ {
  struct vm_page_ *next; /**< Pointer to the next virtual memory page. */
  struct vm_page_ *prev; /**< Pointer to the previous virtual memory page. */
  struct vm_page_family_
      *pg_family; /**< Pointer to the page family associated with the page. */
  block_meta_data_t block_meta_data; /**< Metadata for managing memory blocks
                                        within the page. */
  char page_memory[0]; /**< Memory region allocated for storing data blocks. */
} vm_page_t;

/**
 * @brief Structure representing a page family in virtual memory.
 *
 * This structure maintains information about a page family in virtual memory,
 * including the name of the structure, its size, a pointer to the most recent
 * virtual memory page in use, and a priority list of free memory blocks.
 */
typedef struct vm_page_family_ {
  char struct_name[MM_MAX_STRUCT_NAME]; /**< Name of the structure. */
  uint32_t struct_size;                 /**< Size of the structure. */
  vm_page_t *first_page; /**< Pointer to the most recent vm page in use. */
  glthread_t free_block_priority_list_head; /**< Priority list of free memory
                                               blocks. */
} vm_page_family_t;

/**
 * @brief Structure representing a virtual memory page containing families of
 * memory structures.
 */
typedef struct vm_page_for_families_ {
  struct vm_page_for_families_
      *next; /**< Pointer to the next virtual memory page. */
  vm_page_family_t vm_page_family[0]; /**< Array of variable size storing memory
                                         structure families. */
} vm_page_for_families_t;

/**
 * @brief Allocates a new virtual memory page for a given page family.
 *
 * This function allocates a new virtual memory page for the specified page
 * family. It initializes the metadata and pointers associated with the page and
 * inserts the page into the linked list of pages belonging to the page family.
 *
 * @param vm_page_family Pointer to the page family for which the page is being
 * allocated.
 *
 * @return Pointer to the newly allocated virtual memory page.
 */
vm_page_t *allocate_vm_page(vm_page_family_t *vm_page_family);

/**
 * @brief Deletes and frees a virtual memory page.
 *
 * This function deletes and frees a virtual memory page. It removes the page
 * from the linked list of pages belonging to its page family and deallocates
 * the memory associated with the page.
 *
 * @param vm_page Pointer to the virtual memory page to be deleted and freed.
 */
void mm_vm_page_delete_and_free(vm_page_t *vm_page);

/**-----------------< Public functions interface -----------------*/
/**
 * @brief Looks up a page family by its name.
 *
 * This function iterates over all virtual memory pages hosting page families
 * and returns a pointer to the page family object identified by the given
 * struct_name. If no such page family object is found, it returns NULL.
 *
 * @param struct_name The name of the page family to look up.
 *
 * @return Pointer to the page family object if found, otherwise NULL.
 *
 * @note This function should be used to retrieve a page family object by its
 * name after the page families have been registered and initialized using the
 *       appropriate functions and macros provided by the memory manager.
 *
 * @see mm_init
 * @see MM_REG_STRUCT
 * @see vm_page_for_families_t
 * @see vm_page_family_t
 */
vm_page_family_t *lookup_page_family_by_name(char *struct_name);

/**
 * @brief Checks if a virtual memory page is empty.
 *
 * This function determines whether a virtual memory page is empty based on its
 * metadata.
 *
 * @param vm_page Pointer to the virtual memory page to be checked.
 *
 * @return
 * - MM_TRUE if the page is empty.
 * - MM_FALSE if the page is not empty.
 * - -1 if the input pointer is NULL.
 *
 * @note
 * A virtual memory page is considered empty if all the following conditions are
 * met:
 * - The 'next_block' pointer in the block metadata is NULL, indicating no next
 * block.
 * - The 'prev_block' pointer in the block metadata is NULL, indicating no
 * previous block.
 * - The 'is_free' flag in the block metadata is set to MM_TRUE, indicating the
 * page is free.
 *
 * @warning
 * It is important to ensure that the 'vm_page' parameter is a valid pointer to
 * a virtual memory page structure. Passing invalid or uninitialized pointers
 * may result in undefined behavior.
 */
vm_bool_t mm_is_vm_page_empty(vm_page_t *vm_page);

/**
 * @brief Add a free block's metadata to the free block list of a virtual memory
 * page family.
 *
 * This function adds the metadata of a free block to the free block list of a
 * virtual memory page family. The block metadata is inserted into the free
 * block list in descending order of block size, based on the comparison
 * function `free_blocks_comparison_function`.
 *
 * @param vm_page_family Pointer to the virtual memory page family to which the
 * free block metadata will be added.
 * @param free_block Pointer to the block_meta_data_t structure representing the
 * metadata of the free block to be added to the free block list.
 *
 * @note This function assumes that the `is_free` flag of the `free_block`
 * structure is set to MM_TRUE. An assertion will trigger if this condition is
 * not met.
 */
static void
mm_add_free_block_meta_data_to_free_block_list(vm_page_family_t *vm_page_family,
                                               block_meta_data_t *free_block);

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
 * This macro is used to begin iteration over page families stored within a
 * virtual memory page. It initializes a loop for iterating over page families,
 * using the provided pointers.
 *
 * @param vm_page_for_families_ptr Pointer to the virtual memory page for
 * families.
 * @param curr Pointer to the current page family being iterated.
 *
 * @note This macro is typically used in conjunction with
 * `ITERATE_PAGE_FAMILIES_END` to iterate over page families stored within a
 * virtual memory page. The loop continues until all page families have been
 * iterated or the maximum number of families per page is reached.
 *
 * @warning This macro assumes that `vm_page_for_families_ptr` points to a valid
 * virtual memory page structure containing page families, and `curr` is a valid
 * pointer to iterate over these families. Improper usage may result in
 * undefined behavior.
 *
 * @see ITERATE_PAGE_FAMILIES_END
 */
#define ITERATE_PAGE_FAMILIES_BEGIN(vm_page_for_families_ptr, curr)            \
  {                                                                            \
    uint32_t count = 0;                                                        \
    for (curr =                                                                \
             (vm_page_family_t *)&vm_page_for_families_ptr->vm_page_family[0]; \
         curr->struct_size && count < MAX_FAMILIES_PER_VM_PAGE;                \
         curr++, count++) {

/**
 * @brief Macro marking the end of iteration over families within a virtual
 * memory page.
 *
 * This macro is used to mark the end of iteration over families within a
 * virtual memory page, which was started with the `ITERATE_PAGE_FAMILIES_BEGIN`
 * macro. It concludes the loop for iterating over page families.
 *
 * @param vm_page_for_families_ptr Pointer to the virtual memory page for
 * families.
 * @param curr Pointer to the current family being iterated.
 *
 * @note This macro should be used in conjunction with
 * `ITERATE_PAGE_FAMILIES_BEGIN` to properly mark the end of the iteration loop
 * over page families within a virtual memory page.
 *
 * @warning The loop for iterating over families within a virtual memory page
 * should be enclosed within curly braces `{}` to ensure proper scoping of loop
 * variables and statements. Improper usage of this macro may lead to
 * compilation errors or unexpected behavior.
 *
 * @see ITERATE_PAGE_FAMILIES_BEGIN
 */
#define ITERATE_PAGE_FAMILIES_END(vm_page_for_families_ptr, curr)              \
  }                                                                            \
  }

/**
 * @brief Macro to iterate over virtual memory pages beginning from the first
 * page of a page family.
 *
 * This macro allows for iterating over virtual memory pages starting from the
 * first page of a specified page family.
 *
 * @param vm_page_family_ptr Pointer to the page family containing the first
 * page.
 * @param curr Pointer variable to hold the current virtual memory page during
 * iteration.
 */
#define ITERATE_VM_PAGE_BEGIN(vm_page_family_ptr, curr)                        \
  {                                                                            \
    curr = (vm_page_family_ptr)->first_page;                                   \
    vm_page_t *next = NULL;                                                    \
    for (; curr != NULL; curr = next) {                                        \
      next = curr->next;

/**
 * @brief Macro marking the end of the iteration over virtual memory pages.
 *
 * This macro marks the end of the iteration over virtual memory pages.
 *
 * @param vm_page_family_ptr Pointer to the page family containing the first
 * page.
 * @param curr Pointer variable holding the current virtual memory page.
 */
#define ITERATE_VM_PAGE_END(vm_page_family_ptr, curr)                          \
  }                                                                            \
  }

/**
 * @brief Macro to begin iteration over all memory blocks within a virtual
 * memory page.
 *
 * This macro initializes the iteration process over all memory blocks within a
 * given virtual memory page.
 *
 * @param vm_page_ptr Pointer to the virtual memory page.
 * @param curr Pointer to hold the current memory block during iteration.
 *
 * @note This macro is typically used in memory management systems to iterate
 * over all memory blocks within a virtual memory page. It sets up a loop that
 * traverses through the metadata blocks of each memory block within the page.
 *       The iteration begins with the metadata block of the first memory block
 * in the page.
 */
#define ITERATE_VM_PAGE_ALL_BLOCKS_BEGIN(vm_page_ptr, curr)                    \
  do {                                                                         \
    curr = &(vm_page_ptr->block_meta_data);                                    \
    block_meta_data_t *next = NULL;                                            \
    for (; curr != NULL; curr = next) {                                        \
      next = NEXT_META_BLOCK(curr);

/**
 * @brief Macro to end iteration over all memory blocks within a virtual memory
 * page.
 *
 * This macro marks the end of the iteration process over all memory blocks
 * within a virtual memory page.
 *
 * @param vm_page_ptr Pointer to the virtual memory page.
 * @param curr Pointer holding the current memory block during iteration.
 *
 * @note This macro is used in conjunction with ITERATE_VM_PAGE_ALL_BLOCKS_BEGIN
 * macro to define the end of the iteration loop. It completes the loop setup by
 * ITERATE_VM_PAGE_ALL_BLOCKS_BEGIN, ensuring proper termination of the loop.
 */
#define ITERATE_VM_PAGE_ALL_BLOCKS_END(vm_page_ptr, curr)                      \
  }                                                                            \
  }                                                                            \
  while (0)                                                                    \
    ;

/**
 * @brief Macro to calculate the offset of a field within a structure.
 *
 * This macro calculates the byte offset of a specified field within a
 * structure. It is often used in low-level programming to access structure
 * members at specific memory locations.
 *
 * @param container_structure The name of the structure containing the field.
 * @param field_name The name of the field whose offset is being calculated.
 *
 * @return The byte offset of the field within the structure.
 *
 * @note This macro uses the pointer arithmetic to calculate the offset.
 */
#define offset_of(container_structure, field_name)                             \
  ((size_t)(&((container_structure *)0)->field_name))

/**
 * @brief Macro to retrieve the virtual memory page from a block's metadata.
 *
 * This macro retrieves the virtual memory page associated with a given block's
 * metadata.
 *
 * @param block_meta_data_ptr Pointer to the block's metadata.
 * @return Pointer to the virtual memory page.
 */
#define MM_GET_PAGE_FROM_META_BLOCK(block_meta_data_ptr)                       \
  ((void *)((uintptr_t)(block_meta_data_ptr) - (block_meta_data_ptr)->offset))

/**
 * @brief Macro to retrieve the metadata of the next block based on the current
 * block's size.
 *
 * This macro calculates the pointer to the metadata of the next block by adding
 * the size of the current block to the pointer to the current block's metadata.
 *
 * @param block_meta_data_ptr Pointer to the current block's metadata.
 * @return Pointer to the metadata of the next block.
 *
 * @note This macro is commonly used in memory management systems where metadata
 * blocks are used to manage memory allocation. It allows for efficient
 * traversal of the memory blocks, enabling operations such as coalescing
 * adjacent free memory blocks or iterating over allocated memory blocks.
 *
 * @warning The behavior of this macro depends on the assumption that the next
 * block starts immediately after the current block in memory. Ensure that the
 * memory layout and block sizes are correctly managed to avoid undefined
 * behavior.
 */
#define NEXT_META_BLOCK_BY_SIZE(block_meta_data_ptr)                           \
  ((block_meta_data_t *)((uintptr_t)(block_meta_data_ptr) +                    \
                         (block_meta_data_ptr)->block_size))

/**
 * @brief Macro to get the pointer to the next metadata block.
 *
 * This macro is used to obtain the pointer to the next metadata block
 * given a pointer to the current metadata block.
 *
 * @param block_meta_data_ptr Pointer to the current metadata block.
 *
 * @return Pointer to the next metadata block.
 *
 * @note This macro is typically used in memory management systems where
 * metadata blocks are used to manage memory allocation. It allows for efficient
 * traversal of the metadata blocks linked list, enabling operations such as
 * coalescing adjacent free memory blocks or iterating over allocated memory
 * blocks.
 */
#define NEXT_META_BLOCK(block_meta_data_ptr) ((block_meta_data_ptr)->next_block)

/**
 * @brief Macro to get the pointer to the previous metadata block.
 *
 * This macro is used to obtain the pointer to the previous metadata block
 * given a pointer to the current metadata block.
 *
 * @param block_meta_data_ptr Pointer to the current metadata block.
 *
 * @return Pointer to the previous metadata block.
 *
 * @note This macro is typically used in memory management systems where
 * metadata blocks are used to manage memory allocation. It allows for efficient
 * traversal of the metadata blocks linked list, allowing operations such as
 * merging adjacent free memory blocks or finding neighboring blocks.
 */
#define PREV_META_BLOCK(block_meta_data_ptr) ((block_meta_data_ptr)->prev)

/**
 * @brief Macro to mark a virtual memory page as empty.
 *
 * This macro is heavily documented to provide detailed information about its
 * purpose, usage, and behavior.
 *
 * @param vm_page_t_ptr Pointer to the virtual memory page to be marked as
 * empty.
 *
 * @details
 * This macro is used to reset the state of a virtual memory page, indicating
 * that it contains no allocated memory blocks and is available for reuse. It
 * operates by modifying the metadata associated with the memory blocks within
 * the page.
 *
 * The macro takes a single parameter:
 * - @p vm_page_t_ptr: Pointer to the virtual memory page to be marked as empty.
 *
 * The macro does the following:
 * - Sets the 'next_block' and 'prev_block' pointers of the block metadata to
 * NULL, indicating that the page does not have any neighboring blocks.
 * - Sets the 'is_free' flag of the block metadata to MM_TRUE, indicating that
 * the page is free and available for allocation.
 *
 * @note
 * This macro should be used judiciously and only when it is certain that the
 * virtual memory page is not in use and can be safely reset. Incorrect usage
 * may lead to memory corruption or undefined behavior.
 *
 * @warning
 * It is important to ensure that the 'vm_page_t_ptr' parameter is a valid
 * pointer to a virtual memory page structure. Passing invalid or uninitialized
 * pointers may result in undefined behavior.
 *
 * @remark
 * This macro is typically used in memory management systems as part of memory
 * recycling and allocation routines. It helps maintain memory hygiene by
 * properly managing the state of virtual memory pages.
 */
#define MARK_VM_PAGE_EMPTY(vm_page_t_ptr)                                      \
  do {                                                                         \
    (vm_page_t_ptr)->block_meta_data.next_block = NULL;                        \
    (vm_page_t_ptr)->block_meta_data.prev_block = NULL;                        \
    (vm_page_t_ptr)->block_meta_data.is_free = MM_TRUE;                        \
  } while (0)

/**-----------------< Private functions interfacce -----------------*/
/**
 * @brief Allocates a new virtual memory page from the kernel.
 *
 * This function allocates a new virtual memory page from the kernel and returns
 * a pointer to the allocated memory block. It uses the `mmap()` system call to
 * request the allocation of memory from the kernel.
 *
 * @param units The number of memory pages to allocate.
 * @return A pointer to the allocated memory block, or NULL if the allocation
 * fails.
 *
 * @note The size of the allocated memory block is determined by multiplying the
 * specified number of units by the system page size (defined by
 * `SYSTEM_PAGE_SIZE`).
 *
 * @warning This function should be used with caution as it interacts directly
 * with the kernel to allocate memory. Improper use or misuse of this function
 * can lead to memory leaks or system instability.
 *
 * @see man mmap()
 */
static void *mm_get_new_vm_page_from_kernel(int units);

/**
 * @brief Returns a virtual memory page to the kernel.
 *
 * This function returns a virtual memory page previously allocated from the
 * kernel back to the kernel. It uses the `munmap()` system call to release the
 * memory.
 *
 * @param vm_page A pointer to the memory block to be returned to the kernel.
 * @param units The number of memory pages to return to the kernel.
 *
 * @note The size of the memory block to be returned is determined by
 * multiplying the specified number of units by the system page size (defined by
 * `SYSTEM_PAGE_SIZE`).
 *
 * @warning This function should be used with caution as it interacts directly
 * with the kernel to release memory. Improper use or misuse of this function
 * can lead to memory leaks or system instability.
 *
 * @see man munmap()
 */
static void mm_return_vm_page_to_kernel(void *vm_page, int units);

/**
 * @brief Merges two contiguous free memory blocks.
 *
 * This function merges two contiguous free memory blocks into a single block.
 * The function assumes that both blocks are free and contiguous.
 *
 * @param first Pointer to the first free memory block.
 * @param second Pointer to the second free memory block.
 *
 * @note This function is typically used in memory management systems to
 * optimize memory usage by consolidating adjacent free memory blocks.
 */
static void mm_union_free_blocks(block_meta_data_t *first,
                                 block_meta_data_t *second);

/**
 * @brief Calculates the maximum allocatable memory within a virtual memory
 * page.
 *
 * This function computes the maximum amount of memory that can be allocated
 * within a virtual memory page, given the number of units specified.
 *
 * @param units The number of memory units to be allocated.
 * @return The maximum allocatable memory size in bytes.
 *
 * @note This function takes into account the size of the virtual memory page
 * and subtracts the offset of the page memory within the vm_page_t structure to
 *       determine the available memory for allocation.
 *       It is typically used in memory management systems to ensure proper
 * allocation of memory within virtual memory pages.
 */
static inline uint32_t mm_max_page_allocatable_memory(int units);

/**
 * @brief Comparison function for sorting free blocks by block size.
 *
 * This function compares two block_meta_data_t objects based on their block
 * sizes. It is intended to be used as a comparison function for sorting free
 * blocks in descending order of block size.
 *
 * @param _block_meta_data1 Pointer to the first block_meta_data_t object.
 * @param _block_meta_data2 Pointer to the second block_meta_data_t object.
 * @return An integer value representing the result of the comparison:
 *         - If the block size of _block_meta_data1 is greater than that of
 * _block_meta_data2, the function returns -1.
 *         - If the block size of _block_meta_data1 is less than that of
 * _block_meta_data2, the function returns 1.
 *         - If the block sizes are equal, the function returns 0.
 */
static int free_blocks_comparison_function(void *_block_meta_data1,
                                           void *_block_meta_data2);

/**
 * @brief Retrieves the metadata of the biggest free memory block within a given
 * virtual memory page family.
 *
 * This function retrieves the metadata of the biggest free memory block within
 * a specified virtual memory page family. It utilizes a priority list to
 * maintain the biggest free block at the head of the list.
 *
 * @param vm_page_family Pointer to the virtual memory page family for which the
 * biggest free block is to be retrieved.
 *
 * @return Pointer to the metadata of the biggest free memory block within the
 * page family. If no such block exists (i.e., the priority list is empty), it
 * returns NULL.
 *
 * @note This function is typically used in memory management systems to
 * efficiently locate the largest available free block within a page family,
 * which can then be used for memory allocation.
 */
static inline block_meta_data_t *
mm_get_biggest_free_block_page_family(vm_page_family_t *vm_page_family);

#endif /**< MM_H_ */
