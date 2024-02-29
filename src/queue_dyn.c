#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Item
{
    int data;
    struct Item *next;
};

typedef struct
{
    struct Item *first;
    struct Item *last;
    int size;
} queue;

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
    q->first = q->last == 0;
    q->size = 0;
}

int main()
{
    printf("Hello World!\n");

    queue qwer;

    Create(&qwer);
    Push(&qwer, 1);
    Push(&qwer, 2);
    Push(&qwer, 3);
    Push(&qwer, 4);
    printf("%d\t", Top(&qwer));
    Pop(&qwer);
    printf("%d\t", Top(&qwer));
    Pop(&qwer);
    printf("%d\t", Top(&qwer));
    Pop(&qwer);
    printf("%d\t", Top(&qwer));

    return 0;
}
