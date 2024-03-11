#include <stdio.h>
#include "vector_lib.h"

int main()
{
    printf("Hello World!\n");
    Vector vector;
    Create(&vector, 10);
    for (int i = 0; i < 9; i++)
    {
        Save(&vector, i, i);
    }
    for (int i = 0; i < 9; i++)
    {
        printf("%d ", Load(&vector, i));
    }
    putchar('\n');
    printf("Size = %d \n", Size(&vector));
    Destroy(&vector);
    return 0;
}
