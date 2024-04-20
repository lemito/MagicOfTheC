#include "queue_static_lib.h"

void Create(queue *q)
{
    q->first.value = 0;
    q->first.key = 0;
    q->size = 0;
}

bool Empty(queue *q)
{
    return q->size == 0;
}

size_t Size(queue *q)
{
    return q->size;
}

bool Push(queue *q, const data_type elem)
{
    if (q->size == POOL_SIZE)
        return false;
    q->data[(q->first.key + q->size++) % POOL_SIZE] = elem;
    return true;
}

bool Pop(queue *q)
{
    if (!q->size)
        return false;
    q->first.key = (q->first.key + 1) % POOL_SIZE;
    q->size--;
    return true;
}

data_type Top(const queue *q)
{
    if (!q->size)
        return (data_type){0, 0};
    return q->data[q->first.key];
}

int Top_value(const queue *q){
    return Top(q).value;
}

void Destroy(queue *q)
{
    q->size = 0;
    q->first.key = -1;
    q->first.value = -1;
}

void Print(queue *q){
    puts("Очередь выглядит так: ");
    putchar('[');
    putchar(' ');
    int original_first_key = q->first.key;
    while (!Empty(q)){
        printf("%d:%d ", Top(q).key, Top(q).value);
        Pop(q);
    }
    q->first.key = original_first_key;
    puts("]");
}