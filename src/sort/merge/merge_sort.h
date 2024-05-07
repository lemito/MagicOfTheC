//
// Created by lemito on 4/20/24.
//
#include "../../queue/queue_static_lib.h"
#ifndef MAGICOFTHEC_MERGE_SORT_H
#define MAGICOFTHEC_MERGE_SORT_H

/**
 * Функция для мерджа: сливает две очереди
 * @param q1 первая очередь
 * @param q2 вторая очередь
 * @param q выходная очередь
 */
void merge(queue *q1, queue* q2, queue* q);

/**
 * Функция сортировки
 * @param q
 */
void merge_sort(queue* q);

#endif //MAGICOFTHEC_MERGE_SORT_H
