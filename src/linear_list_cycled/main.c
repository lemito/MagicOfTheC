#include <stdio.h>
#include "list/list.h"

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void print_menu()
{
    printf("0) Выйти\n");
    printf("1) Печать списка\n");
    printf("2) Вставка нового жлемента в список\n");
    printf("3) Удаление элемента из списка\n");
    printf("4) Подсчет длины списка\n");
    printf("5) Добавить k экзампляров последнего элемента в начало списка\n");
}


int main()
{
    List listik;
    Create(&listik);

    print_menu();
    char choise;
    char tmp[15];
    int k = 0;
    scanf("%c", &choise);
    while (choise != '0')
    {
        if (choise == EOF)
        {
            printf("Пока!!!\n");
            break;
        }
        switch (choise)
        {
        // вывод списка
        case '1':
            printf("Список выглядит так: ");
            PrintList(&listik);
            clearInputBuffer();
            break;
        // добавление в список
        case '2':
            printf("Что добавим в список? : ");
            scanf("%s", tmp);
            Append(&listik, tmp);
            printf("Добавлено\n");
            clearInputBuffer();
            break;

        // удаление элемента из списка
        case '3':
            printf("Что удалим из списка? : ");
            scanf("%s", tmp);
            if (Remove(&listik, tmp))
            {
                printf("Элемент %s успешно удален.\n", tmp);
            }
            else
            {
                printf("Элемент %s не найден в списке.\n", tmp);
            }
            clearInputBuffer();
            break;

        // длина списка
        case '4':
            printf("Текущая длина списка равна : %d\n", size(&listik));
            break;

        case '5':
            printf("Сколько раз добавляем последний элемент в начало k=");
            scanf("%d", &k);
            AddLastToHead(&listik, k);
            printf("Добавлено!!!\n");
            clearInputBuffer();
            break;

        case '0':
            printf("Выход из программы.\n");
            exit(0);
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
        print_menu();
        scanf("%c", &choise);
        clearInputBuffer();
    }
    Destroy(&listik);
    return 0;
}
