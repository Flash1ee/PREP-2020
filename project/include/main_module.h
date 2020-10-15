#ifndef PROJECT_INCLUDE_MAIN_MODULE_H_
#define PROJECT_INCLUDE_MAIN_MODULE_H_

#include <stdio.h>
#include <string.h>

#define LEN_(X) #X

#define LEN(X) LEN_(X)

#define NAME 19
#define SURNAME 19
#define ADDRES 29
#define TELNUM 14

#define client_file "record_test.dat"
#define transaction_file "transaction_test.dat"

#define NOT_EQUAL -1
#define SUCCESS 0
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
void write_to_file(const char *filename, Data *data);
void read_from_file(const char *filename, Data *data);
void test_write_to_file();
int compare_data(Data *one, Data *two);


#endif  //  PROJECT_INCLUDE_MAIN_MODULE_H_
