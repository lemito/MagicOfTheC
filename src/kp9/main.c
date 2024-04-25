#include <stdio.h>

#define N 8

typedef struct Key
{
    char key_value[5];
    int to;
} Key;

typedef struct Data
{
    char data[50];
} Data;

void Create_Table(FILE *file, Key *keys, Data *datas)
{
    for (int i = 0; i < N; i++)
    {
        fscanf(file, "%s %[^\n]\n", keys[i].key_value, datas[i].data);
        keys[i].to = i;
    }
}

void Print_Table(const Key *keys, const Data *datas)
{
    printf("|---------------------------------------------------------|\n");
    printf("| Ключ | Строка |\n");
    printf("|---------------------------------------------------------|\n");
    for (int i = 0; i < N; i++)
    {
        printf(" %s | %-50s\n", keys[i].key_value, datas[keys[i].to].data);
        printf("|---------------------------------------------------------|\n");
    }
}

void heapify(int arr[], int n, int i)
{
    int temp, maximum, left_index, right_index;

    maximum = i;

    right_index = 2 * i + 2;

    left_index = 2 * i + 1;

    if (left_index < n && arr[left_index] > arr[maximum])
        maximum = left_index;

    if (right_index < n && arr[right_index] > arr[maximum])
        maximum = right_index;

    if (maximum != i)
    {
        temp = arr[i];
        arr[i] = arr[maximum];
        arr[maximum] = temp;
        heapify(arr, n, maximum);
    }
}

void heapsort(int arr[], int n)
{
    int i, temp;

    for (i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }
    for (i = n - 1; i > 0; i--)
    {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
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
            FILE *input = fopen("input.txt", "r");
            if (input == NULL)
            {
                printf("Не удалось открыть файл\n");
                return 1;
            }
            Create_Table(input, keys, datas);
            break;

        case '2':
            puts("Введите ключ и значение элемента в формате key:value");
            // scanf("%d:%d", &worker_type.key, &worker_type.value);
            // if ()
            puts("Добавлено!");
            break;

        case '3':
            break;

        case '4':
            Print_Table(keys, datas);
            break;

        case '5':
            puts("Отсортировано");
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