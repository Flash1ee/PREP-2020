#include "check_correct.h"

int compare_data(const Data *one, const Data *two) {
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
int test_read_write_client() {
    const Data client_test = {1, "Vasya", "Pupkin", "Moscow", "88005553535", 200.00, 1000.00, 50.00};
    const Data expect = {1, "Vasya", "Pupkin", "Moscow", "88005553535", 200.00, 1000.00, 50.00};
    Data got_data = {};

    FILE *client_data = fopen(CLIENT_FILE, "w");
    if (!client_data) {
        return EXIT_FAILURE;
    }
    client_out(client_data, &client_test);
    fclose(client_data);

    client_data = fopen(CLIENT_FILE, "r");
    if (!client_data) {
        return EXIT_FAILURE;
    }
    client_input(client_data, &got_data);
    fclose(client_data);

    int rc = compare_data(&expect, &got_data);
    if (!rc) {
        puts("TEST_WRITE_RECORD ---- SUCCESS...");
        return EXIT_FAILURE;
    } else {
        puts("TEST_WRITE_RECORD ---- FAILED...");
        return EXIT_SUCCESS;
    }
}
int test_read_write_transaction() {
    const Data transaction_test = {.number = 1, .cash_payments = 200};
    const Data expect = {.number = 1, .cash_payments = 200};
    Data got_data = {};

    FILE *transaction_file = fopen(TRANSACTION_FILE, "w");
    if (!transaction_file) {
        return EXIT_FAILURE;
    }
    transaction_out(transaction_file, &transaction_test);
    fclose(transaction_file);

    transaction_file = fopen(TRANSACTION_FILE, "r");
    if (!transaction_file) {
        return EXIT_FAILURE;
    }
    transaction_input(transaction_file, &got_data);
    fclose(transaction_file);

    int rc = compare_data(&expect, &got_data);
    if (!rc) {
        puts("TEST_WRITE_TRANSACTION ---- SUCCESS...");
        return EXIT_FAILURE;
    } else {
        puts("TEST_WRITE_TRANSACTION ---- FAILED...");
        return EXIT_SUCCESS;
    }
}
int test_read_write_blackrecord() {
    const Data blackrecord_test = {1, "Vasya", "Pupkin", "Moscow", "88005553535", 200.00, 1000.00, 50.00};
    const Data expect = {1, "Vasya", "Pupkin", "Moscow", "88005553535", 200.00, 1000.00, 50.00};
    Data got_data = {};

    FILE *blackrecord_file = fopen(BLACKRECORD_FILE, "w");
    if (!blackrecord_file) {
        return EXIT_FAILURE;
    }
    blackrecord_out(blackrecord_file, &blackrecord_test);
    fclose(blackrecord_file);

    blackrecord_file = fopen(BLACKRECORD_FILE, "r");
    if (!blackrecord_file) {
        return EXIT_FAILURE;
    }
    blackrecord_input(blackrecord_file, &got_data);
    fclose(blackrecord_file);

    int rc = compare_data(&expect, &got_data);
    if (!rc) {
        puts("TEST_READ_WRITE_BLACKRECORD ---- SUCCESS...");
        return EXIT_FAILURE;
    } else {
        puts("TEST_READ_WRITE_BLACKRECORD ---- FAILED...");
        return EXIT_SUCCESS;
    }
}
int test_calculate_blackrecord() {
    const Data client_test = {1, "Vasya", "Pupkin", "Moscow", "88005553535", 200.00, 1000.00, 50.00};
    const Data transaction_data = {.number = 1, .cash_payments = 15};

    const Data expect = {1, "Vasya", "Pupkin", "Moscow", "88005553535", 200.00, 1015.00, 50.00};
    Data got_data = {};

    FILE *client_data = fopen(CLIENT_FILE, "w");
    if (!client_data) {
        return EXIT_FAILURE;
    }
    client_out(client_data, &client_test);
    fclose(client_data);

    FILE *transaction_file = fopen(TRANSACTION_FILE, "w");
    if (!transaction_file) {
        return EXIT_FAILURE;
    }
    transaction_out(transaction_file, &transaction_data);
    fclose(transaction_file);

    write_blackrecord_file();
    FILE *blackrecord_file = fopen(BLACKRECORD_FILE, "r");
    if (!blackrecord_file) {
        return EXIT_FAILURE;
    }
    client_input(blackrecord_file, &got_data);
    fclose(blackrecord_file);

    int rc = compare_data(&expect, &got_data);
    if (!rc) {
        puts("TEST_CALCULATE_BLACKRECORD ---- SUCCESS...");
        return EXIT_FAILURE;
    } else {
        puts("TEST_CALCULATE_BLACKRECORD ---- FAILED...");
        return EXIT_SUCCESS;
    }
}
int test_multy_calculate_blackrecord() {
    const Data client_test_frst = {1, "Vasya", "Pupkin", "Moscow", "88005553535", 200.00, 1000.00, 50.00};
    const Data client_test_second = {2, "Volodya", "Smirnov", "Samara", "664466", 100.00, 500.00, 10.00};
    const Data transaction_one = {.number = 2, .cash_payments = 10};
    const Data transaction_two = {.number = 1, .cash_payments = 200};

    const Data expect_one = {1, "Vasya", "Pupkin", "Moscow", "88005553535", 200.00, 1200.00, 50.00};
    const Data expect_two = {2, "Volodya", "Smirnov", "Samara", "664466", 100.00, 510.00, 10.00};
    Data got_data_one = {};
    Data got_data_two = {};

    FILE *client_data = fopen(CLIENT_FILE, "w");
    if (!client_data) {
        return EXIT_FAILURE;
    }
    client_out(client_data, &client_test_frst);
    client_out(client_data, &client_test_second);
    fclose(client_data);

    FILE *transaction_file = fopen(TRANSACTION_FILE, "w");
    if (!transaction_file) {
        return EXIT_FAILURE;
    }
    transaction_out(transaction_file, &transaction_one);
    transaction_out(transaction_file, &transaction_two);
    fclose(transaction_file);

    write_blackrecord_file();
    FILE *blackrecord_file = fopen(BLACKRECORD_FILE, "r");
    if (!blackrecord_file) {
        return EXIT_FAILURE;
    }
    client_input(blackrecord_file, &got_data_one);
    client_input(blackrecord_file, &got_data_two);
    fclose(blackrecord_file);

    int rc = compare_data(&expect_one, &got_data_one);
    rc += compare_data(&expect_two, &got_data_two);
    if (!rc) {
        puts("TEST_CALCULATE_MULTY_BLACKRECORD ---- SUCCESS...");
        return EXIT_FAILURE;
    } else {
        puts("TEST_CALCULATE_MULTY_BLACKRECORD ---- FAILED...");
        return EXIT_SUCCESS;
    }
}