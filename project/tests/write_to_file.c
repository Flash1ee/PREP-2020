#include "main_module.h"

void write_to_file(const char *filename, Data *data) {
    FILE* src = fopen(filename, "w");
    if (!strcmp(filename, client_file)) {
        client_out(src, data);
    } else {
        transaction_out(src, data);
    }
    fclose(src);
}
