#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <emscripten/emscripten.h>

typedef struct
{
    int *data;
    int size;
} Vector;

void EMSCRIPTEN_KEEPALIVE Create(Vector *v, int sz)
{
    v->size = sz;
    v->data = malloc(v->size * sizeof(int));
}

bool EMSCRIPTEN_KEEPALIVE Empty(Vector *v)
{
    return v->size == 0;
}

int EMSCRIPTEN_KEEPALIVE Size(Vector *v)
{
    return v->size;
}

int EMSCRIPTEN_KEEPALIVE Load(Vector *v, int i)
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

void EMSCRIPTEN_KEEPALIVE Save(Vector *v, int i, int t)
{
    if ((i >= 0) && i < v->size)
    {
        v->data[i] = t;
    }
}

void EMSCRIPTEN_KEEPALIVE Resize(Vector *v, int sz)
{
    v->size = sz;
    v->data = realloc(v->data, v->size * sizeof(int));
}

bool EMSCRIPTEN_KEEPALIVE Eq(Vector *l, Vector *r)
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

void EMSCRIPTEN_KEEPALIVE Destroy(Vector *v)
{
    v->size = 0;
    free(v);
}

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
