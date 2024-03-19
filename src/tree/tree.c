#include <stdio.h>
#include "tree_lib.h"
const int DEBUG = 0;
#define D      \
    if (DEBUG == 1) \
        ;

// For visualisation use https://www.cs.usfca.edu/~galles/visualization/BST.html

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main()
{
    Tree *work_tree = NULL;
    int value = 0;
    print_menu();
    int action = getchar() - '0';
    D { printf("%d\n", action); }
    clearInputBuffer();
    while (action)
    {

        value = 0;

        switch (action)
        {
        case 0:
            action = 0;
            break;
        case 1:
            printf("\nВведите значение элемента: ");
            scanf("%d", &value);
            clearInputBuffer();
            work_tree = add_element_tree(work_tree, value);
            break;
        case 2:
            printf("\n-------------------------\n");
           print_tree(work_tree, 0);
                // printTree(work_tree);
            printf("\n-------------------------\n");
            break;
        case 3:
            printf("\nВведите значение элемента: ");
            scanf("%d", &value);
            clearInputBuffer();
            work_tree = delete_element(work_tree, value);
            break;
        case 4:
            printf("Степень двоичного графа = %d\n", find_degree(work_tree));
            break;
        default:
            printf("Комманда не найдена\n");
            print_menu();
        }
        action = getchar() - '0';
        D { printf("%d\n", action); }
        clearInputBuffer();
    }

    destroy_tree(work_tree);
    return 0;
}