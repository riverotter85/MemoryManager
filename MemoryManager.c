#include "MemoryManager.h"

#include <sys/mman.h>
#include <stdlib.h>

void* mem_manager_malloc(int size)
{
    void* ptr = NULL;

    mmfree_t* split;
    if (split = locate_split(size))
    {
        split->size -= size;
        hptr = (mmfree_t *) split + split->size;
        hptr->size = size - sizeof(mmfree_t);
        hptr->next = NULL;
        ptr = hptr + sizeof(mmfree_t); // NOTE: Check this!!!
    }

    return ptr;
}

// NOTE: Also make sure to check this bad boy!!
// This stuff is extremely importaaaannnnttt!!!!
void mem_manager_free(void* ptr)
{
    mmfree_t* hptr = (mmfree_t *) ptr - sizeof(mmfree_t);
    mmfree_t* sorted_loc = find_sorted_location(hptr);
    if (sorted_loc + sizeof(mmfree_t) + sorted_loc->size == hptr)
    {
        sorted_loc->size += hptr->size + sizeof(mmfree_t);
    }
    else
    {
        hptr->next = sorted_loc->next;
        sorted_loc->next = hptr;
    }
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
    head = (mmfree_t *) mmap(NULL, free_space_size, PROT_READ|PROT_WRITE,
                MAP_ANON|MAP_PRIVATE, -1, 0);
    head->size = free_space_size - sizeof(mmfree_t);
    head->next = NULL;
}

// Implemented using First Fit
mmfree_t* locate_split(int size)
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

// NOTE: Make sure that the calculations for this function
// is correct! This is super important!!!
mmfree_t* find_sorted_location(void* ptr)
{
    mmfree_t* curr = head;
    while (curr != NULL)
    {
        if (curr->next > ptr)
            break;
        curr = curr->next;
    }

    return curr;
}
