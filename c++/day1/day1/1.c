#include <stdio.h>
int main()
{
    const int a = 12;
    int *p = (int *)&a;

    *p += 13;

    printf("*p: %d a: %d\n", *p, a);
}