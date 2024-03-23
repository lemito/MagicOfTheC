#include "queue_dyn_lib.h"

void Create(queue *q)
{
    q->first = q->last = malloc(sizeof(struct Item));
    q->size = 0;
}

bool Empty(queue *q)
{
    return q->first == q->last;
}

int Size(queue *q)
{
    return q->size;
}

bool Push(queue *q, const int t)
{
    if (!(q->last->next = malloc(sizeof(struct Item))))
        return false;
    q->last->data = t;
    q->last = q->last->next;
    q->size++;
    return true;
}

bool Pop(queue *q)
{
    if (q->first == q->last)
        return false;
    struct Item *pi = q->first;
    q->first = q->first->next;
    q->size--;
    free(pi);
    return true;
}

int Top(const queue *q)
{
    if (q->first != q->last)
        return q->first->data;
}

void Destroy(queue *q)
{
    while (!Empty(q))
    {
        struct Item *pi = q->first;
        q->first = q->first->next;
        free(pi);
    }
    free(q->first);
    q->first->data = q->last->data == 0;
    q->size = 0;
}

void Reverse(queue *q)
{
    if (!Empty(q))
    {
        int t = Top(q);
        Pop(q);
        Reverse(q);
        Push(q, t);
    }
}