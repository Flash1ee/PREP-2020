#ifndef PROJECT_INCLUDE_WRITE_H_
#define PROJECT_INCLUDE_WRITE_H_

#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "types.h"

void write_client_file(FILE * client_file);
void write_transaction_file(FILE * transaction_file);
void write_blackrecord_file(FILE * client_file, FILE * transaction_file, FILE * blackrecord_file);


#endif  //  PROJECT_INCLUDE_WRITE_H_
