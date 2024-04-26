#include "heap_sort.h"



// в результате просеивания самый большой элемент оказывается наверху, меняется с последним и... в конец

void siftdown(Key* arr, int start, int end)
{
    // коренб пирамиды
    int root = start;
    while (root * 2 + 1 <= end)
    {
        // индекс первого ребенка
        int child = root * 2 + 1;
        int swap = root;

        // Сравниваем корневой элемент с первым ребенком
        if (strcmp(arr[swap].key_value, arr[child].key_value) < 0)
        {
            swap = child;
        }
        //сравниваем еще, если есть еще ребенок
        if (child + 1 <= end && strcmp(arr[swap].key_value, arr[child + 1].key_value) < 0)
        {
            swap = child + 1;
        }
        // если корень меньше одного из ребенка -- меняем местами
        if (swap != root)
        {
            swapify(&arr[root], &arr[swap]);
            root = swap;
        }
        // если корень больше всех детей -- просеено
        else
        {
            return;
        }
    }
}

void heapSort(Key* arr)
{
    // 1 этап: построение кучи ~ нижний ряд пирамиды
    // создание кучи с середины массива
    for (int i = N / 2 - 1; i >= 0; i--)
    {
        siftdown(arr, i, N - 1);
    }
    // 2 этап: сама сортировка остальных элементов
    // наибольший элемент -> конец; просеиваем остальное
    for (int i = N - 1; i >= 0; i--)
    {
        swapify(&arr[0], &arr[i]);
        siftdown(arr, 0, i - 1);
    }
}