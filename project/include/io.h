#ifndef PROJECT_INCLUDE_IO_H_
#define PROJECT_INCLUDE_IO_H_

#include <stdio.h>
#include "types.h"

#define LEN_(X) #X
#define LEN(X) LEN_(X)

void client_info();
void transaction_info();
int client_input(FILE *stream, Data *client);
int client_out(FILE *stream, Data *client);
int transaction_input(FILE *stream, Data *transfer);
int transaction_out(FILE *stream, Data *transfer);
int blackrecord_out(FILE *stream, Data *client);

#endif  //  PROJECT_INCLUDE_IO_H_
