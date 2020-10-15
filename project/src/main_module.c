#include "main_module.h"

int compare_data(Data *one, Data *two)
{
    int rc = one->Number - two->Number;
    rc = strcmp(one->Name, two->Name);
    rc = strcmp(one->Surname, two->Surname);
    rc = strcmp(one->addres, two->addres);
    rc = strcmp(one->TelNumber, two->TelNumber);
    rc = one->cash_payments - two->cash_payments;
    rc = one->indebtedness - two->indebtedness;
    rc = one->credit_limit - two->credit_limit;
    return rc;
}
void test_write_to_file() {
	const char *filename_client = client_file;

	Data expected_data;
    expected_data.Number = 1;
    strcpy(expected_data.Name, "Vasya");
    strcpy(expected_data.Surname, "Pupkin");
    strcpy(expected_data.addres, "Moscow");
    strcpy(expected_data.TelNumber, "88005553535");
    expected_data.indebtedness = 200.00;
    expected_data.credit_limit = 1000.00;
    expected_data.cash_payments = 50.00;


	write_to_file(filename_client, &expected_data);

	Data got_data;
	read_from_file(filename_client, &got_data);

    if (!compare_data(&expected_data, &got_data)) {
        printf("TEST_WRITE-READ_RECORD ---- SUCCESS...\n");
    } else {
        printf("TEST_WRITE-READ_RECORD ---- FAILED...\n");
    }


	const char *filename_transaction = transaction_file;

    write_to_file(filename_transaction, &expected_data);

    read_from_file(filename_client, &got_data);

    if (!compare_data(&expected_data, &got_data)) {
        printf("TEST_WRITE-READ_TRANSACTION ---- SUCCESS...\n");
    } else {
        printf("TEST_WRITE-READ_TRANSACTION ---- FAILED...\n");
    }
}
