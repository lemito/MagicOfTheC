// Реализация полиморфизма на Си с помощью объектов и наследования. Пример ИИ-шковый, мб добавлю нормальный
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FREE_AND_NULL(p) \
    do                   \
    {                    \
        free(p);         \
        (p) = NULL;      \
    } while (0)

// классом будем называть "класс" - это не клас как на питоне, но что-то похожее
// функцией (функцией для класса) будем называть "метод" ("метод класса") - не как на питоне, но что-то похожее
// конструктур - экивалент __init__ и Dog(){} <= C++

// Базовый класс
typedef struct Animal
{
    void (*speak)(struct Animal *); // Указатель на функцию speak
    char* name;
} Animal;

// Функция speak для Animal
void Animal_speak(Animal *animal)
{
    printf("Animal is speaking\n");
}

// Класс (наследник Animal)
typedef struct Dog
{
    Animal base; // Наследование от Animal
} Dog;

// Функция speak для Dog
void Dog_speak(Animal *animal)
{
    printf("Dog %s says: Woof!\n", animal->name);
}

// Конструктор для Dog
Dog *Dog_new()
{
    Dog *dog = (Dog *)malloc(sizeof(Dog));
    dog->base.speak = Dog_speak; // Полиморфизм
    dog->base.name = strdup("Ytrewq");
    return dog;
}

// Класс Cat (наследник Animal)
typedef struct Cat
{
    Animal base; // Наследование от Animal
} Cat;

// Функция speak для Cat
void Cat_speak(Animal *animal)
{
    printf("Cat %s says: Meow!\n", animal->name);
}

// Конструктор для Cat
Cat *Cat_new()
{
    Cat *cat = (Cat *)malloc(sizeof(Cat));
    cat->base.speak = Cat_speak; // Полиморфизм
    cat->base.name = strdup("Qwerty");
    return cat;
}

// Некая обобщающая функция
void makeAnimalSpeak(Animal *animal)
{
    animal->speak(animal);
}

int main()
{
    Dog *dog = Dog_new();
    Cat *cat = Cat_new();

    // В makeAnimalSpeak приводим класс от наследника к базовому, так как он прописан в функции аргкментом Anmial*, не Dog*/Cat*
    makeAnimalSpeak((Animal *)dog);
    makeAnimalSpeak((Animal *)cat);

    FREE_AND_NULL(dog);
    FREE_AND_NULL(cat);

    return 0;
}
