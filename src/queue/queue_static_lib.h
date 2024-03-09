#ifndef QUEUE_STATIC_LIB_H
#define QUEUE_STATIC_LIB_H

#include <stdbool.h>

#define POOL_SIZE 100

typedef struct queue
{
    int first;
    int size;
    int data[POOL_SIZE];
} queue;

void Create(queue *q);
bool Empty(queue *q);
int Size(queue *q);
bool Push(queue *q, const int t);
bool Pop(queue *q);
int Top(const queue *q);
void Destroy(queue *q);

#endif // QUEUE_STATIC_LIB_H