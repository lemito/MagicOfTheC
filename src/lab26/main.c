//
// Created by lemito on 4/20/24.
//
#include <stdio.h>
#include "../sort/merge/merge_sort.h"

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void print_menu()
{
    puts("0) Выйти");
    puts("1) Печать очереди");
    puts("2) Вставика в очередь элемента в формате key:value");
    puts("3) Удалить из очереди и вывести элемент в формате key:value");
    puts("4) Длина очереди");
    puts("5) Отсортировать (метод: сортировка слиянием)");
}

int main(void)
{
    queue work_queue;
    data_type worker_type = {0, 0};
    Create(&work_queue);

    print_menu();
    char choise;
    while (scanf("%c", &choise) != EOF && choise != '0')
    {
        if (choise == EOF)
        {
            break;
        }
        switch (choise)
        {
        case '1':
            Print(&work_queue);
            // clearInputBuffer();
            break;

        case '2':
            puts("Введите ключ и значение элемента в формате key:value");
            scanf("%d:%d", &worker_type.key, &worker_type.value);
            if (Push(&work_queue, worker_type))
                puts("Добавлено!");
            // clearInputBuffer();
            break;

        case '3':
            printf("Удален элемент %d:%d\n", Top(&work_queue).key, Top(&work_queue).value);
            Pop(&work_queue);
            // clearInputBuffer();
            break;

        case '4':
            printf("Длина очереди = %zu\n", Size(&work_queue));
            // clearInputBuffer();
            break;

        case '5':
            merge_sort(&work_queue);
            puts("Отсортировано");
            // clearInputBuffer();
            break;

        default:
            puts("Неверный вариант!");
            break;
        }
        print_menu();
        // clearInputBuffer();
        scanf("%c", &choise);
    }

    Destroy(&work_queue);
    puts("Работа окончена!");

    return 0;
}