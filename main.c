#include "MemoryManager.h"
#include "Matrix.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define FREE_SPACE_BYTES 4096
#define RANDOM_MAX 501

int main(int argc, char* argv[])
{
    if (argc < 2 || atoi(argv[1]) <= 0)
        return -1;

    int num_matrices = atoi(argv[1]);

    printf("mmalloc header size: %d\n", (int) sizeof(mmalloc_t));
    printf("mmfree node size: %d\n", (int) sizeof(mmfree_t));
    printf("Matrix size: %d\n", (int) sizeof(matrix));
    printf("double size: %d\n", (int) sizeof(double));

    srand(time(NULL));

    init_mem(FREE_SPACE_BYTES);

    matrix** m_list = (matrix **) mem_manager_malloc(num_matrices * sizeof(matrix *));

    for (int i = 0; i < num_matrices; i++)
    {
        int num_rows = (rand() % 10) + 1;
        int num_cols = (rand() % 10) + 1;
        m_list[i] = matrix_malloc(num_rows, num_cols);

        for (int j = 0; j < num_rows; j++)
        {
            for (int k = 0; k < num_cols; k++)
                set_element(m_list[i], j, k, rand() % RANDOM_MAX);
        }
    }

    for (int i = 0; i < num_matrices; i++)
    {
        int index1 = rand() % num_matrices;
        int index2 = rand() % num_matrices;

        matrix* temp = m_list[index1];
        m_list[index1] = m_list[index2];
        m_list[index2] = temp;
    }

    for (int i = 0; i < num_matrices; i++)
    {
        display(m_list[i]);
        traverse_free_list();
        matrix_free(m_list[i]);
    }
    traverse_free_list();

    mem_manager_free(m_list);
    traverse_free_list();

    free_mem(FREE_SPACE_BYTES);
    return 0;
}
