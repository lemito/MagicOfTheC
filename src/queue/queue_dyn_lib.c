#include "queue_dyn_lib.h"
#include <stdlib.h>
#include <string.h>

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

bool Push(queue *q, const char *t)
{
    if (!(q->last->next = malloc(sizeof(struct Item))))
        return false;
    strcpy(q->last->data, t);
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

char *Top(const queue *q)
{
    if (q->first != q->last)
        return q->first->data;
}

void Destroy(queue *q)
{
    while (!Empty(q))
        Pop(q);
    free(q->first);
    q->first = q->last = NULL;
    q->size = 0;
}

void Reverse(queue *q)
{
    if (!Empty(q))
    {
        char *t = Top(q);
        Pop(q);
        Reverse(q);
        Push(q, t);
    }
}