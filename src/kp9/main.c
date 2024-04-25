#include <string.h>
#include <stdbool.h>
#include "table.h"
#include "../sort/heap_sort.h"

void Binary_Search(const Key* keys, const Data* datas){
    Key search_elem;
    puts("Введите значение ключа");
    scanf("%4s", search_elem.key_value);
    int l = 0, r = N - 1;
    bool flag = false;
    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (strcmp(keys[mid].key_value, search_elem.key_value) == 0) {
            printf("ключ найден, его значение: %s\n", datas[keys[mid].to].data);
            flag = true;
            break;
        }

        if (strcmp(keys[mid].key_value, search_elem.key_value) > 0)
            l = mid + 1;

        else
            r = mid - 1;
    }

    if (flag == false) puts("Значение по ключу не найдено :(");
}

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
    FILE *input;
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
            input = fopen("input.txt", "r");
            if (input == NULL)
            {
                puts("Не удалось открыть файл\n");
                return 1;
            }
            Create_Table(input, keys, datas);
            puts("Создано");
            break;

        case '2':
            heapSort((Key *) keys->key_value, N);
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


    fclose(input);
    puts("Работа окончена!");

    return 0;
}