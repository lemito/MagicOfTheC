#include <stddef.h>
#include <stdio.h>
#include <malloc.h>

/**
 * Пример с бестиповыми указателями
 */

// Тут все id-шки объектов
typedef enum {idNone, idCircle, idTriangle, idExecutable} objectID;

/**
 * Точечка
 */
typedef struct {
    float x;
    float y;
} TPoint;

/**
 * КружочеГ
 */
typedef struct {
    objectID id;
    TPoint center;
    float radius;
} TCircle, *PCircle;

/**
 * ТреугольничеГ
 */
typedef struct {
    objectID id;
    TPoint A, B, C;
} TTriangle, *PTriangle;

// Указатель на процедуру
typedef void (*PProcedure)(void);

/**
 * Структурка процедуры
 */
typedef struct {
    objectID id;
    PProcedure ProcPtr;
} TExecutable, *PExecutable;

typedef struct {
    objectID id;
} TIDRecord, *PIDRecord;

//typedef ptrdiff_t word;
//typedef *word Pointer;

typedef void* TValue;

/**
 * Функция отрисовки кружка
 * @param T
 */
void DrawCircle (TCircle T)
{
    printf("CIRCLE(X=%f,?Y=%f,?R=%f)\n", T.center.x, T.center.y, T.radius);
}

/**
 * Функция отрисовки треугольника
 * @param T
 */
void DrawTriangle (TTriangle T)
{
    printf("TRIANGLE(A=(%f,␣%f)," , T .A .x , T.A .y);
    printf("B=(%f,␣%f),", T.B .x, T.B .y);
    printf("C =(%f,␣%f))\n", T.C .x, T.C .y);
}

/**
 * Функция отрисовки процедуры (мб какой-то функции)
 * @param T
 */
void DrawExecutable (TExecutable T)
{
    if (T.ProcPtr != NULL)
        T.ProcPtr();
}

/**
 * Обобщающий Draw
 * @param P
 */
void Draw (TValue P)
{
    if (P != NULL) {
        switch (((PIDRecord) P)->id) {
            case idCircle:
                DrawCircle(*((PCircle) P));
                break;
            case idTriangle:
                DrawTriangle(*((PTriangle) P));
                break;
            case idExecutable:
                DrawExecutable(*((PExecutable) P));
                break;
            case idNone:
                break;
        }
    }
}

/**
 * Создание нового кружка
 * @param x
 * @param y
 * @param r
 * @return
 */
TValue NewCircle (float x, float y, float r)
{
    PCircle Z;
    Z = malloc(sizeof(TCircle));
    Z->center.x
            =
            x;
    Z->center.y
            =
            y;
    Z->radius = r;
    Z->id = idCircle;
    return (TValue) Z;
}

/**
 * Создание нового треугольничка
 * @param ax
 * @param ay
 * @param bx
 * @param by
 * @param cx
 * @param cy
 * @return
 */
TValue NewTriangle (float ax, float ay, float bx, float by, float cx, float
cy)
{
    PTriangle Z;
    Z = malloc(sizeof(TTriangle));
    Z->A.x
            =
            ax; Z->A.y
                        =
                        ay;
    Z->B.x
            =
            bx; Z->B.y
                        =
                        by;
    Z->C.x
            =
            cx; Z->C.y
                        =
                        cy;
    Z->id = idTriangle;
    return (TValue) Z;
}

/**
 * Создание некоего "демона"
 * @param T
 * @return
 */
TValue NewExecutable (PProcedure T) {
    PExecutable Z;
    Z = malloc(sizeof(TExecutable));
    Z->ProcPtr = T;
    Z->id = idExecutable;
    return (TValue) Z;
}

/**
 * Уничтожалка
 * @param P
 */
void DestroyObject (TValue P)
{
    switch (((PIDRecord) P)->id)
    {
        case idCircle:
            free((PCircle) P);
            break;
        case idTriangle:
            free((PTriangle) P);
            break;
        case idExecutable:
            free((PExecutable) P);
            break;
        case idNone:
            break;
    }
}

/**
 * Некий демон
 */
void ExampleDraw(void){
    puts("I DRAW");
}

int main(){
    TValue circle = NewCircle(10, 10, 5);
    TValue triangle = NewTriangle(1,2 ,3 ,4 ,5 ,6);
    TValue daemon = NewExecutable(ExampleDraw);
    Draw(circle);
    Draw(triangle);
    Draw(daemon);
    DestroyObject(circle);
    DestroyObject(triangle);
    DestroyObject(daemon);
    return 0;
}