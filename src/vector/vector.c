#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "vector_lib.h"

int main()
{
    printf("Hello World!\n");
    Vector vector;
    Create(&vector, 5);
    for (int i = 0; i < 9; i++)
    {
        Save(&vector, i, i);
    }
    for (int i = 0; i < 9; i++)
    {
        printf("%d ", Load(&vector, i));
    }

    return 0;
}
