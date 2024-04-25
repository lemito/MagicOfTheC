#include "heap_sort.h"

void siftdown(Key arr[], int start, int end)
{
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
            Key temp = arr[root];
            arr[root] = arr[swap];
            arr[swap] = temp;
            root = swap;
        }
        else
        {
            return;
        }
    }
}

void heapSort(Key arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        siftdown(arr, i, n - 1);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        Key temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        siftdown(arr, 0, i - 1);
    }
}