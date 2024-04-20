#ifndef QUEUE_STATIC_LIB_H
#define QUEUE_STATIC_LIB_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

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

/**
 * Cоздает очередь - инициализация
 * @param q
 */
void Create(queue *q);

/**
 * Проверка на пустоту
 * @param q
 * @return
 */
bool Empty(queue *q);

/**
 * Размер очереди
 * @param q
 * @return
 */
size_t Size(queue *q);

/**
 * Добавляет элемент в конец
 * @param q
 * @param t
 * @return
 */
bool Push(queue *q, data_type t);

/**
 * Удаляет элемент
 * @param q
 * @return
 */
bool Pop(queue *q);

/**
 * Берет элемент и возвращает его
 * @param q
 * @return {data_type}
 */
data_type Top(const queue *q);

/**
 * Берет элемент и возвращает его
 * @param q
 * @return {int}
 */
int Top_value(const queue *q);

/**
 * "Уничтожает" очередь
 * @param q
 */
void Destroy(queue *q);

/**
 * Распечатать очередь в формате: [key:value, key:value, key:value, ...]
 * @param q
 */
void Print(queue *q);

#endif // QUEUE_STATIC_LIB_H