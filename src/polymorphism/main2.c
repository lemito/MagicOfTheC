#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float x;
    float y;
} TPoint;

// Результат сравнения ключей.
typedef enum {Less, Equal , More, NotEqual, NotComp} CmpType;

/* Тип TObject заменяет используемую в предыдущем примере TIDRecord
он содержит поля?ссылки на родовые процедуры, которые должны
располагаться в том же порядке, что и в самих объектах */
typedef struct TObject_ {
    void (*Draw)(struct TObject_*); // Функция отрисовки на первой позиции.
    void (*Compare)(struct TObject_*, struct TObject_*); // Функция сравнения на второй позиции.
} TObject, *PObject;

typedef CmpType (*PCmpFunction)(PObject U, PObject V);

// Тип указателя на функцию, будет во всех типах элементов очереди.
typedef void (*PProcedure)(PObject);

// Тип указатель на функцию для хранения в TExtcutable.
typedef void (*PDrawProc)(void);

typedef void* TValue;

// Теперь - особое внимание на абсолютный порядок полей в структурах.
// Указатель на функцию отрисовки ВСЕГДА первый, функция сравнения всегда
// вторая, в соответствии с их расположением в TObject.
typedef struct {
    PProcedure Draw; // Функция отрисовки на первой позиции.
    PCmpFunction Compare; // Функция сравнения на второй позиции.
    TPoint Center;
    float Radius;
} TCircle, *PCircle;

typedef struct {
    PProcedure Draw; // Функция отрисовки на первой позиции.
    PCmpFunction Compare; // Функция сравнения на второй позиции.
    TPoint A, B, C;
} TTriangle, *PTriangle;

typedef struct {
    PProcedure Draw; // Функция отрисовки на первой позиции.
    PCmpFunction Compare; // Функция сравнения на второй позиции.
    PDrawProc ProcPtr;
} TExecutable, *PExecutable;

/* Особенности отрисовки или вывода объекта на экране определяются конкретно
й реализацией. В данном примере мы просто печатаем геометрическое описани
е.*/
void DrawCircle (PObject P)
{
    PCircle T;
    T = (PCircle) P;
    printf("CIRCLE(X=%f,␣Y=%f,␣R=%f)\n", T->Center.x, T->Center.y, T->Radius);
}

void DrawTriangle (PObject P)
{
    PTriangle T;
    T = (PTriangle) P;
    printf("TRIANGLE(A=(%f,␣%f)," , T ->A.x , T ->A.y);
    printf("B =(%f,␣%f),", T->B.x, T->B.y);
    printf("C =(%f,␣%f))\n", T->C.x, T->C.y);
}

void DrawExecutable (PObject P)
{
    if (((PExecutable) P)->ProcPtr != NULL)
        (((PExecutable) P)->ProcPtr) ();
}

/* Сравнение основано на том, что у каждого объекта есть указатель на функцию Draw и у объектов одинакового исходного типа, указатели на эту функцию будут одинаковыми. */

//проверка эквивалентности типов
bool EqType (PObject U, PObject V)
{
/* Eсли указатели на родовые процедуры совпадают ? типы одинаковы! */
    return U->Draw == V ->Draw;
}

/* Cоответствует TCmpFunc */
CmpType CmpCircle (PObject U, PObject V)
{
    if (!EqType(U, V)) // Сравнение совпадания исходных типов.
        return NotComp;
    else // Сравнение радиусов. (Чей радиус больше - та и фигура больше)
    {
        if (((PCircle) U)->Radius == ((PCircle) V)->Radius)
            return Equal;
        if (((PCircle) U)->Radius < ((PCircle) V)->Radius)
            return Less;
        if (((PCircle) U)->Radius > ((PCircle) V)->Radius)
            return More;
    }
}

/* Расстояние между точками */
float Dist (TPoint A, TPoint B)
{
    return sqrt(pow(A.x -B .x, 2)+pow(A.y -B .y, 2));
}

