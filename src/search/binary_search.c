#include "binary_search.h"


void Binary_Search(const Key *keys, const Data *datas)
{

    Key search_elem;
    puts("Введите значение ключа");
    int scan_res = scanf("%5s", search_elem.key_value);
    if (scan_res != 1){
        puts("Ошибка. Введите ключ правильно - строка из пяти символов");
    }

    int l = 0, r = N - 1;
    bool findStatus = false;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;

        if (strcmp(keys[mid].key_value, search_elem.key_value) == 0)
        {
            printf("Ключ найден, его значение: %s\n", datas[keys[mid].to].data);
            return;
        }

        if (strcmp(keys[mid].key_value, search_elem.key_value) < 0)
            l = mid + 1;

        else
            r = mid - 1;
    }

    puts("Значение по ключу не найдено");
    return;
}