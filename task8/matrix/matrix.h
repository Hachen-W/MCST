#ifndef MATRIX_H
#define MATRIX_H


#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    size_t rows;
    size_t cols;
    double *data;
} Matrix;


Matrix matrix_create(size_t rows, size_t cols);
void matrix_free(Matrix *m);

int matrix_is_valid(const Matrix *m);

double matrix_get(const Matrix *m, size_t row, size_t col);
void matrix_set(Matrix *m, size_t row, size_t col, double value);

int matrix_fill(Matrix *m, double value);
int matrix_input(Matrix *m);
void matrix_print(const Matrix *m);

Matrix matrix_add(const Matrix *a, const Matrix *b);
Matrix matrix_sub(const Matrix *a, const Matrix *b);
Matrix matrix_mul(const Matrix *a, const Matrix *b);
Matrix matrix_transpose(const Matrix *m);


#endif