#include "MemoryManager.h"

#include <stdlib.h>

void* mem_manager_malloc(int size)
{
    //stuff
}

void mem_manager_free(void* ptr)
{
    //stuff
}

void traverse_free_list()
{
    //stuff
}

void init_mem(int free_space_size)
{
    head = mmap(NULL, free_space_size, PROT_READ|PROT_WRITE,
                MAP_ANON|MAP_PRIVATE, -1, 0);
    head->size = free_space_size - sizeof(mmfree_t);
    head->next = NULL;
}

// ?? locate_split(??);

// ?? find_sorted_location(??);
