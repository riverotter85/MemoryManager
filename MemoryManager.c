#include "MemoryManager.h"

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>

void* mem_manager_malloc(int size)
{
    void* ptr = NULL;

    mmfree_t* split;
    if (split = locate_split(size + sizeof(mmalloc_t)))
    {
        split->size -= size + sizeof(mmalloc_t);
        mmalloc_t* hptr = (mmalloc_t *) (((size_t) split) + sizeof(mmfree_t) + split->size);
        //mmalloc_t* hptr = mmap(split + sizeof(mmfree_t) + split->size, sizeof(mmalloc_t),
        //        PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
        printf("Split %p\n", split);
        printf("Split size %d\n", split->size);
        printf("mmfree_t size: %d\n", sizeof(mmfree_t));
        printf("Memory allocated!: %p\n", hptr);
        printf("Difference: %d\n", (int) ((void *) hptr - (void *) split));
        hptr->size = size;
        hptr->magic = 1234567; // May want to change!!
        ptr = (void *) ((size_t) hptr) + sizeof(mmalloc_t); // NOTE: Check this!!!
    }

    return ptr;
}

// NOTE: Also make sure to check this bad boy!!
// This stuff is extremely importaaaannnnttt!!!!
void mem_manager_free(void* ptr)
{
    mmalloc_t* hptr = (mmalloc_t *) (((size_t) ptr) - sizeof(mmalloc_t));
    printf("Curr: %p\n", hptr);
    printf("Size: %d\n", hptr->size);
    printf("Magic: %d\n", hptr->magic);

    mmfree_t* sorted_loc = find_sorted_location(hptr);
    printf("Sorted Location: %p\n", (void *) sorted_loc);
    printf("Sorted Location Offset: %p\n", (void *) (((size_t) sorted_loc) + sorted_loc->size));
    printf("Header Pointer Location: %p\n", (void *) hptr);

    if ((void *) (((size_t) sorted_loc) + sizeof(mmfree_t) + sorted_loc->size) == (void *) hptr)
    {
        printf("Yo!\n");
        //munmap(hptr, sizeof(mmalloc_t));
        sorted_loc->size += hptr->size + sizeof(mmalloc_t);
    }
    else
    {
        //printf("Yo!\n");
        //munmap(hptr, sizeof(mmalloc_t));
        //mmfree_t* new_free = (mmfree_t *) ((size_t) ptr) - sizeof(mmalloc_t);
        mmfree_t* new_free = (mmfree_t *) hptr;
        printf("New free location: %p\n", new_free);
        //mmfree_t* new_free = mmap(hptr, sizeof(mmfree_t),
        //        PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
        new_free->size = hptr->size + sizeof(mmalloc_t) - sizeof(mmfree_t);
        new_free->next = sorted_loc->next;
        sorted_loc->next = new_free;

        sorted_loc = new_free; // Doesn't affect values but is used for next block
    }
    
    mmfree_t* next = sorted_loc->next;
    if ((void *) (((size_t) sorted_loc) + sizeof(mmfree_t) + sorted_loc->size) == (void *) next)
    {
        printf("Howdy!\n");
        int next_size = next->size;
        sorted_loc->next = next->next;
        //munmap(next, sizeof(mmfree_t));
        sorted_loc->size += next_size + sizeof(mmfree_t);
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

// NOTE: Make sure that the calculations for this function
// is correct! This is super important!!!
mmfree_t* find_sorted_location(void* ptr)
{
    mmfree_t* curr = head;
    while (curr->next != NULL)
    {
        if ((void *) curr->next > (void *) ptr) {
            printf("Found sorted location for address %p: %p\n", ptr, curr);
            break;
        }
        curr = curr->next;
    }

    return curr;
}
