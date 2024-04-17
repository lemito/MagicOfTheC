#include <stdio.h>
#include "queue_dyn_lib.h"

int main()
{
    printf("Hello World!\n");

    queue qwer;

    Create(&qwer);
    Push(&qwer, "1");
    Push(&qwer, "2");
    Push(&qwer, "3");
    Push(&qwer, "4");
    printf("%s\t", Top(&qwer));
    Pop(&qwer);
    printf("%s\t", Top(&qwer));
    Pop(&qwer);
    printf("%s\t", Top(&qwer));
    Pop(&qwer);
    printf("%s\t", Top(&qwer));

    printf("\n");

    return 0;
}
