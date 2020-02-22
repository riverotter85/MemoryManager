#include "Matrix.h"

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
