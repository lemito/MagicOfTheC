#ifndef VECTOR_LAB_H
#define VECTOR_LAB_H

#include <stdbool.h>

typedef struct Vector
{
    int *data;
    int size;
} Vector;

void Create(Vector *v, int sz);
bool Empty(Vector *v);
int Size(Vector *v);
int Load(Vector *v, int i);
void Save(Vector *v, int i, int t);
void Resize(Vector *v, int sz);
bool Eq(Vector *l, Vector *r);
void Destroy(Vector *v);

#endif // VECTOR_LAB_H

