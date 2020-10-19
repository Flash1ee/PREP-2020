#include "main_module.h"

void read_from_file(const char *filename, Data *data) {
    FILE* src = fopen(filename, "r");
    if (!strcmp(filename, client_file)) {
        fscanf(src,
                    "%d"
                    "%" LEN(NAME) "s"
                    "%" LEN(SURNAME) "s"
                    "%" LEN(ADDRES) "s"
                    "%" LEN(TELNUM) "s"
                    "%lf%lf%lf",
                    &(data->number), data->name, data->surname, data->addres,
                    data->tel_number, &(data->indebtedness), &(data->credit_limit),
                    &(data->cash_payments));
    } else {
        fscanf(src, "%d %lf", &(data->number), &(data->cash_payments));
    }
    fclose(src);
}
