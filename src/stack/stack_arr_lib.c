#include "stack_arr_lib.h"

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
    return s->data[s->size-1];
}

void Destroy(stack *s)
{
    s->size = 0;
    free(s->data);
}
