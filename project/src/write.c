#include "write.h"

void write_client_file(FILE *client_file) {
    Data client;
    memset(&client, 0, sizeof(client));
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
           "1 Number account: ",
           "2 Client name: ",
           "3 Surname: ",
           "4 Addres client: ",
           "5 Client Telnum: ",
           "6 Client indebtedness: ",
           "7 Client credit limit: ",
           "8 Client cash payments: ");
    while ((scanf("%d"
                        "%" LEN(NAME) "s"
                        "%" LEN(SURNAME) "s"
                        "%" LEN(ADDRES) "s"
                        "%" LEN(TELNUM) "s"
                        "%lf%lf%lf",
                       &client.Number,
                       client.Name,
                       client.Surname,
                       client.addres,
                       client.TelNumber,
                       &client.indebtedness, &client.credit_limit, &client.cash_payments)) != -1) {
        fprintf(client_file, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                client.Number,
                client.Name,
                client.Surname,
                client.addres,
                client.TelNumber,
                client.indebtedness,
                client.credit_limit,
                client.cash_payments);
        printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
               "1 Number account: ",
               "2 Client name: ",
               "3 Surname: ",
               "4 Addres client: ",
               "5 Client Telnum: ",
               "6 Client indebtedness: ",
               "7 Client credit limit: ",
               "9 Client cash payments:");
    }
}
void write_transaction_file(FILE *transaction_file) {
    Data transfer;
    memset(&transfer, 0, sizeof(transfer));

    printf("%s\n%s\n",
           "1 Number account: ",
           "2 Client cash payments: ");
    while ((scanf("%d %lf", &transfer.Number, &transfer.cash_payments)) != -1) {
        fprintf(transaction_file, "%-3d%-6.2f\n", transfer.Number, transfer.cash_payments);
        printf("%s\n%s\n",
               "1 Number account:",
               "2 Client cash payments: ");
    }
}
void write_blackrecord_file(FILE *client_file, FILE *transaction_file, FILE *blackrecord_file) {
    Data client, transfer;
    memset(&client, 0, sizeof(client));
    memset(&transfer, 0, sizeof(transfer));

    while (fscanf(client_file,
                  "%d"
                  "%" LEN(NAME) "s"
                  "%" LEN(SURNAME) "s"
                  "%" LEN(ADDRES) "s"
                  "%" LEN(TELNUM) "s"
                  "%lf%lf%lf",
                  &client.Number, client.Name, client.Surname, client.addres,
                  client.TelNumber, &client.indebtedness, &client.credit_limit,
                  &client.cash_payments) != -1) {
        while (fscanf(transaction_file, "%d %lf", &transfer.Number, &transfer.cash_payments) != -1) {
            if (client.Number == transfer.Number && transfer.cash_payments != 0) {
                client.credit_limit += transfer.cash_payments;
            }
        }
        fprintf(blackrecord_file, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                client.Number, client.Name,
                client.Surname, client.addres, client.TelNumber,
                client.indebtedness, client.credit_limit, client.cash_payments);
        rewind(transaction_file);
    }
}
