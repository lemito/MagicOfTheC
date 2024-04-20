#include <stdio.h>
#include "queue_static_lib.h"

int main()
{
    printf("Hello World!\n");

    queue qwer;
    
    data_type zero = {0, 11};
    data_type one = {1, 11234};
    data_type two = {2, 2124};
    data_type three = {3, 23456};

    Create(&qwer);
    Push(&qwer, zero);
    Push(&qwer, one);
    Push(&qwer, two);
    Push(&qwer, three);
    printf("Size = %zu\n", Size(&qwer));
    printf("%d\t", Top_value(&qwer));
    Pop(&qwer);
    printf("%d\t", Top_value(&qwer));
    Pop(&qwer);
    printf("%d\t", Top_value(&qwer));
    Pop(&qwer);
    printf("%d\t", Top_value(&qwer));

    return 0;
}
