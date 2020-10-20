#include "write.h"
#include "io.h"

void write_client_file(FILE *client_file) {
    Data client = {};
    while (TRUE) {
        client_info();
        int rc = client_input(stdin, &client);
        if (rc == -1 || rc != CLIENT_ARGS) {
            break;
        }
        client_out(client_file, &client);
    }
}
void write_transaction_file(FILE *transaction_file) {
    Data transfer = {};
    while (TRUE) {
        transaction_info();
        int rc = transaction_input(stdin, &transfer);
        if (rc == -1 || rc != TRANSACTION_ARGS) {
            break;
        }
        transaction_out(transaction_file, &transfer);
    }
}
void write_blackrecord_file(FILE *client_file, FILE *transaction_file, FILE *blackrecord_file) {
    Data client = {};
    Data transfer = {};
    while (TRUE) {
        int rc = client_input(client_file, &client);
        if (rc == -1 || rc != CLIENT_ARGS) {
            return;
        }
        while (TRUE) {
            rc = transaction_input(transaction_file, &transfer);
            if (rc == -1 || rc != TRANSACTION_ARGS) {
                break;
            }
            if (client.number == transfer.number && transfer.cash_payments != 0) {
                client.credit_limit += transfer.cash_payments;
            }
        }
        blackrecord_out(blackrecord_file, &client);
        rewind(transaction_file);
    }
}
