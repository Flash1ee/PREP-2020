#include <string.h>

#include "utils.h"

size_t custom_strlen(const char *str) {
    size_t i = 0;
    while (*str) {
        i++;
        str++;
    }
    return i;
}

int custom_pow(int base, int power) {
    int res = base;
    int count = power;

    if (!power) {
        return 1;
    }
    for (int i = 1; i < count; i++) {
        res *= base;
    }

    return res;
}
