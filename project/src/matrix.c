#include "matrix.h"

// NOTE(stitaevskiy): Place your implementation here
Matrix* create_matrix(size_t rows, size_t cols) {
    if (!rows || !cols || rows < 1 || cols < 1) {
        return NULL;
    }
    Matrix* matrix = (Matrix*)calloc(1, sizeof(Matrix));
    if (!matrix) {
        return NULL;
    }
    matrix->data = calloc(rows, sizeof(my_num_t*));
    if (!matrix->data) {
        free(matrix);
        return NULL;
    }
    for (size_t i = 0; i < rows; i++) {
        matrix->data[i] = calloc(cols, sizeof(my_num_t));
        if (!matrix->data[i]) {
            free_matrix(matrix);
            return NULL;
        }
    }
    matrix->rows = rows;
    matrix->cols = cols;
    return matrix;
}
int free_matrix(Matrix* matrix) {
    if (!matrix) {
        return ARG_ERR;
    }
    for (size_t i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
    return EXIT_SUCCESS;
}

Matrix* create_matrix_from_file(const char* path_file) {
    if (!path_file) {
        return NULL;
    }
    FILE* in = fopen(path_file, "r");
    if (!in) {
        return NULL;
    }
    size_t rows = 0;
    size_t cols = 0;
    if (fscanf(in, "%zu %zu", &rows, &cols) != 2 || rows < 1 || cols < 1) {
        fclose(in);
        return NULL;
    }
    Matrix* matrix = create_matrix(rows, cols);
    if (!matrix) {
        fclose(in);
        return NULL;
    }
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (fscanf(in, ScMyNum, &(matrix->data[i][j])) != 1) {
                fclose(in);
                free_matrix(matrix);
                return NULL;
            }
        }
    }
    fclose(in);
    return matrix;
}
int get_rows(const Matrix* matrix, size_t* rows) {
    if (!matrix || !rows) {
        return ARG_ERR;
    }
    if (matrix->rows < 1) {
        return DATA_ERR;
    }
    *rows = matrix->rows;
    return EXIT_SUCCESS;
}
int get_cols(const Matrix* matrix, size_t* cols) {
    if (!matrix || !cols) {
        return ARG_ERR;
    }
    if (matrix->cols < 1) {
        return DATA_ERR;
    }
    *cols = matrix->cols;
    return EXIT_SUCCESS;
}
int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    if (!matrix || !val) {
        return ARG_ERR;
    }
    if (!matrix->data || matrix->rows < 1 || matrix->cols < 1) {
        return DATA_ERR;
    }
    if (row > matrix->rows - 1 || col > matrix->cols - 1) {
        return ARG_ERR;
    }
    *val = matrix->data[row][col];
    return EXIT_SUCCESS;
}
int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    if (!matrix) {
        return ARG_ERR;
    }
    if (!matrix->data || matrix->rows < 1 || matrix->cols < 1) {
        return DATA_ERR;
    }
    if (row > matrix->rows - 1 || col > matrix->cols - 1) {
        return ARG_ERR;
    }
    matrix->data[row][col] = val;
    return EXIT_SUCCESS;
}
Matrix* mul_scalar(const Matrix* matrix, double val) {
    if (!matrix) {
        return NULL;
    }
    if (!matrix->data || matrix->rows < 1 || matrix->cols < 1) {
        return NULL;
    }
    Matrix* res = create_matrix(matrix->rows, matrix->cols);
    if (!res) {
        return NULL;
    }
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            res->data[i][j] = matrix->data[i][j] * val;
        }
    }
    return res;
}
Matrix* transp(const Matrix* matrix) {
    if (!matrix) {
        return NULL;
    }
    if (!matrix->data || matrix->rows < 1 || matrix->cols < 1) {
        return NULL;
    }
    Matrix* res = create_matrix(matrix->cols, matrix->rows);
    if (!res) {
        return NULL;
    }
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            res->data[j][i] = matrix->data[i][j];
        }
    }
    return res;
}
Matrix* sum(const Matrix* l, const Matrix* r) {
    if (!l || !r) {
        return NULL;
    }
    if (!r->data || r->rows < 1 || r->cols < 1) {
        return NULL;
    }
    if (!l->data || l->rows < 1 || l->cols < 1) {
        return NULL;
    }
    if (l->rows != r->rows || l->cols != r->cols) {
        return NULL;
    }
    Matrix* res = create_matrix(r->rows, r->cols);
    if (!res) {
        return NULL;
    }
    for (size_t i = 0; i < res->rows; i++) {
        for (size_t j = 0; j < res->cols; j++) {
            res->data[i][j] = l->data[i][j] + r->data[i][j];
        }
    }
    return res;
}
Matrix* sub(const Matrix* l, const Matrix* r) {
    if (!l || !r) {
        return NULL;
    }
    if (!r->data || r->rows < 1 || r->cols < 1) {
        return NULL;
    }
    if (!l->data || l->rows < 1 || l->cols < 1) {
        return NULL;
    }
    if (l->rows != r->rows || l->cols != r->cols) {
        return NULL;
    }
    Matrix* res = create_matrix(r->rows, r->cols);
    if (!res) {
        return NULL;
    }
    for (size_t i = 0; i < res->rows; i++) {
        for (size_t j = 0; j < res->cols; j++) {
            res->data[i][j] = l->data[i][j] - r->data[i][j];
        }
    }
    return res;
}
Matrix* mul(const Matrix* l, const Matrix* r) {
    if (!l || !r) {
        return NULL;
    }
    if (!r->data || r->rows < 1 || r->cols < 1) {
        return NULL;
    }
    if (!l->data || l->rows < 1 || l->cols < 1) {
        return NULL;
    }
    if (l->cols != r->rows) {
        return NULL;
    }
    Matrix* res = create_matrix(l->rows, r->cols);
    if (!res) {
        return NULL;
    }
    for (size_t i = 0; i < l->rows; i++) {
        for (size_t j = 0; j < r->cols; j++) {
            for (size_t k = 0; k < l->cols; k++) {
                res->data[i][j] += l->data[i][k] * r->data[k][j];
            }
        }
    }
    return res;
}
int det(const Matrix* matrix, double* val) {
    if (!matrix || !val) {
        return ARG_ERR;
    }
    if (!matrix->data || matrix->cols < 1 || matrix->rows < 1) {
        return DATA_ERR;
    }
    if (matrix->rows != matrix->cols) {
        return NOT_SQUARE;
    }
    if (matrix->rows == 1) {
        *val = matrix->data[0][0];
        return EXIT_SUCCESS;
    } else if (matrix->rows == 2) {
        *val = (matrix->data[0][0] * matrix->data[1][1] - matrix->data[1][0] * matrix->data[0][1]);
        return EXIT_SUCCESS;
    } else {
        for (size_t el = 0; el < matrix->cols; el++) {
            Matrix* tmp = create_matrix(matrix->rows - 1, matrix->cols - 1);
            if (!tmp) {
                return ALLOCATION_ERR;
            }
            get_minor(matrix, tmp, el, 0);
            double cur = *val;
            *val = 0;
            det(tmp, val);
            *val = cur + (pow(-1, el) * matrix->data[0][el] * *val);
            free_matrix(tmp);
        }
    }
    return EXIT_SUCCESS;
}
void get_minor(const Matrix* src, Matrix* dst, size_t cur_col, size_t cur_row) {
    size_t dst_rows = 0;
    size_t dst_cols = 0;
    for (size_t i = 0; i < src->rows; i++) {
        if (i == cur_row) {
            continue;
        }
        dst_cols = 0;
        for (size_t j = 0; j < src->cols; j++) {
            if (j != cur_col) {
                dst->data[dst_rows][dst_cols] = src->data[i][j];
                dst_cols++;
            }
        }
        dst_rows++;
    }
}
// int det(const Matrix* matrix, double* val) {
//     if (!matrix) {
//         return ARG_ERR;
//     }
//     *val = *val;
//     return 0;
// }

Matrix* adj(const Matrix* matrix) {
    if (!matrix || !matrix->data) {
        return NULL;
    }
    if (matrix->rows < 1 || matrix->cols < 1 || matrix->rows != matrix->cols) {
        return NULL;
    }
    Matrix *matrix_adj = create_matrix(matrix->rows, matrix->cols);
    if (!matrix_adj) {
        return NULL;
    }
    return NULL;
}

Matrix* inv(const Matrix* matrix) {
    if (!matrix) {
        return NULL;
    }
    return NULL;
}