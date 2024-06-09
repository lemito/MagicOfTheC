#ifndef SYMBOL_H_
#define SYMBOL_H_

typedef enum {
    ASSOC_LEFT, ASSOC_RIGHT
} OP_ASSOC;

typedef enum {
    SYMBOL_NONE,    // не символ вовсе
    SYMBOL_NUMBER,  // число
    SYMBOL_VAR,     // переменная
    SYMBOL_OP,      // оператор
    SYMBOL_LEFT_BR, // открывающая скобка
    SYMBOL_RIGHT_BR // закрывающая скобка
} Symbol_type;

typedef enum {
    OP_MINUS = '-',
    OP_PLUS = '+',
    OP_MULT = '*',
    OP_DIVIDE = '/',
    OP_POW = '^',
    OP_UNARY_MINUS = '!' // а вот тут что угодно может быть, главное, чтобы с простым минусом не путать
} Operator;

typedef struct Symbol_ {
    Symbol_type type;
} Symbol;

typedef struct Symbol_number_ {
  Symbol_type type;
  double number;
} Symbol_number;

#define VARIABLE_MAX_SIZE 10
typedef struct Symbol_variable_ {
  Symbol_type type;
  char variable[VARIABLE_MAX_SIZE];
} Symbol_variable;

typedef struct Symbol_OP_ {
  Symbol_type type;
  Operator op;
} Symbol_OP;
#endif // SYMBOL_H_
