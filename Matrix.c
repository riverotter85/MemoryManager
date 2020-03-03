#include "Matrix.h"

#include "MemoryHeader.h"

#include <stdio.h>
#include <stdlib.h>

matrix* matrix_malloc(int num_rows, int num_cols)
{
    if (num_rows <= 0 || num_cols <= 0)
    {
        printf("Invalid dimension values passed! Aborting.\n\n");
        return NULL;
    }

    matrix* mat;
    double* elements;

    // Make sure that the matrix was allocated correctly
    if (!(mat = (matrix *) mem_manager_malloc(sizeof(matrix))))
    {
        printf("An error occured while allocating matrix! Aborting.\n\n");
        return NULL;
    }

    // Also do the same for the matrix elements
    if (!(elements = (double *) mem_manager_malloc(num_rows * num_cols * sizeof(double))))
    {
        printf("An error occured while allocating matrix elements! Aborting.\n\n");
        mem_manager_free(mat);
        return NULL;
    }

    // Initialize all matrix elements to 0
    for (int i = 0; i < num_rows * num_cols; i++)
        elements[i] = 0;

    mat->elements = elements;
    mat->num_rows = num_rows;
    mat->num_cols = num_cols;

    return mat;
}

void matrix_free(matrix* mat)
{
    if (!mat)
    {
        printf("Attempting to free NULL matrix! Aborting.\n\n");
        return;
    }

    mem_manager_free(mat->elements);
    mem_manager_free(mat);
}

void set_element(matrix* mat, int row, int col, double val)
{
    if (!mat)
    {
        printf("NULL matrix value passed! Aborting.\n\n");
        return;
    }

    if (row < 0 || row >= mat->num_rows || col < 0 || col >= mat->num_cols)
    {
        printf("Element index out of range!\n\n");
        return;
    }

    int index = row * mat->num_cols + col;
    mat->elements[index] = val;
}

double get_element(matrix* mat, int row, int col)
{
    if (!mat)
    {
        printf("NULL matrix value passed! Aborting.\n\n");
        return -1;
    }

    if (row < 0 || row >= mat->num_rows || col < 0 || col >= mat->num_cols)
    {
        printf("Element index out of range!\n\n");
        return -1;
    }

    int index = row * mat->num_cols + col;
    return mat->elements[index];
}

matrix* multiply(matrix* left, matrix* right)
{
    if (!left || !right)
    {
        printf("NULL value(s) passed for matrix multiply! Aborting.\n\n");
        return NULL;
    }

    int left_rows = left->num_rows;
    int left_cols = left->num_cols;
    int right_rows = right->num_rows;
    int right_cols = right->num_cols;

    // Make sure that we allocate our multiplication matrix correctly
    matrix* result;
    if (!(result = matrix_malloc(left_rows, right_cols)))
        return NULL;

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
        printf("NULL matrix!\n\n");
        return;
    }

    printf("Matrix Addr: %p\n", mat);
    printf("Elements Addr: %p\n", mat->elements);
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
