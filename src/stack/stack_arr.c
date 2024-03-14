#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "stack_arr_lib.h"

int main()
{
    printf("Hello World!\n");
    stack stack;
    Create(&stack);
    for (int i = 0; i < 9; i++)
    {
        printf("%d", i);
        Push(&stack, i);
    }
    printf("%d\n", Size(&stack));
    for (int i = 0; i < 10; i++)
    {

        printf("%d ", Top(&stack));
    }

    return 0;
}