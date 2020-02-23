#include "Matrix.h"

#include <stdio.h>
#include <stdlib.h>

matrix* matrix_malloc(int num_rows, int num_cols)
{
    matrix* mat = (matrix *) malloc(sizeof(matrix));

    elements = (double *) malloc(num_rows * num_cols * sizeof(double));

    mat->elements = elements;
    mat->num_rows = num_rows;
    mat->num_cols = num_cols;

    return mat;
}

void matrix_free(matrix* mat)
{
    // NOTE: Check this!!
    free(mat->elements);
    free(mat);
}

void set_element(matrix* mat, int row, int col, double val)
{
    // NOTE: Check this!!
    int index = row * mat->num_cols + col;
    mat->elements[index] = val;
}

double get_element(matrix* mat, int row, int col)
{
    // NOTE: Check this!!
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

    for (int i = 1; i <= left_rows; i++)
    {
        for (int j = 1; j <= right_cols; j++)
        {
            double val = 0;
            for (int k = 1; k <= left_cols; k++)
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
    if (mat->num_rows == 0 || mat->num_cols == 0)
        return;

    int arr_size = mat->num_cols * 8; // NOTE: May want to tweak this!
    char str[arr_size];

    for (int i = 0; i < mat->num_rows; i++)
    {
        printf("%f", str[i * mat->num_cols]);
        for (int j = 0; j < mat->num_cols; j++)
            printf(", %f", str[i * mat->num_cols + j]);
    }
}
