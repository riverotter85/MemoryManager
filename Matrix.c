#include "Matrix.h"

#include "MemoryManager.h"

#include <stdio.h>
#include <stdlib.h>

matrix* matrix_malloc(int num_rows, int num_cols)
{
    if (num_rows <= 0 || num_cols <= 0)
        return NULL;

    matrix* mat = (matrix *) mem_manager_malloc(sizeof(matrix));
    //matrix* mat = (matrix *) malloc(sizeof(matrix));

    double* elements = (double *) mem_manager_malloc(num_rows * num_cols * sizeof(double));
    //double* elements = (double *) malloc(num_rows * num_cols * sizeof(double));

    for (int i = 0; i < num_rows * num_cols; i++)
        elements[i] = 0;

    mat->elements = elements;
    mat->num_rows = num_rows;
    mat->num_cols = num_cols;

    return mat;
}

void matrix_free(matrix* mat)
{
    // NOTE: Check this!!
    mem_manager_free(mat->elements);
    mem_manager_free(mat);
    //free(mat->elements);
    //free(mat);
}

void set_element(matrix* mat, int row, int col, double val)
{
    if (row < 0 || row >= mat->num_rows || col < 0 || col >= mat->num_cols)
        return;

    int index = row * mat->num_cols + col;
    mat->elements[index] = val;
}

double get_element(matrix* mat, int row, int col)
{
    if (row < 0 || row >= mat->num_rows || col < 0 || col >= mat->num_cols)
        return 0;

    int index = row * mat->num_cols + col;
    return mat->elements[index];
}

matrix* multiply(matrix* left, matrix* right)
{
    int left_rows = left->num_rows;
    int left_cols = left->num_cols;
    int right_rows = right->num_rows;
    int right_cols = right->num_cols;
    matrix* result = matrix_malloc(left_rows, right_cols);

    for (int i = 0; i < left_rows; i++)
    {
        for (int j = 0; j < right_cols; j++)
        {
            double val = 0;
            for (int k = 0; k < left_cols; k++)
            {
                double element_left = get_element(left, i, k);
                double element_right = get_element(right, k, j);
                double mul = element_left * element_right;
                val += mul;
            }
            set_element(result, i, j, val);
        }
    }

    return result;
}

void display(matrix* mat)
{
    if (!mat)
    {
        printf("NULL!\n");
        return;
    }

    printf("Rows: %d\n", mat->num_rows);
    printf("Cols: %d\n", mat->num_cols);

    for (int i = 0; i < mat->num_rows; i++)
    {
        printf("%f", mat->elements[i * mat->num_cols]);
        for (int j = 1; j < mat->num_cols; j++)
            printf(", %f", mat->elements[i * mat->num_cols + j]);
        printf("\n");
    }
}
