#include "MemoryManager.h"

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>

void* mem_manager_malloc(int size)
{
    void* ptr = NULL;

    mmfree_t* split;
    if (split = locate_split(size - sizeof(mmalloc_t)))
    {
        split->size -= size;
        //mmalloc_t* hptr = (mmalloc_t *) split + sizeof(mmfree_t) + split->size;
        mmalloc_t* hptr = mmap(split + sizeof(mmfree_t) + split->size, sizeof(mmalloc_t),
                PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
        hptr->size = size - sizeof(mmalloc_t);
        printf("Memory allocated!\n");
        hptr->magic = 1234567; // May want to change!!
        ptr = hptr + sizeof(mmalloc_t); // NOTE: Check this!!!
    }

    return ptr;
}

// NOTE: Also make sure to check this bad boy!!
// This stuff is extremely importaaaannnnttt!!!!
void mem_manager_free(void* ptr)
{
    mmalloc_t* hptr = (mmalloc_t *) ptr - sizeof(mmalloc_t);
    mmfree_t* sorted_loc = find_sorted_location(hptr);
    if ((void *) (sorted_loc + sizeof(mmfree_t) + sorted_loc->size) == (void *) hptr)
    {
        printf("Yo!\n");
        munmap(hptr, sizeof(mmalloc_t));
        sorted_loc->size += hptr->size + sizeof(mmalloc_t);
    }
    else
    {
        //printf("Yo!\n");
        int size = hptr->size;
        munmap(hptr, sizeof(mmalloc_t));
        //mmfree_t* new_free = (mmfree_t *) ptr - sizeof(mmalloc_t);
        mmfree_t* new_free = mmap(hptr, sizeof(mmfree_t),
                PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
        new_free->size = size + sizeof(mmalloc_t) - sizeof(mmfree_t);
        new_free->next = sorted_loc->next;
        sorted_loc->next = new_free;
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
    head = mmap(NULL, free_space_size, PROT_READ|PROT_WRITE,
                MAP_ANON|MAP_PRIVATE, -1, 0);
    head->size = free_space_size - sizeof(mmfree_t);
    head->next = NULL;
}

void free_mem(int space_size)
{
    munmap(head, space_size);
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
    while (curr->next != NULL)
    {
        if ((void *) curr->next > (void *) ptr)
            break;
        curr = curr->next;
    }

    return curr;
}
