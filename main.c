#include "MemoryManager.h"
#include "Matrix.h"

#include <stdlib.h>
#include <stdio.h>

#define FREE_SPACE_BYTES 4096

int main()
{
    printf("mmalloc header size: %d\n", (int) sizeof(mmalloc_t));
    printf("mmfree node size: %d\n", (int) sizeof(mmfree_t));

    init_mem(FREE_SPACE_BYTES);

    matrix* m1 = matrix_malloc(4, 7);
    display(m1);
    matrix* m2 = matrix_malloc(7, 4);
    display(m2);
    //matrix* m3 = matrix_malloc(500, 4000);
    //display(m3);
    //matrix_free(m3);
    matrix* m4 = multiply(m1, m2);
    display(m4);
    matrix_free(m1);
    matrix_free(m2);
    matrix_free(m4);
    //matrix* m4 = matrix_malloc(-1, 0);
    //matrix_free(m4);

    free_mem(FREE_SPACE_BYTES);
    return 0;
}
