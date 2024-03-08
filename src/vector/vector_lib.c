#include <stdbool.h>
#include <stdlib.h>
#include "vector_lib.h"

void Create(Vector *v, int sz)
{
    v->size = sz;
    v->data = malloc(v->size * sizeof(int));
}

bool Empty(Vector *v)
{
    return v->size == 0;
}

int Size(Vector *v)
{
    return v->size;
}

int Load(Vector *v, int i)
{
    if ((i >= 0) && i < v->size)
    {
        return v->data[i];
    }
    else
    {

        return -1;
    }
}

void Save(Vector *v, int i, int t)
{
    if ((i >= 0) && i < v->size)
    {
        v->data[i] = t;
    }
}

void Resize(Vector *v, int sz)
{
    v->size = sz;
    v->data = realloc(v->data, v->size * sizeof(int));
}

bool Eq(Vector *l, Vector *r)
{
    if (l->size != r->size)
    {
        return false;
    }
    for (int i = 0; i < l->size; i++)
    {
        if (l->data[i] != r->data[i])
        {
            return false;
        }
    }
    return true;
}

void Destroy(Vector *v)
{
    v->size = 0;
    free(v);
}