#include <stdio.h>
#include <stdlib.h>

void temp(int i) {
    int a[2];
    int b[3];
    int *c;
    int *d;

    c = (int *)malloc(sizeof(int) * 4);
    d = (int *)malloc(sizeof(int) * 5);

    printf("a = %p\n", (void *)a);
    printf("b = %p\n", (void *)b);
    printf("c = %p\n", (void *)c);
    printf("d = %p\n", (void *)d);

    free(c);
    free(d);
}

int main(void) {
    temp(0);
    return 0;
}