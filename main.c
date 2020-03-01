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

    matrix* m1 = matrix_malloc(4, 4);
    matrix* m2 = matrix_malloc(8, 5);
    set_element(m2, 2, 4, 12);
    matrix* m3 = matrix_malloc(5, 8);
    set_element(m3, 4, 2, 3);
    matrix* m4 = multiply(m2, m3);

    display(m1);
    display(m2);
    display(m3);
    display(m4);

    matrix_free(m1);
    matrix_free(m2);
    matrix_free(m3);
    matrix_free(m4);

    free_mem(FREE_SPACE_BYTES);
    return 0;
}
