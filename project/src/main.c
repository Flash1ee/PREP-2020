#include <stdio.h>
#include <matrix.h>

#include "utils.h"
#include "units.h"

#define matrix_test "matrix_test.txt"


int main(void) {
    size_t rows = 1;
    size_t cols = 1;

    Matrix *src = create_matrix(rows, cols);

    src->data[0][0] = -100.0;

    Matrix *inverse = inv(src);

    puts("SRC:");
    print_matrix(src);
    puts("INVERSE:");
    print_matrix(inverse);

    free_matrix(src);
    free_matrix(inverse);

    test_create_matrix_from_file(matrix_test);
    test_get_cols_rows();
    test_get_set_elem();
    test_mul_sub_sum();


    return 0;
}

