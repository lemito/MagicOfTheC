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
        Resize(v, v->size++);
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
    void *new_data = realloc(v->data, sz * sizeof(int));
    if (new_data) {
        v->data = new_data;
        v->size = sz;
    } else {
        printf("Error in resizing!!!");
    }
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
    if (v->data != NULL) {
        FREE_AND_NULL(v->data);
    }
    v->size = 0;
}