#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "write.h"

int main(void) {
    while (TRUE) {
        printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");

        int choice = 0;
        if (scanf("%d", &choice) != 1) {
            break;
        }
        switch (choice) {
            case CLIENT: {
                FILE* client_file = fopen(CLIENT_FILE, "w");
                if (!client_file) {
                    printf("Can't open file %s.\n", CLIENT_FILE);
                } else {
                    write_client_file(client_file);
                    fclose(client_file);
                }
                break;
            }
            case TRANSACTION: {
                FILE* transaction_file = fopen(TRANSACTION_FILE, "w");
                if (!transaction_file) {
                    printf("Can't open file %s.\n", TRANSACTION_FILE);
                } else {
                    write_transaction_file(transaction_file);
                    fclose(transaction_file);
                }
                break;
            }
            case BLACKRECORD: {
                FILE* client_file = fopen(CLIENT_FILE, "r");
                FILE* transaction_file = fopen(TRANSACTION_FILE, "r");
                FILE* blackrecord_file = fopen(BLACKRECORD_FILE, "w");

                if (!client_file || !transaction_file || !blackrecord_file) {
                    if (!client_file) {
                        printf("Can't open file %s.\n", CLIENT_FILE);
                    }
                    if (!transaction_file) {
                        printf("Can't open file %s.\n", TRANSACTION_FILE);
                    }
                    if (!blackrecord_file) {
                        printf("Can't open file %s.\n", BLACKRECORD_FILE);
                    }
                    if (client_file) {
                        fclose(client_file);
                    }
                    if (transaction_file) {
                        fclose(transaction_file);
                    }
                    if (blackrecord_file) {
                        fclose(blackrecord_file);
                    }
                    puts("Not access");
                    break;
                } else {
                    write_blackrecord_file(client_file, transaction_file, blackrecord_file);
                    fclose(client_file);
                    fclose(transaction_file);
                    fclose(blackrecord_file);
                    break;
                }
            }
            default:
                puts("Error mode : use only modes 0, 1, 2.");
        }
    }
    return EXIT_SUCCESS;
}
