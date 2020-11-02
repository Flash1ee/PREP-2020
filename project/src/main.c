#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "write.h"

int main(void) {
    while (TRUE) {
        printf("please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");

        int choice = 0;
        if (scanf("%d", &choice) != 1) {
            return READ_ERR;
        }
        int rc = 0;
        switch (choice) {
            case CLIENT: {
                rc = write_client_file();
                if (rc == OPEN_ERR) {
                    puts("Can't open file record.dat.");
                    return rc;
                }
                if (rc == READ_ERR) {
                    puts("Error reading the file");
                    return rc;
                }
                return EXIT_SUCCESS;
            }
            case TRANSACTION: {
                rc = write_transaction_file();
                if (rc == OPEN_ERR) {
                    puts("Can't open file transaction.dat.");
                    return rc;
                }
                if (rc == READ_ERR) {
                    puts("Error reading the file");
                    return rc;
                }
                return EXIT_SUCCESS;
            }
            case BLACKRECORD: {
                rc = write_blackrecord_file();
                if (rc == READ_ERR) {
                    puts("Error reading the file");
                }
                return rc;
            }
            default:
                puts("Error mode : use only modes 0, 1, 2.");
        }
    }
    return EXIT_SUCCESS;
}
