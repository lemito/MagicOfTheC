#include <cstdint>
#include <cstdio>
#include <cstdlib>

struct node {
    int8_t key;
    int8_t cnt;
    int16_t balance;
    struct node *left;
    struct node *right;
    struct node *parent;
};

typedef struct node *ptr;

void balance(ptr p);
ptr create_node(int8_t key, ptr parent);
void balance_delete(ptr p);
void rotate_left(ptr p);
void rotate_right(ptr p);

ptr create_node(int key, ptr parent) {
    ptr node = (ptr)malloc(sizeof(struct node));
    node->key = key;
    node->cnt = 1;
    node->balance = 0;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
    return node;
}

void search(int8_t sample, ptr* root){
    ptr p = *root;
    while (p->key != sample){
        if (p->key > sample){
            if (p->left == NULL) break;
            p = p->left;
        }
        if (p->key < sample){
            if (p->right == NULL) break;
            p = p->right;
        }
    }

    if (p->key == sample){
        ++(p->cnt);
    } else {
        if (p->key > sample){
            p->left = create_node(sample, p);
            p = p->left;
        }
        else {
            p->right = create_node(sample, p);
            p = p->right;
        }
        balance(p);
    }
    while ((*root)->parent != NULL) *root = (*root)->parent;
}

void balance(ptr p)
{

        ptr parent = p->parent; // Заводим указатель на родителя для удобства
        if (parent == NULL) // Если поднялись до корня -- выходим
            return;
        if (parent->left == p) { // Если пришли из левого поддерева
            --parent->balance;
        } else { // Иначе мы пришли из правого поддерева
            ++parent->balance; // И баланс надо увеличить
        }
        if (parent->balance == 0) {
            return; // И поддерево стало идеально сбалансированно -- выходим
        } else if (parent->balance == 1 || parent->balance == -1) {
        } else if (parent->balance == -2) {
            ptr y = parent; // Вводим обозначения как в конспекте
            ptr x = p; // Для удобства
            if (x->balance == -1) { // Случай 1 (Требуется 1 поворот)
                rotate_right(y); // Поворот x и y
                y->balance = 0;
                x->balance = 0;
            } else { // Случай 2 (Требуется 2 поворота)
                ptr z = x->right;
                rotate_left(x); // Поворот z и x
                rotate_right(y); // Поворот z и y
                x->balance = 0; // Балансировка
                y->balance = 0;
                if (z->balance == 1)
                    x->balance = -1;
                else if (z->balance == -1)
                    y->balance = 1;
                z->balance = 0;
            }
            return;
        } else if (parent->balance == 2) {
            ptr y = parent;
            ptr x=p;
            if (x->balance == 1) {
                rotate_left(y);
                y->balance = 0;
                x->balance = 0;
            }else{
                ptr z = x->left;
                rotate_right(x);
                rotate_left(y);
                x->balance = 0;
                y->balance = 0;
                if (z->balance == 1)
                y->balance = -1;
                else if (z->balance == -1)
                    x->balance = 1;
                z->balance = 0;
            }
            return;
        }
    }

void rotate_left(ptr p) { // Поворот влево относительно узла p и его правого потомка
    ֒
    ptr pivot = p->right; // Обеспечиваетя за счёт смены указателей. Лучше всего
// просматривать код вместе с иллюстрацией поворотов
    pivot->parent = p->parent;
    p->parent = pivot;
    if (pivot->parent != NULL) {
        if (pivot->parent->left == p)
            pivot->parent->left = pivot;
        else
            pivot->parent->right = pivot;
    }
    p->right = pivot->left;
    pivot->left = p;
    if (p->right != NULL)
        p->right->parent = p;
}

void rotate_right(ptr p) {
    ptr pivot = p->left;
    pivot->parent = p->parent;
    p->parent = pivot;
    if(pivot->parent != NULL) {
        if(pivot->parent->left == p)
            pivot->parent->left = pivot;
        else
            pivot->parent->right = pivot;
    }
    p->left = pivot->right;
    pivot->right = p;
    if(p->left != NULL)
        p->left->parent = p;
}


void delete(int x, ptr *root) {
ptr p = *root;
while (p->key != x) { // Итеративный поиск элемента
if (p->key > x) {
if (p->left == NULL)
break;
p = p->left;
}else{
if (p->right == NULL)
break;
p = p->right;
}
}
if (p->key != x) // Если его нет в дереве
return;
// Выходим
ptr parent = p->parent;
if (p->left == NULL && p->right == NULL) { // Удаление листа
if (parent == NULL) { // Если лист -- это корень
free(p);
// то удаляем его
*
root = NULL; // И зануляем внешний указатель
return; // Ничего балансировать не надо -- т.к. дерево теперь пустое
} else { // Если лист -- это НЕ корень
if (parent->right == p) { // Зануляем родительский указатель на
удаляемый узел
֒→
parent->
right = NULL;
-- parent->
bal; // Укоротили правую ветвь -- баланс уменьшился
}else{
parent->
left = NULL;
++parent->
bal; // Укоротили левую ветвь -- баланс увеличился
}
balance_delete(parent); // Балансируем родителя
free(p);
// Удаляем лист
}
} else if (p->right == NULL ||
p->left == NULL) { // Если есть только один наследник у
удаляемого
֒→
// узла, то подвешиваем его, вместо
удаляемого,
к родителю
֒→
ptr child = (p->right == NULL ? p->left : p->left); // Определяем
ненулевого потомка
֒→
child->
parent = parent; // Меняем родителя у потомка
// Ставим родителю указатель на потомка, меняя соответственно баланс
if (parent->right == p) {
parent->
right = child;
-- parent->
bal; // Укоротили правую ветвь -- баланс уменьшился
}else{
parent->
left = child;
++parent->
bal; // Укоротили левую ветвь -- баланс увеличился
}
balance_delete(parent); // Балансируем родителя
free(p);
// Удаляем элемент
} else { // Остался плохой вариант, когда у нас 2 ребенка
ptr next = p->right; // Находим минимальный элемент в правом поддереве
while(next->left != NULL)
next = next->left;
p->
key = next->key; // Перемещаем его в данный узел
p->
count = next->count;
delete(next->key, &next); // Запускаем удаление узла next
}
while ((*root)->parent != NULL) { // В конце поднимаем внешний указатель по
дереву,
до тех
пор,
пока он
не станет
указывать на
корень
֒
*
root = (*root)->parent;
}
}