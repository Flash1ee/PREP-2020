#include <stdio.h>

#include "check_correct.h"

int main(void) {
    int no_failed = 0;
    no_failed += test_read_write_client();
    no_failed += test_read_write_transaction();
    no_failed += test_read_write_blackrecord();
    no_failed += test_calculate_blackrecord();
    no_failed += test_multy_calculate_blackrecord();

    return no_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE; 
}
