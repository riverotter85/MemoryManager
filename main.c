#include "MemoryManager.h"
#include "Matrix.h"

#include <stdlib.h>
#include <stdio.h>

int main()
{
    printf("mmalloc header size: %d\n", sizeof(mmalloc_t));
    printf("mmfree node size: %d\n", sizeof(mmfree_t));

    return 0;
}
