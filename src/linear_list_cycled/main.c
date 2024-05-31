#include <stdio.h>
#include "list/list.h"

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void print_menu()
{
    puts("0) Выйти");
    puts("1) Печать списка");
    puts("2) Вставка нового жлемента в список");
    puts("3) Удаление элемента из списка");
    puts("4) Подсчет длины списка");
    puts("5) Добавить k экзампляров последнего элемента в начало списка");
}

int main()
{
    // для КП9
    // for (int n = 1; n < 28; ++n)
    // {printf("%d: %d_%d\n", n, ((n-1)%15)+1, ((n+5)%9)+1);}


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
            int pos = 0;
            printf("Куда добавим? : ");
            scanf("%d", &pos);
            if (Append(&listik, pos, tmp)) printf("Добавлено\n");
            clearInputBuffer();
            break;

        // удаление элемента из списка
        case '3':
            printf("Что удалим из списка? : ");
            int delPos = 0;
            scanf("%d", &delPos);
            if (Remove(&listik, delPos))
            {
                printf("Элемент # %d успешно удален.\n", delPos);
            }
            else
            {
                printf("Элемент # %d не найден в списке.\n", delPos);
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
            clearInputBuffer();
            exit(0);
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
        print_menu();
        scanf("\n%c", &choise);
        clearInputBuffer();
    }
    Destroy(&listik);
    return 0;
}
