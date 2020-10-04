#include "prime.h"

int isprime(int num) {
    if (num < 2) {
        return NOT_PRIME;
    }
    for (int i = 2; i * i < num; i++) {
        if (num % i == 0) {
            return NOT_PRIME;
        }
    }
    return PRIME;
}
