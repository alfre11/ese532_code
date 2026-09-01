#include <stdio.h>

int main(void) {
    double a[] = {3.14, 2.71};

    unsigned char *bytes = (unsigned char *)a;

    for (size_t i = 0; i < sizeof(a); i++) {
        printf("byte %zu: 0x%02X\n", i, bytes[i]);
    }

    return 0;
}