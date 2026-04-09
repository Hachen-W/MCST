#include "matrix.h"


static size_t matrix_index(const Matrix *m, size_t row, size_t col)
{
    return row * m->cols + col;
}


Matrix matrix_create(size_t rows, size_t cols)
{
    Matrix m;
    m.rows = rows;
    m.cols = cols;
    m.data = NULL;

    if (rows == 0 || cols == 0)
        return m;

    m.data = (double *)malloc(rows * cols * sizeof(double));
    if (m.data == NULL)
    {
        m.rows = 0;
        m.cols = 0;
    }

    return m;
}


void matrix_free(Matrix *m)
{
    if (m == NULL)
        return;

    free(m->data);
    m->data = NULL;
    m->rows = 0;
    m->cols = 0;
}


int matrix_is_valid(const Matrix *m)
{
    return m != NULL && m->data != NULL && m->rows > 0 && m->cols > 0;
}


double matrix_get(const Matrix *m, size_t row, size_t col)
{
    return m->data[matrix_index(m, row, col)];
}


void matrix_set(Matrix *m, size_t row, size_t col, double value)
{
    m->data[matrix_index(m, row, col)] = value;
}


int matrix_fill(Matrix *m, double value)
{
    if (!matrix_is_valid(m))
        return 0;

    for (size_t i = 0; i < m->rows; i++)
        for (size_t j = 0; j < m->cols; j++)
            matrix_set(m, i, j, value);

    return 1;
}


int matrix_input(Matrix *m)
{
    if (!matrix_is_valid(m))
        return 0;

    for (size_t i = 0; i < m->rows; i++)
        for (size_t j = 0; j < m->cols; j++)
            if (scanf("%lf", &m->data[matrix_index(m, i, j)]) != 1)
                return 0;

    return 1;
}


void matrix_print(const Matrix *m)
{
    if (!matrix_is_valid(m))
    {
        printf("Invalid matrix\n");
        return;
    }

    for (size_t i = 0; i < m->rows; i++)
    {
        for (size_t j = 0; j < m->cols; j++)
            printf("%8.2f ", matrix_get(m, i, j));
        printf("\n");
    }
}


Matrix matrix_add(const Matrix *a, const Matrix *b)
{
    Matrix res = {0, 0, NULL};

    if (!matrix_is_valid(a) || !matrix_is_valid(b))
        return res;

    if (a->rows != b->rows || a->cols != b->cols)
        return res;

    res = matrix_create(a->rows, a->cols);
    if (!matrix_is_valid(&res))
        return res;

    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            matrix_set(&res, i, j, matrix_get(a, i, j) + matrix_get(b, i, j));

    return res;
}


Matrix matrix_sub(const Matrix *a, const Matrix *b)
{
    Matrix res = {0, 0, NULL};

    if (!matrix_is_valid(a) || !matrix_is_valid(b))
        return res;

    if (a->rows != b->rows || a->cols != b->cols)
        return res;

    res = matrix_create(a->rows, a->cols);
    if (!matrix_is_valid(&res))
        return res;

    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            matrix_set(&res, i, j, matrix_get(a, i, j) - matrix_get(b, i, j));

    return res;
}


Matrix matrix_mul(const Matrix *a, const Matrix *b)
{
    Matrix res = {0, 0, NULL};

    if (!matrix_is_valid(a) || !matrix_is_valid(b))
        return res;

    if (a->cols != b->rows)
        return res;

    res = matrix_create(a->rows, b->cols);
    if (!matrix_is_valid(&res))
        return res;

    for (size_t i = 0; i < a->rows; i++)
    {
        for (size_t j = 0; j < b->cols; j++)
        {
            double sum = 0.0;
            for (size_t k = 0; k < a->cols; k++)
                sum += matrix_get(a, i, k) * matrix_get(b, k, j);
            matrix_set(&res, i, j, sum);
        }
    }

    return res;
}


Matrix matrix_transpose(const Matrix *m)
{
    Matrix res = {0, 0, NULL};

    if (!matrix_is_valid(m))
        return res;

    res = matrix_create(m->cols, m->rows);
    if (!matrix_is_valid(&res))
        return res;

    for (size_t i = 0; i < m->rows; i++)
        for (size_t j = 0; j < m->cols; j++)
            matrix_set(&res, j, i, matrix_get(m, i, j));

    return res;
}
