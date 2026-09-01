#include <stdio.h>
#include <stdlib.h>

struct s2 {
  float a;
  int b;
};

struct s1 {
  int c;
  struct s2 **d;
};




int main(void) {
    struct s1 x[5];

    struct s2 obj;
    obj.a = 1;
    obj.b = 2;

    struct s2 *p = &obj;

    x[2].d = &p;

    printf("Address using expression: %p\n",
           (void *)&((*x[2].d)->b));

    printf("Actual address of obj.b: %p\n",
           (void *)&obj.b);

    printf("Value of b: %d\n",
           (*x[2].d)->b);

    return 0;
}