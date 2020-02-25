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
    mmfree_t* curr = head;
    while (curr != NULL)
    {
        // NOTE: May want to change this!!!!
        printf("curr: %p\n", curr + sizeof(mmfree_t));
        printf("size: %d\n", curr->size);
    }
}

void init_mem(int free_space_size)
{
    head = mmap(NULL, free_space_size, PROT_READ|PROT_WRITE,
                MAP_ANON|MAP_PRIVATE, -1, 0);
    head->size = free_space_size - sizeof(mmfree_t);
    head->next = NULL;
}

// Implemented using First Fit
__mmfree_t* locate_split(int size)
{
    mmfree_t* curr = head;
    while (curr != NULL)
    {
        if (curr->size >= size)
            break;
        curr = curr->next;
    }

    return curr;
}

// ?? find_sorted_location(??);
