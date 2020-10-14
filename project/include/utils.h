#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

#include <stdlib.h>

#define BLACKRECORD_FILE "blackrecord.dat"
#define CLIENT_FILE "record.dat"
#define TRANSACTION_FILE "transaction.dat"

#define TRUE 1
#define CLIENT 1
#define TRANSACTION 2
#define BLACKRECORD 3
#define EXIT 4

#define NAME 19
#define SURNAME 19
#define ADDRES 29
#define TELNUM 14


#define LEN_(X) #X

#define LEN(X) LEN_(X)

#define CLIENT_ARGS 8
#define TRANSACTION_ARGS 2

typedef struct {
        int Number;
        char Name[NAME + 1];
        char Surname[SURNAME + 1];
        char addres[ADDRES + 1];
        char TelNumber[TELNUM + 1];
        double indebtedness;
        double credit_limit;
        double cash_payments;
} Data;


#endif  //  PROJECT_INCLUDE_UTILS_H_
