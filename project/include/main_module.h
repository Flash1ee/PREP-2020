#ifndef PROJECT_INCLUDE_MAIN_MODULE_H_
#define PROJECT_INCLUDE_MAIN_MODULE_H_

#include <stdio.h>
#include <string.h>
#include "types.h"
#include "io.h"

#define LEN_(X) #X
#define LEN(X) LEN_(X)


#define client_file "record_test.dat"
#define transaction_file "transaction_test.dat"

#define NOT_EQUAL -1
#define SUCCESS 0

void write_to_file(const char *filename, Data *data);
void read_from_file(const char *filename, Data *data);
void test_write_to_file();
int compare_data(Data *one, Data *two);


#endif  //  PROJECT_INCLUDE_MAIN_MODULE_H_
