#ifndef MM_H_
#define MM_H_

#define MM_MAX_STRUCT_NAME 32

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

#endif /**< MM_H_ */
