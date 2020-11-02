#ifndef PROJECT_INCLUDE_IO_H_
#define PROJECT_INCLUDE_IO_H_

#include <stdio.h>
#include "types.h"
#include "utils.h"

#define LEN_(X) #X
#define LEN(X) LEN_(X)

void client_info();
void transaction_info();
int client_input(FILE *stream, Data *client);
int client_out(FILE *stream, const Data *client);
int transaction_input(FILE *stream, Data *transfer);
int transaction_out(FILE *stream, const Data *transfer);
int blackrecord_input(FILE *stream, Data *client);
int blackrecord_out(FILE *stream, const Data *client);

#endif  //  PROJECT_INCLUDE_IO_H_
