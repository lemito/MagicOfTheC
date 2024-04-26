//
// Created by lemito on 4/25/24.
//

#ifndef MAGICOFTHEC_HEAP_SORT_H
#define MAGICOFTHEC_HEAP_SORT_H

#include "../kp9/table.h"
#include <string.h>

/**
 * Меняет ключи местами -- свап
 * @param a первый ключ
 * @param b второй ключ
 */
void swapify(Key* a, Key* b);

/**
 * Просеивание, тяжелые элементы падают вниз
 * @param arr
 * @param start
 * @param end
 */
void siftdown(Key* arr, int start, int end);

/**
 * Функция сортировки
 * @param arr
 */
void heapSort(Key* arr);

#endif //MAGICOFTHEC_HEAP_SORT_H
