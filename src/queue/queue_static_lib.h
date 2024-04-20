#ifndef QUEUE_STATIC_LIB_H
#define QUEUE_STATIC_LIB_H

#include <stdbool.h>
#include <stddef.h>

#define POOL_SIZE 100

typedef struct data_type
{
    int key;
    int value;
} data_type;


typedef struct queue
{
    data_type first;
    size_t size;
    data_type data[POOL_SIZE];
} queue;

void Create(queue *q);
bool Empty(queue *q);
size_t Size(queue *q);
bool Push(queue *q, data_type t);
bool Pop(queue *q);
data_type Top(const queue *q);
int Top_value(const queue *q);
void Destroy(queue *q);

#endif // QUEUE_STATIC_LIB_H