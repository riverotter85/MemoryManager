#ifndef _MATRIX_H
#define _MATRIX_H

typedef struct __matrix
{
    int num_rows;
    int num_cols;
    double* elements;
} matrix;

matrix* matrix_malloc(int num_rows, int num_cols);
void matrix_free(matrix* mat);
void set_element(matrix* mat, int row, int col, double val);
double get_element(matrix* mat, int row, int col);
matrix* multiply(matrix* left, matrix* right);
void display(matrix* mat);

#endif
