#include <string.h>

#include "utils.h"

size_t custom_strlen(const char *str) {
    return strlen(str);
}

double custom_pow(double base, int power) {
    // double res = base;
    int res = base;
    int count = power;

    if (!power)
        return 1;
    /*
    else if (power < 0)
        count = power * -1;
    */

    for (int i = 1; i < count; i++)
        res *= base;

    /*if (power < 0)
        return 1 / res;
    */
    return res;
}
