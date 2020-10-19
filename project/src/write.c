#include "write.h"
#include "io.h"

void write_client_file(FILE *client_file) {
    Data client;
    memset(&client, 0, sizeof(client));
    while (TRUE) {
        client_info(stdout);
        if (client_input(stdin, &client) == -1) {
            break;
        }
        client_out(client_file, &client);
    }
}
void write_transaction_file(FILE *transaction_file) {
    Data transfer;
    memset(&transfer, 0, sizeof(transfer));

    while (TRUE) {
        transaction_info(stdout);
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
        if (transaction_input(stdin, &transfer) == -1) {
            break;
        }
        transaction_out(transaction_file, &transfer);
    }
}
void write_blackrecord_file(FILE *client_file, FILE *transaction_file, FILE *blackrecord_file) {
    Data client, transfer;
    memset(&client, 0, sizeof(client));
    memset(&transfer, 0, sizeof(transfer));
    while (TRUE) {
        if (client_input(client_file, &client) == -1) {
            return;
        }
        while (TRUE) {
            if (transaction_input(transaction_file, &transfer) == -1) {
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
