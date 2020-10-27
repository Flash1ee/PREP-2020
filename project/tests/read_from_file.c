#include "check_correct.h"

void read_from_file(const char *filename, Data *data) {
    FILE* src = fopen(filename, "r");
    if (!strcmp(filename, client_file)) {
        client_input(src, data);
    } else {
        transaction_input(src, data);
    }
    fclose(src);
}
