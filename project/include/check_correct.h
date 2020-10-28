#ifndef PROJECT_INCLUDE_CHECK_CORRECT_H_
#define PROJECT_INCLUDE_CHECK_CORRECT_H_

#include <stdio.h>
#include <string.h>
#include "types.h"
#include "io.h"
#include "write.h"

#define CLIENT_FILE "record.dat"
#define TRANSACTION_FILE "transaction.dat"
#define BLACKRECORD_FILE "blackrecord.dat"

#define NOT_EQUAL -1
#define SUCCESS 0

int test_read_write_client();
int test_read_write_transaction();
int test_read_write_blackrecord();
int test_calculate_blackrecord();
int test_multy_calculate_blackrecord();
int compare_data(Data *one, Data *two);


#endif  //  PROJECT_INCLUDE_CHECK_CORRECT_H_
