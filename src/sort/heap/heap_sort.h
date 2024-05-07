//
// Created by lemito on 4/25/24.
//

#ifndef MAGICOFTHEC_HEAP_SORT_H
#define MAGICOFTHEC_HEAP_SORT_H

#include "../../kp9/table.h"
#include <string.h>

/**
 * Просеивание, тяжелые элементы падают вниз
 * @param arr  массив для просеивания
 * @param start откуда начинаем
 * @param end где заканчиваем
 */
void siftdown(Key* arr, int start, int end);

/**
 * Функция сортировки
 * @param arr массив для сортировки
 */
void heapSort(Key* arr);

#endif //MAGICOFTHEC_HEAP_SORT_H
