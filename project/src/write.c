#include "write.h"

#include "io.h"

int write_client_file() {
    FILE* client_file = fopen("record.dat", "w");
    if (!client_file) {
        return OPEN_ERR;
    }
    Data client = {};
    int rc = 0;
    while (TRUE) {
        client_info();
        rc = client_input(stdin, &client);
        if (rc == EOF || rc != CLIENT_ARGS) {
            break;
        }
        client_out(client_file, &client);
    }
    fclose(client_file);
    return rc;
}
int write_transaction_file() {
    FILE* transaction_file = fopen("transaction.dat", "w");
    if (!transaction_file) {
        return OPEN_ERR;
    }
    Data transfer = {};
    int rc = 0;
    while (TRUE) {
        transaction_info();
        int rc = transaction_input(stdin, &transfer);
        if (rc == EOF || rc != TRANSACTION_ARGS) {
            break;
        }
        transaction_out(transaction_file, &transfer);
    }
    fclose(transaction_file);
    return rc;
}
int write_blackrecord_file() {
    FILE* client_file = fopen("record.dat", "r");
    if (!client_file) {
        puts("Can't open file record.dat.");
        return OPEN_ERR;
    }
    FILE* transaction_file = fopen("transaction.dat", "r");
    if (!transaction_file) {
        puts("Can't open file transaction.dat.");
        fclose(client_file);
        return OPEN_ERR;
    }
    FILE* blackrecord_file = fopen("blackrecord.dat", "w");
    if (!blackrecord_file) {
        puts("Can't open file blackrecord.dat.");
        fclose(client_file);
        fclose(transaction_file);
        return OPEN_ERR;
    }
    Data client = {};
    Data transfer = {};
    int rc = 0;
    while (TRUE) {
        int rc = client_input(client_file, &client);
        if (rc == EOF || rc != CLIENT_ARGS) {
            break;
        }
        while (TRUE) {
            rc = transaction_input(transaction_file, &transfer);
            if (rc == EOF || rc != TRANSACTION_ARGS) {
                break;
            }
            if (client.number == transfer.number && transfer.cash_payments != 0) {
                client.credit_limit += transfer.cash_payments;
            }
        }
        blackrecord_out(blackrecord_file, &client);
        rewind(transaction_file);
    }
    fclose(client_file);
    fclose(transaction_file);
    fclose(blackrecord_file);
    return rc;
}
