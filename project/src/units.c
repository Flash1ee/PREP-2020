#include "units.h"

#include "matrix.h"

int equal_matrix(Matrix *first, Matrix *second) {
    if (first->rows != second->rows || first->cols != second->rows) {
        return NOT_EQUAL;
    }
    if (sizeof(*first) != sizeof(*second)) {
        return NOT_EQUAL;
    }
    if (!memcmp(first, second, sizeof(*first))) {
        return NOT_EQUAL;
    }
    return EQUAL;
}
int test_create_matrix_from_file(const char *filename) {
    size_t rows = 4;
    size_t cols = 4;
    Matrix *expected = create_matrix(rows, cols);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            expected->data[i][j] = i * cols + j;
        }
    }
    Matrix *matrix = create_matrix_from_file(filename);
    if (!matrix) {
        puts("CREATE_MATRIX_FROM_FILE -----FAILURE---");
        return EXIT_FAILURE;
    }
    if (equal_matrix(expected, matrix) == EQUAL) {
        puts("CREATE_MATRIX_FROM_FILE -----SUCCESS---");
        free_matrix(expected);
        free_matrix(matrix);
        return EXIT_SUCCESS;
    } else {
        puts("CREATE_MATRIX_FROM_FILE -----FAILURE---");
        free_matrix(expected);
        free_matrix(matrix);
        return EXIT_FAILURE;
    }
}

int test_get_cols_rows() {
    srand(time(NULL));
    unsigned int seed = time(NULL);
    size_t rows = rand_r(&seed) % 100;
    size_t cols = rand_r(&seed) % 100;

    Matrix *matrix = create_matrix(rows, cols);
    if (!matrix) {
        puts("GET_ROWS -----FAILURE---");
        puts("GET_COLS -----FAILURE---");
        return EXIT_FAILURE;
    }
    size_t rows_check = 0;
    size_t cols_check = 0;

    if (!get_rows(matrix, &rows_check) && rows_check == rows) {
        if (!get_cols(matrix, &cols_check) && cols_check == cols) {
            puts("GET_ROWS -----SUCCESS---");
            puts("GET_COLS -----SUCCESS---");
            free_matrix(matrix);
            return EXIT_SUCCESS;
        } else {
            puts("GET_ROWS -----FAILURE---");
            puts("GET_COLS -----FAILURE---");
            free_matrix(matrix);
            return EXIT_FAILURE;
        }
    }
    return EXIT_FAILURE;
}
int test_get_set_elem() {
    size_t rows = 4;
    size_t cols = 4;

    size_t col_check = 3;
    size_t row_check = 2;

    matrix_t value = 2020.;

    Matrix *matrix = create_matrix(rows, cols);
    if (!matrix) {
        puts("GET_SET_ELEM -----FAILURE---");
        return EXIT_FAILURE;
    }
    set_elem(matrix, row_check, col_check, value);

    matrix_t get_value = -1;
    if (!get_elem(matrix, row_check, col_check, &get_value) && get_value == value) {
        puts("GET_SET_ELEM -----SUCCESS---");
        free_matrix(matrix);
        return EXIT_SUCCESS;
    } else {
        puts("GET_SET_ELEM -----FAILURE---");
        free_matrix(matrix);
        return EXIT_FAILURE;
    }
}
int test_mul_sub_sum() {
    size_t rows = 4;
    size_t cols = 4;

    int rc = 0;
    Matrix *first = create_matrix(rows, cols);
    if (!first) {
        return EXIT_FAILURE;
    }
    Matrix *second = create_matrix(rows, cols);
    if (!second) {
        free_matrix(first);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            first->data[i][j] = i * cols + j;
            second->data[i][j] = i * cols + j;
        }
    }
    Matrix *res_sum = sum(first, second);
    Matrix *res_sub = sub(res_sum, first);
    rc = equal_matrix(res_sub, first);
    if (rc == EXIT_SUCCESS) {
        puts("EQUAL_MATRIX -----SUCCESS---");
    } else {
        puts("EQUAL_MATRIX -----FAILURE---");
    }
    res_sum = sub(first, second);
    Matrix *res_mul = mul(res_sum, res_sub);
    Matrix *zeroes = create_matrix(rows, cols);
    rc = equal_matrix(zeroes, res_mul);
    if (rc == EXIT_SUCCESS) {
        puts("MUL -----SUCCESS---");
    } else {
        puts("EQUAL_MATRIX -----FAILURE---");
    }
    free_matrix(first);
    free_matrix(second);
    free_matrix(res_sum);
    free_matrix(res_sub);
    free_matrix(res_mul);
    free_matrix(zeroes);
    return rc;
}
