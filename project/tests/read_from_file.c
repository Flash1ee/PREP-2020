#include "main_module.h"

void write_to_file(const char *filename, Data *data) {
    FILE* src = fopen(filename, "w");
    if (!strcmp(filename, client_file)) {
        fprintf(src, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                data->Number,
                data->Name,
                data->Surname,
                data->addres,
                data->TelNumber,
                data->indebtedness,
                data->credit_limit,
                data->cash_payments);
    } else {
        fprintf(src, "%-3d%-6.2f\n", data->Number, data->cash_payments);
    }
    fclose(src);
}
