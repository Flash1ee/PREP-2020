#ifndef PROJECT_INCLUDE_TYPES_H_
#define PROJECT_INCLUDE_TYPES_H_


#define NAME 19
#define SURNAME 19
#define ADDRES 29
#define TELNUM 14

typedef struct {
        int number;
        char name[NAME + 1];
        char surname[SURNAME + 1];
        char addres[ADDRES + 1];
        char tel_number[TELNUM + 1];
        double indebtedness;
        double credit_limit;
        double cash_payments;
} Data;




#endif  //  PROJECT_INCLUDE_TYPES_H_
