//
// Created by lemito on 4/20/24.
//
#include "merge_sort.h"

void merge(queue *q1, queue *q2, queue *q)
{
    /*
     * сортировка двух объектов по ключу
     * если первый ключ меньше, то добавляем его в q и убираем из q1
     * иначе: добавляем элемент из q2 в q и убираем из q2
     */
    while (!Empty(q1) && !Empty(q2))
    {
        if (Top(q1).key <= Top(q2).key)
        {
            Push(q, Top(q1));
            Pop(q1);
        }
        else
        {
            Push(q, Top(q2));
            Pop(q2);
        }
    }

    // Добавляем оставшиеся элементы из q1 и q2 в q по остаточному принципу
    while (!Empty(q1))
    {
        Push(q, Top(q1));
        Pop(q1);
    }
    while (!Empty(q2))
    {
        Push(q, Top(q2));
        Pop(q2);
    }
}


void merge_sort(queue *q)
{
    // выход из рекурсии
    if (Size(q) <= 1)
    {
        return;
    }

    // начинаем делить на две половинки
    size_t mid = Size(q) / 2;
    queue q1, q2;
    Create(&q1);
    Create(&q2);

    // заполняем первую половину
    for (size_t i = 0; i < mid; i++)
    {
        Push(&q1, Top(q));
        Pop(q);
    }

    // заполняем вторую половину
    for (size_t i = 0; i < Size(q); i++)
    {
        Push(&q2, Top(q));
        Pop(q);
    }

    // Рекурсия для каждой из половинок
    merge_sort(&q1);
    merge_sort(&q2);

    // сливаем половинки
    merge(&q1, &q2, q);

    // удаляем использованные временные очереди
    Destroy(&q1);
    Destroy(&q2);
}