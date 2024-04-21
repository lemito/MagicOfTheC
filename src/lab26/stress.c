#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../queue/queue_static_lib.h"
#include "../sort/merge_sort.h"

// генерация числа
int random_in_range(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Стресс-тест
void stress_test() {
    srand(time(NULL));
    queue work_queue;
    Create(&work_queue);

    // Генерация и добавление элементов
    for (int i = 0; i < 101; i++) {
        data_type worker_type = {random_in_range(1, 1000), random_in_range(1, 1000)};
        Push(&work_queue, worker_type);
    }

    // Первая печать
    Print(&work_queue);

    // Сортировка
    merge_sort(&work_queue);

    // Вторая печать
    Print(&work_queue);

    Destroy(&work_queue);
}

int main(void) {
    stress_test();
    return 0;
}
