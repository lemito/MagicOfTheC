#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define POOL_SIZE 100

typedef struct
{
    int first;
    int size;
    int data[POOL_SIZE];
} queue;

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
