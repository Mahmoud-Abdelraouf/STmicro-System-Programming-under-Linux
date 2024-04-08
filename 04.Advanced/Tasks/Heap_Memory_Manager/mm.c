#include <assert.h>
#include <memory.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include "mm.h"

/**< The size of the system page.*/
static size_t SYSTEM_PAGE_SIZE = 0;

/**<  */
static vm_page_for_families_t *first_vm_page_for_families = NULL;

/**< Initialize the memory manager. */
void mm_init()
{
	SYSTEM_PAGE_SIZE = getpagesize();
}

/**
 * @brief Allocate a new virtual memory page from the kernel.
 *
 * @param units Number of units to allocate (multiples of system page size).
 * @return Pointer to the allocated memory page, or NULL if allocation fails.
 */
static void *mm_get_new_vm_page_from_kernel(int units)
{
	char *vm_page = mmap(NULL, units * SYSTEM_PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, 0, 0);
	if (vm_page == MAP_FAILED) {
		printf("Error : VM page allocation Failed\n");
		return NULL;
	}

	memset(vm_page, 0, units * SYSTEM_PAGE_SIZE);
	return (void *)vm_page;
}

/**
 * @brief Return a virtual memory page to the kernel.
 *
 * @param vm_page Pointer to the memory page to return.
 * @param units Number of units to deallocate (multiples of system page size).
 */
static void mm_return_page_to_kernel(void *vm_page, int units)
{
	if (munmap(vm_page, units * SYSTEM_PAGE_SIZE) != 0) {
		printf("Error : could not munmap VM page to kernel\n");
	}
}

void mm_instantiate_new_page_family(char *struct_name, uint32_t struct_size) 
{
	vm_page_family_t *vm_page_family_curr = NULL;
	vm_page_for_families_t *new_vm_page_for_families = NULL;

	if (struct_size > SYSTEM_PAGE_SIZE) {
		printf
		    ("Error : %s() structure %s size exceeds system page size\n", __FUNCTION__, struct_name);
	}

	if (!first_vm_page_for_families) {
		first_vm_page_for_families = (vm_page_for_families_t *)mm_get_new_vm_page_from_kernel(1);

		first_vm_page_for_families->next = NULL;

		strncpy(first_vm_page_for_families->vm_page_family[0].struct_name, struct_name, MM_MAX_STRUCT_NAME);

		first_vm_page_for_families->vm_page_family[0].struct_size = struct_size;
		return; 
	}

	uint32_t count = 0;

	ITERATE_PAGE_FAMILIES_BEGIN(first_vm_page_for_families, vm_page_family_curr) {
		if (strncmp(vm_page_family_curr->struct_name, struct_name, MM_MAX_STRUCT_NAME) != 0) {
			count++;
			continue;
		}

		assert(0);
	} ITERATE_PAGE_FAMILIES_END(first_vm_page_for_families, vm_page_family_curr);

	if (count == (uint32_t)MAX_FAMILIES_PER_VM_PAGE) {
		new_vm_page_for_families = (vm_page_for_families_t *)mm_get_new_vm_page_from_kernel(1);
		new_vm_page_for_families->next = first_vm_page_for_families;
		first_vm_page_for_families = new_vm_page_for_families;
	}	
}

int main(int argc, char *argv[])
{
  /**< Initialize memory manager. */
	mm_init();

  /**< Print the size of the virtual memory page. */
	printf("VM page size = %lu\n", SYSTEM_PAGE_SIZE);

  /**< Requests and allocates two new virtual memory pages from the kernel using
   * the memory manager. */
	void *addr1 = mm_get_new_vm_page_from_kernel(1);
	void *addr2 = mm_get_new_vm_page_from_kernel(1);

  /**< Prints the addresses of the two allocated memory pages. */
	printf("Page 1 = %p, Page 2 = %p\n", addr1, addr2);

	return 0;
}
