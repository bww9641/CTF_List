#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include "DataStructures.h"

int checkEndianness() {
    unsigned char *pointer_test = NULL;
    unsigned int test = 1;

    pointer_test = (unsigned char*) (&test);
    if ((*pointer_test) == 1) {
        return 1;
    }
    return 0;
}

void xorshift32(unsigned int seed, unsigned int n, unsigned long int *v) {
    unsigned long int r = seed, k;

    for (k = 1; k < n; k++) {
        r = r ^ (r << 13);
        r = r ^ (r >> 17);
        r = r ^ (r << 5);
        v[k] = r;
    }
}

void permutation(unsigned long int *xorshift32_array, unsigned long int n, unsigned long *permutation_array) {
    unsigned long int k, r, aux;

    for (k = 0; k < n; k++) {
        permutation_array[k] = k;
    }
    for (k = n - 1; k >= 1; k--) {
        r = xorshift32_array[n - k] % (k + 1);
        aux = permutation_array[r];
        permutation_array[r] = permutation_array[k];
        permutation_array[k] = aux;
    }
}

#endif // ALGORITHMS_H
