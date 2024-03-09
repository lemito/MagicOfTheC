#include "queue_static_lib.h"

void Create(queue *q)
{
    q->first = 0;
    q->size = 0;
}

bool Empty(queue *q)
{
    return q->size == 0;
}

int Size(queue *q)
{
    return q->size;
}

bool Push(queue *q, const int t)
{
    if (q->size == POOL_SIZE)
        return false;
    q->data[(q->first + q->size++) % POOL_SIZE] = t;
    return true;
}

bool Pop(queue *q)
{
    if (!q->size)
        return false;
    q->first++;
    q->first %= POOL_SIZE;
    q->size--;
    return true;
}

int Top(const queue *q)
{
    if (!q->size)
        return q->data[q->first];
}

void Destroy(queue *q)
{
    q->size = 0;
}