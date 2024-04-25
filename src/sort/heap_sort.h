//
// Created by lemito on 4/25/24.
//

#ifndef MAGICOFTHEC_HEAP_SORT_H
#define MAGICOFTHEC_HEAP_SORT_H

#include "../kp9/table.h"
#include <string.h>

void siftdown(Key arr[], int start, int end);

void heapSort(Key arr[], int n);

#endif //MAGICOFTHEC_HEAP_SORT_H
