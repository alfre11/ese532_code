#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int a[2][4] = {{10, 20, 30, 40}, {50, 60, 70, 80}};

    int *p[2];

    p[0] = a[0];
    p[1] = a[1];

    printf("Using array of pointers:\n");

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", p[i][j]);
        }
        printf("\n");
    }

    int **pp = p;

    printf("\nUsing double pointer:\n");

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", pp[i][j]);
        }
        printf("\n");
    }

    printf("\nPointer verification:\n");

    printf("a[0]    = %p\n", (void *)a[0]);
    printf("p[0]    = %p\n", (void *)p[0]);

    printf("a[1]    = %p\n", (void *)a[1]);
    printf("p[1]    = %p\n", (void *)p[1]);

    printf("&p[0]   = %p\n", (void *)&p[0]);
    printf("pp      = %p\n", (void *)pp);

    return 0;
}