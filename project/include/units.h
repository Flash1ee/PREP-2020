#ifndef PROJECT_INCLUDE_UNITS_H_
#define PROJECT_INCLUDE_UNITS_H_

#include <string.h>
#include <time.h>
#include <stdlib.h>

#define EQUAL 0
#define FILE_ERR -1
#define NOT_EQUAL -2

int test_create_matrix_from_file(const char *filename);
int test_get_cols_rows();
int test_get_set_elem();
int test_mul_sub_sum();



#endif  //  PROJECT_INCLUDE_UNITS_H_
