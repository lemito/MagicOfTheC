#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define POOL_SIZE 100

typedef struct
{
    int size;
    int data[POOL_SIZE];
} stack;

void Create(stack *s)
{
    s->size = 0;
}

bool Empty(stack *s)
{
    return s->size == 0;
}

int Size(stack *s)
{
    return s->size;
}

bool Push(stack *s, int t)
{
    if (s->size == POOL_SIZE)
    {
        return false;
    }
    s->data[s->size++] = t;
    return true;
}

bool Pop(stack *s)
{
    if (!s->size)
    {
        return false;
    }
    s->size--;
    return true;
}

int Top(stack *s)
{
    return s->data[s->size--];
}

void Destroy(stack *s)
{
    s->size = 0;
    free(s->data);
}

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