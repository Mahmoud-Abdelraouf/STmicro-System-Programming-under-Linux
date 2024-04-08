/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 8 Apr 2023                 *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : MemeoryManager.c           *****************/
/****************************************************************/

/**-----------------< Includes section -----------------*/
#include <assert.h>
#include <memory.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include "mm.h"

/**-----------------< Global variable section -----------------*/
/**
 * @brief Size of the system page.
 * 
 * This static variable holds the size of the system page. It is initialized to 0
 * and should be updated to the actual size of the system page during program initialization
 * using a system-specific function or method.
 * 
 * @note This variable should be initialized to the size of the system page
 *       before any memory management operations are performed within the program.
 *       The actual size of the system page depends on the underlying operating system
 *       and hardware architecture.
 */
static size_t SYSTEM_PAGE_SIZE = 0;

/**
 * @brief Pointer to the first virtual memory page for page families.
 * 
 * This static pointer variable holds the address of the first virtual memory page used
 * to store page families. It is initialized to NULL, indicating that no virtual memory
 * page is currently allocated for page families. As page families are instantiated,
 * new virtual memory pages may be allocated and linked to this pointer.
 * 
 * @note This variable is static and should be accessible only within the scope of the file
 *       in which it is declared. It is used to maintain the linked list of virtual memory
 *       pages for page families throughout the program.
 */
static vm_page_for_families_t *first_vm_page_for_families = NULL;

/**-----------------< Functions implementation section -----------------*/
void mm_init()
{
    SYSTEM_PAGE_SIZE = getpagesize();
}

static void *mm_get_new_vm_page_from_kernel(int units)
{
    // Use the mmap() system call to allocate memory from the kernel
    char *vm_page = mmap(NULL, units * SYSTEM_PAGE_SIZE,
                         PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, 0,
                         0);
    // Check if the allocation was successful
    if (vm_page == MAP_FAILED) {
        // Print an error message if allocation fails
        printf("Error: VM page allocation failed\n");
        return NULL;
    }

    // Initialize the allocated memory block with zeros
    memset(vm_page, 0, units * SYSTEM_PAGE_SIZE);
    
    // Return a pointer to the allocated memory block
    return (void *)vm_page;
}

static void mm_return_page_to_kernel(void *vm_page, int units)
{
    // Use the munmap() system call to return memory to the kernel
    if (munmap(vm_page, units * SYSTEM_PAGE_SIZE) != 0) {
        // Print an error message if unmapping fails
        printf("Error: Could not munmap VM page to kernel\n");
    }
}

void mm_instantiate_new_page_family(char *struct_name, uint32_t struct_size)
{
    vm_page_family_t *vm_page_family_curr = NULL;
    vm_page_for_families_t *new_vm_page_for_families = NULL;

    // Check if the size of the memory structure exceeds the system page size
    if (struct_size > SYSTEM_PAGE_SIZE) {
        printf("Error: %s() structure %s size exceeds system page size\n", __FUNCTION__, struct_name);
        return;
    }

    // If there are no existing virtual memory pages, allocate a new page and initialize it with the first page family
    if (!first_vm_page_for_families) {
        first_vm_page_for_families = (vm_page_for_families_t *)mm_get_new_vm_page_from_kernel(1);
        first_vm_page_for_families->next = NULL;
        strncpy(first_vm_page_for_families->vm_page_family[0].struct_name, struct_name, MM_MAX_STRUCT_NAME);
        first_vm_page_for_families->vm_page_family[0].struct_size = struct_size;
        return;
    }

    uint32_t count = 0;

    // Iterate over existing page families to check if a page family with the same name already exists
    ITERATE_PAGE_FAMILIES_BEGIN(first_vm_page_for_families, vm_page_family_curr) {
        if (strncmp(vm_page_family_curr->struct_name, struct_name, MM_MAX_STRUCT_NAME) != 0) {
            count++;
            continue;
        }

        // Trigger an assertion error if a page family with the same name already exists
        assert(0);
    } ITERATE_PAGE_FAMILIES_END(first_vm_page_for_families, vm_page_family_curr);

    // If the existing page is full, allocate a new page and add it to the beginning of the linked list
    if (count == (uint32_t) MAX_FAMILIES_PER_VM_PAGE) {
        new_vm_page_for_families = (vm_page_for_families_t *)mm_get_new_vm_page_from_kernel(1);
        new_vm_page_for_families->next = first_vm_page_for_families;
        first_vm_page_for_families = new_vm_page_for_families;
        vm_page_family_curr = &first_vm_page_for_families->vm_page_family[0];
    }

    // Initialize the new page family with the specified name and size
    strncpy(vm_page_family_curr->struct_name, struct_name, MM_MAX_STRUCT_NAME);
    vm_page_family_curr->struct_size = struct_size;
    // vm_page_family_curr->firs_page = NULL;
}
/**-----------------< The end of functions implementation section -----------------*/
