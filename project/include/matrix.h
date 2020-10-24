#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_

#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define ARG_ERR -1
#define DATA_ERR -2
#define NOT_SQUARE -3
#define ALLOCATION_ERR -4

#define ScMyNum "%lf"
#define PrMyNum "%lf"

typedef double my_num_t;
typedef struct Matrix {
    size_t rows;
    size_t cols;
    my_num_t** data;
} Matrix;

void get_minor(const Matrix* src, Matrix* dst, size_t cur_col, size_t cur_row);

// Init/release operations
Matrix* create_matrix_from_file(const char* path_file);
Matrix* create_matrix(size_t rows, size_t cols);
int free_matrix(Matrix* matrix);

// Basic operations
int get_rows(const Matrix* matrix, size_t* rows);
int get_cols(const Matrix* matrix, size_t* cols);
int get_elem(const Matrix* matrix, size_t row, size_t col, double* val);
int set_elem(Matrix* matrix, size_t row, size_t col, double val);

// Math operations
Matrix* mul_scalar(const Matrix* matrix, double val);
Matrix* transp(const Matrix* matrix);

Matrix* sum(const Matrix* lhs, const Matrix* rhs);
Matrix* sub(const Matrix* lhs, const Matrix* rhs);
Matrix* mul(const Matrix* lhs, const Matrix* rhs);

// Extra operations
int det(const Matrix* matrix, double* val);
Matrix* adj(const Matrix* matrix);
Matrix* inv(const Matrix* matrix);

#endif  //  PROJECT_INCLUDE_MATRIX_H_
