#ifndef PROJECT_INCLUDE_TYPES_H_
#define PROJECT_INCLUDE_TYPES_H_


#define NAME 20
#define SURNAME 20
#define ADDRES 30
#define TELNUM 15

typedef struct {
        int number;
        char name[NAME];
        char surname[SURNAME];
        char addres[ADDRES];
        char tel_number[TELNUM];
        double indebtedness;
        double credit_limit;
        double cash_payments;
} Data;




#endif  //  PROJECT_INCLUDE_TYPES_H_
