#include "list/list.h"

int main()
{
    List listik;
    Create(&listik); // Ensure this is the first operation on listik

    Iterator lastElem = Last(&listik);
    Insert(&listik, &lastElem, "10");
    Insert(&listik, &lastElem, "20");
    Insert(&listik, &lastElem, "30");

    printf("===== iterator ala c loop =====\n");
    Iterator it = First(&listik);
    for (int i = 0; i < size(&listik); i++)
    {
        char* data = fetch(&it);
        printf("%s\n", data);
        it = *Next(&it);
    }

    Iterator newit = First(&listik);
    printf("===== iterator ala python =====\n");
    for (; NotEqual(&newit, &lastElem); newit = *Next(&newit))
    {
        char* data = fetch(&newit);
        printf("%s\n", data);
    }
    Destroy(&listik);
    return 0;
}
