#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

#define ARG_ERR -1
#define DATA_ERR -2
#define NOT_SQUARE -3
#define ALLOCATION_ERR -4

typedef double my_num_t;
#define ScMyNum "%lf" 
#define PrMyNum "%lf"

typedef struct Matrix {
    size_t rows;
    size_t cols;
    my_num_t **data;
} Matrix;


void get_minor(const Matrix* src, Matrix* dst, size_t cur_col, size_t cur_row);

// Init/release operations
Matrix* create_matrix_from_file(const char* path_file);  //  +
Matrix* create_matrix(size_t rows, size_t cols);  //  +
int free_matrix(Matrix* matrix);  //  +

// Basic operations
int get_rows(const Matrix* matrix, size_t* rows);  //  +
int get_cols(const Matrix* matrix, size_t* cols);  //  +
int get_elem(const Matrix* matrix, size_t row, size_t col, double* val);  //  +
int set_elem(Matrix* matrix, size_t row, size_t col, double val);  //  +

//Math operations
Matrix* mul_scalar(const Matrix* matrix, double val);  //  +
Matrix* transp(const Matrix* matrix);  //  +

Matrix* sum(const Matrix* l, const Matrix* r);  //  +
Matrix* sub(const Matrix* l, const Matrix* r);  //  +
Matrix* mul(const Matrix* l, const Matrix* r);  //  +

// Extra operations
int det(const Matrix* matrix, double* val);
Matrix* adj(const Matrix* matrix);
Matrix* inv(const Matrix* matrix);


#endif //_MATRIX_H_
