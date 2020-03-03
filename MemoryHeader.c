#include "MemoryHeader.h"

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>

void* mem_manager_malloc(int size)
{
    // Check to see if the requested amount (plus allocated header size)
    // is available
    mmfree_t* split;
    if (!(split = locate_split(size + sizeof(mmalloc_t))))
        return NULL;

    split->size -= size + sizeof(mmalloc_t);
    mmalloc_t* hptr = (mmalloc_t *) (((size_t) split) + sizeof(mmfree_t) + split->size);
    hptr->size = size;
    hptr->magic = 1234567;

    // Retrieve space attached to header
    void* ptr = (void *) ((size_t) hptr) + sizeof(mmalloc_t);
    return ptr;
}

void mem_manager_free(void* ptr)
{
    if (!ptr) // NULL pointer
        return;

    // Retrieve the allocated header and make sure everything is intact
    mmalloc_t* hptr = (mmalloc_t *) (((size_t) ptr) - sizeof(mmalloc_t));
    printf("Node Freed!!\n");
    printf("#########################\n");
    printf("Curr: %p\n", hptr);
    printf("Size: %d\n", hptr->size);
    printf("Magic: %d\n\n", hptr->magic);
    printf("#########################\n\n");

    mmfree_t* sorted_loc = find_sorted_location(hptr);
    // Directly adjacent node found to the left! Coalesce freed space into node.
    if ((void *) (((size_t) sorted_loc) + sizeof(mmfree_t) + sorted_loc->size) == (void *) hptr)
    {
        sorted_loc->size += hptr->size + sizeof(mmalloc_t);
    }
    // Otherwise create new free node attached to space (including leftover mmalloc header space)
    else
    {
        mmfree_t* new_free = (mmfree_t *) hptr;
        new_free->size = hptr->size + sizeof(mmalloc_t) - sizeof(mmfree_t);
        new_free->next = sorted_loc->next;
        sorted_loc->next = new_free;

        sorted_loc = new_free; // Doesn't affect values but is used for next block
    }
    
    mmfree_t* next = sorted_loc->next;
    // Directly adjacent node found to the right! Coalesce right node into current node.
    if ((void *) (((size_t) sorted_loc) + sizeof(mmfree_t) + sorted_loc->size) == (void *) next)
    {
        sorted_loc->next = next->next;
        sorted_loc->size += next->size + sizeof(mmfree_t);
    }
}

void init_mem(int free_space_size)
{
    head = mmap(NULL, free_space_size, PROT_READ|PROT_WRITE,
                MAP_ANON|MAP_PRIVATE, -1, 0);
    head->size = free_space_size - sizeof(mmfree_t);
    head->next = NULL;
}

void free_mem(int space_size)
{
    munmap(head, space_size);
}

void traverse_free_list()
{
    printf("================================\n");
    printf("====       Free List        ====\n");
    printf("================================\n");
    printf("\tHead\n");

    mmfree_t* curr = head;
    while (curr != NULL)
    {
        printf("\t  |\n");
        printf("\t  V\n");
        printf("Addr: %p\n", curr);
        printf("Size: %d\n", curr->size);

        curr = curr->next;
    }

    printf("\t  |\n");
    printf("\t  V\n");
    printf("\tNULL\n");
    printf("\n================================\n\n");
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

// Finds the closest (sorted) node to the left of the provided pointer
mmfree_t* find_sorted_location(void* ptr)
{
    mmfree_t* curr = head;
    while (curr->next != NULL)
    {
        if ((void *) curr->next > (void *) ptr)
            break;
        curr = curr->next;
    }

    return curr;
}
