#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int x = 20;

    int *p = &x;

    int *q = malloc(sizeof(int));
    *q = 50;

    int *arr = malloc(3 * sizeof(int));

    arr[0] = 5;
    arr[1] = 6;
    arr[2] = 7;

    printf("STACK\n");
    printf("x   address: %p, value: %d\n", (void *)&x, x);
    printf("p   address: %p, value: %p\n", (void *)&p, (void *)p);
    printf("q   address: %p, value: %p\n", (void *)&q, (void *)q);
    printf("arr address: %p, value: %p\n", (void *)&arr, (void *)arr);

    printf("\nHEAP / POINTER TARGETS\n");
    printf("*p      address: %p, value: %d\n", (void *)p, *p);
    printf("*q      address: %p, value: %d\n", (void *)q, *q);
    printf("arr[0]  address: %p, value: %d\n", (void *)&arr[0], arr[0]);
    printf("arr[1]  address: %p, value: %d\n", (void *)&arr[1], arr[1]);
    printf("arr[2]  address: %p, value: %d\n", (void *)&arr[2], arr[2]);

    free(q);
    free(arr);

    return 0;
}