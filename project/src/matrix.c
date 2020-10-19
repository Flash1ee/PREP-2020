#include "matrix.h"

// NOTE(stitaevskiy): Place your implementation here
Matrix *create_matrix(size_t rows, size_t cols) {
    if (!rows || !cols || rows < 1 || cols < 1) {
        return NULL;
    }
    Matrix *matrix = (Matrix*) malloc(sizeof(Matrix));
    if (!matrix) {
        return NULL;
    }
    matrix->data = malloc(sizeof(my_num_t *) * rows);
    if (!matrix->data) {
        free(matrix);
        return NULL;
    }
    for (size_t i = 0; i < rows; i++) {
        matrix->data[i] = malloc((sizeof(my_num_t)*cols));
        if (!matrix->data[i]) {
            free_matrix(matrix);
            return NULL;
        }
    }
    matrix->rows = rows;
    matrix->cols = cols;
    return matrix;
}
