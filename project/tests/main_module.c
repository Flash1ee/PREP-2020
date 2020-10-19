#include "main_module.h"

int compare_data(Data *one, Data *two) {
    if (one->number - two->number || one->cash_payments - two->cash_payments) {
        return NOT_EQUAL;
    }
    if (one->indebtedness - two->indebtedness || one->credit_limit - two->credit_limit) {
        return NOT_EQUAL;
    }
    if (strcmp(one->name, two->name) || strcmp(one->surname, two->surname)) {
        return NOT_EQUAL;
    }
    if (strcmp(one->addres, two->addres) || strcmp(one->tel_number, two->tel_number)) {
        return NOT_EQUAL;
    }
    return SUCCESS;
}
void test_write_to_file() {
    const char *filename_client = client_file;

    Data expected_data;
    expected_data.number = 1;
    char *name_test = "Vasya";
    char *surname_test = "Pupkin";
    char *address_test = "Moscow";
    char *number_test = "88005553535";
    double indebtedness_test = 200.00;
    double credit_limit_test = 1000.00;
    double cash_payments_test = 50.00;

    strncpy(expected_data.name, name_test, strlen(name_test));
    strncpy(expected_data.surname, surname_test, strlen(surname_test));
    strncpy(expected_data.addres, address_test, strlen(address_test));
    strncpy(expected_data.tel_number, number_test, strlen(number_test));
    expected_data.indebtedness = indebtedness_test;
    expected_data.credit_limit = credit_limit_test;
    expected_data.cash_payments = cash_payments_test;

    write_to_file(filename_client, &expected_data);

    Data got_data;
    read_from_file(filename_client, &got_data);

    if (!compare_data(&expected_data, &got_data)) {
        printf("TEST_WRITE-READ_RECORD ---- SUCCESS...\n");
    } else {
        printf("TEST_WRITE-READ_RECORD ---- FAILED...\n");
    }

    const char *filename_transaction = transaction_file;

    write_to_file(filename_transaction, &expected_data);

    read_from_file(filename_client, &got_data);

    if (!compare_data(&expected_data, &got_data)) {
        printf("TEST_WRITE-READ_TRANSACTION ---- SUCCESS...\n");
    } else {
        printf("TEST_WRITE-READ_TRANSACTION ---- FAILED...\n");
    }
}