/* Cумма длин сторон ? критерий сравнения треугольников */
float Sum (TTriangle U)
{
    return Dist(U.A, U.B) + Dist(U.A, U.C) + Dist(U.B, U.C);
}

/* Cоответствует TCmpFunc */
CmpType CmpTriangle (PObject U, PObject V)
{
    if (!EqType(U, V))
        return NotComp;
    else
    {
        if (Sum(*((PTriangle) U)) == Sum(*((PTriangle) V)))
            return Equal;
        if (Sum(*((PTriangle) U)) < Sum(*((PTriangle) V)))
            return Less;
        if (Sum(*((PTriangle) U)) > Sum(*((PTriangle) V)))
            return More;
    }
}

CmpType CmpExecutable (PObject U, PObject V)
{
    if (!EqType(U, V))
        return NotComp;
    else
    if (((PExecutable) U)->ProcPtr == ((PExecutable) V)->ProcPtr)
        return Equal;
    else
        return NotEqual;
}

TValue NewCircle (float x, float y, float r)
{
    PCircle Z;
    Z = malloc(sizeof(TCircle));
    Z->Center.x
            =
            x;
    Z->Center.y
            =
            y;
    Z->Radius = r;
    Z->Draw = DrawCircle;
    Z->Compare = CmpCircle;
    return (TValue) Z; //приведение типа к типу элементов очереди
}

TValue NewTriangle (float ax, float ay, float bx, float by, float cx, float
cy)
{
    PTriangle Z;
    Z = malloc(sizeof(TTriangle));
    Z->A.x
            =
            ax;
    Z->A.y
            =
            ay;
    Z->B.x
            =
            bx;
    Z->B.y
            =
            by;
    Z->C.x
            =
            cx;
    Z->C.y
            =
            cy;
    Z->Draw = DrawTriangle;
    Z->Compare = CmpTriangle;
    return (TValue) Z;
}

TValue NewExecutable (PProcedure T)
{
    PExecutable Z;
    Z = malloc(sizeof(TExecutable));
    Z->ProcPtr = (PDrawProc)T;
    Z->Draw = DrawExecutable;
    Z->Compare = CmpExecutable;
    return (TValue) Z;
}
void ExampleDraw() {
    printf("EXECUTING\n");
}


/**
 * @brief
 *
 */
typedef struct Item
{
    PObject data;
    struct Item *next;
} Item;

/**
 * @brief
 *
 */
typedef struct queue
{
    Item *first;
    Item *last;
    int size;
} queue;

void Create(queue *q)
{
    q->first = q->last = malloc(sizeof(struct Item));
    q->size = 0;
}

bool Empty(queue *q)
{
    return q->first == q->last;
}

int Size(queue *q)
{
    return q->size;
}

bool Push(queue *q, PObject t)
{
    if (!(q->last->next = malloc(sizeof(struct Item))))
        return false;
    q->last->data = (PObject)t;
    q->last = q->last->next;
    q->size++;
    return true;
}

bool Pop(queue *q)
{
    if (q->first == q->last)
        return false;
    struct Item *pi = q->first;
    q->first = q->first->next;
    q->size--;
    free(pi);
    return true;
}

PObject Top(const queue *q);

PObject Top(const queue *q)
{
    if (q->first != q->last)
        return (q->first)->data;
    return NULL;
}

void Destroy(queue *q)
{
    while (!Empty(q))
    {
        struct Item *pi = q->first;
        q->first = q->first->next;
        if (pi->data!= NULL) {
            free(pi->data);
        }
        free(pi);
    }
    q->size = 0;
    q->first = NULL;
    q->last = NULL;
}

int main() {
    queue queue;
    Create(&queue);
    Push(&queue , NewCircle(10,10 ,5));
    Push(&queue, NewTriangle(1,2 ,3 ,4 ,5 ,6));
    Push(&queue, NewExecutable(ExampleDraw));
    while (!Empty(&queue)) {
        Top(&queue)->Draw(Top(&queue));
        Pop(&queue);
    }
}