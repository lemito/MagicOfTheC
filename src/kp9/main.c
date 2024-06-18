#include <string.h>
#include <stdbool.h>
#include "table.h"
#include "../sort/heap/heap_sort.h"
#include "../search/binary_search.h"

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void print_menu()
{
    puts("0) Выйти");
    puts("1) Создать таблицу");
    puts("2) Произвести сортировку");
    puts("3) Бинарный поиск по ключу");
    puts("4) Распечатать таблицу");
    puts("5) Перевернуть таблицу");
    puts("6) Перемешать таблицу");
}

int main(void)
{
    Key keys[N];
    Data datas[N];
    // В Cmake (и CLion) файйл берется из директории cmake-...
    // В vscode из  директории build

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
            FILE *input;
            input = fopen("input.txt", "r");
            if (input == NULL)
            {
                puts("Не удалось открыть файл\n");
                return 1;
            }
            Create_Table(input, keys, datas);
            fclose(input);
            puts("Создано");
            break;

        case '2':
            heapSort(keys);
            puts("Отсортировано!");
            break;

        case '3':
            Binary_Search(keys, datas);
            break;

        case '4':
            Print_Table(keys, datas);
            break;

        case '5':
            Reverse(keys);
            puts("Таблица перевернута");
            break;

        case '6':
            CruchuVerchu(keys);
            puts("Таблица перемешана");
            break;

        default:
            puts("Неверный вариант!");
            break;
        }
        print_menu();
        scanf("%c", &choise);
    }



    puts("Работа окончена!");

    return 0;
}