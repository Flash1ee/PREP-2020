#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "prime.h"


#define ERR_ARGS_COUNT -1
#define ERR_WRONG_FLG -2
#define ERR_INPUT_NUM -3


#define TST_FOO_FIX 1
#define TST_FOO_IMPL 2
#define TST_MOD_IMPL 3

#define BASE 10


int main(int argc, const char **argv) {
    if (argc < 3) {
        return ERR_ARGS_COUNT;
    }

    int test_case = atoi(argv[1]);
    const char *data;
    data = argv[2];

    switch (test_case) {
    case TST_FOO_FIX: {
        size_t res = custom_strlen(data);
        printf("%zu\n", res);
        break;
    }
    case TST_FOO_IMPL: {
        if (argc != 4) {
            return ERR_ARGS_COUNT;
        }
        char *check = NULL;
        int base = (int) strtol(data, &check, BASE);
        if (*check != '\0')
            return ERR_INPUT_NUM;
        int pow =  (int) strtol(argv[3], &check, BASE);
        if (*check != '\0')
            return ERR_INPUT_NUM;

        int res = custom_pow(base, pow);

        printf("%d\n", res);
        break;
    }
    case TST_MOD_IMPL: {
        char *check = NULL;
        int num = (int) strtol(data, &check, BASE);
        if (*check != '\0')
            return ERR_INPUT_NUM;
        int res = isprime(num);
        printf("%d\n", res);
        break;
    }
    default: {
        return ERR_WRONG_FLG;
    }
    }

    return 0;
}
