#include "heap_sort.h"

void swapify(Key* a, Key* b) {
    Key temp = *a;
    *a = *b;
    *b = temp;
}

void siftdown(Key* arr, int start, int end)
{
    // текущий узел
    int root = start;
    while (root * 2 + 1 <= end)
    {
        int child = root * 2 + 1;
        int swap = root;

        if (strcmp(arr[swap].key_value, arr[child].key_value) < 0)
        {
            swap = child;
        }
        if (child + 1 <= end && strcmp(arr[swap].key_value, arr[child + 1].key_value) < 0)
        {
            swap = child + 1;
        }
        if (swap != root)
        {
            swapify(&arr[root], &arr[swap]);
            root = swap;
        }
        else
        {
            return;
        }
    }
}

void heapSort(Key* arr)
{
    for (int i = N / 2 - 1; i >= 0; i--)
    {
        siftdown(arr, i, N - 1);
    }
    for (int i = N - 1; i >= 0; i--)
    {
        swapify(&arr[0], &arr[i]);
        siftdown(arr, 0, i - 1);
    }
}