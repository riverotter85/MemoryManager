#include <sys/mman.h>

typedef struct __mmalloc_t
{
    int size;
    int magic;
} mmalloc_t;

typedef struct __mmfree_t
{
    int size;
    struct __mmfree_t* next;
} mmfree_t;

mmfree_t* head;

void* mem_manager_malloc(int size);
void mem_manager_free(void* ptr);
// traverse the free space list starting from the head, printing out info (for debugging)
void traverse_free_list();
void init_mem(int free_space_size);

// called by malloc
// find a free space chunk large enough for the requested allocation
// obtain some memory from that chunk
mmfree_t* locate_split(int size);

// called by free
// locate the freed memory insert position so free space nodes are sorted by address
// ?? find_sorted_location(??);
