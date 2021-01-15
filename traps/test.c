#include <stdio.h>

void max()
{
    printf("OK\n");
}

int main(void)
{
    /* p 是函数指针 */
    void *p; // &可以省略
    p = &max;
    ((void (*)())p)();

    return 0;
}