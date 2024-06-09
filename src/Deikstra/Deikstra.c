#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "symbol.h"
#include "tree.h"

int op_priority(char op) {
  switch (op) {
  case OP_MINUS:
  case OP_PLUS:
    return 1;
  case OP_MULT:
  case OP_DIVIDE:
    return 2;
  case OP_POW:
    return 3;
  case OP_UNARY_MINUS:
    return 4;
  }
  return -1;
}
OP_ASSOC op_assoc(Operator op) {
  switch (op) {
  case OP_MINUS:
  case OP_PLUS:
  case OP_MULT:
  case OP_DIVIDE:
    return ASSOC_LEFT;
  case OP_UNARY_MINUS:
  case OP_POW:
    return ASSOC_RIGHT;
  }
  return -1;
}

char op_to_char(Operator op) {
  switch (op) {
  case OP_UNARY_MINUS:
    return '-';
  default:
    return op;
  }
  return -1;
}

bool is_space(int c) { return (c == ' ') || (c == '\n') || (c == '\t'); }

// ?????????? ??????? ? ?????? ????????? ???????? ??????
char next_char() {
  char c = getchar();
  while (is_space(c))
    c = getchar();
  return c;
}

Symbol * scan_number();
Symbol * scan_variable();
Symbol * scan_operator(
    Symbol_type prev_type); // ??? ??????????? ???????? ?????? ? ????????
Symbol * next_symbol() {
  // ????? ????? ??????? ??? ?????????? ?????????? ??????
  // ???? ??? ?????, ?????, ???????????? ? ??????? ??????? ?? ??????? ??? ?
  // ????????
  static Symbol_type prev_type = SYMBOL_NONE;

  Symbol * result;
  int c = next_char();
  // EOF на ? сменил
  if (c == '?') { // ???? ??????? ????? ??
    result = malloc(sizeof(Symbol));
    result->type = SYMBOL_NONE;
    prev_type = SYMBOL_NONE;
  }
  else if (c == '.' || (c >= '0' && c <= '9')) {
    // ????? ????? ?????????? ? ?????: .9 == 0.9
    ungetc(c, stdin);
    result = scan_number();
  }
  else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
    ungetc(c, stdin);
    result = scan_variable();
  }
  else if (c == '(') {
    result = malloc(sizeof(Symbol));
    result->type = SYMBOL_LEFT_BR;
  }
  else if (c == ')') {
    result = malloc(sizeof(Symbol));
    result->type = SYMBOL_RIGHT_BR;
  }
  else if (c == '-' || c == '+' || c == '*' || c == '/' || c == '^') {
    ungetc(c, stdin);
    result = scan_operator(prev_type);
  }
  else {
    // ????? ??????: ?? ?????? ???? ???????, ??????? ?? ?? ????? ?? ?????????
    result = malloc(sizeof(Symbol));
    result->type = SYMBOL_NONE;
  }

  // ?????????? ? ??????????? ?????????? ??? ?????? ??? ?????????? ??????
  prev_type = result->type;

  return result;
}

Symbol * scan_operator(Symbol_type prev_type) {
  Symbol_OP * temp = malloc(sizeof(Symbol_OP));
  temp->type = SYMBOL_OP;
  char op;
  scanf("%c", &op);
  if (op == '-' && (prev_type == SYMBOL_OP || prev_type == SYMBOL_NONE || prev_type == SYMBOL_LEFT_BR)) {
    temp->op = OP_UNARY_MINUS;
  }
  else {
    temp->op = op;
  }
  return (Symbol *)temp;
}

Symbol * scan_variable() {
  Symbol_variable * temp = malloc(sizeof(Symbol_variable));
  temp->type = SYMBOL_VAR;
  scanf("%[a-zA-Z]", temp->variable);
  return (Symbol *)temp;
}

Symbol * scan_number() {
  Symbol_number * temp = malloc(sizeof(Symbol_number));
  temp->type = SYMBOL_NUMBER;
  scanf("%lf", &temp->number); // ?????? ? ?????????
  return (Symbol *)temp;
}

DEF_STACK(symbol, Symbol *)
bool build_tree(Expression_node ** tree, Stack_symbol * rev) {
  if (Stack_symbol_empty(rev)) {
    return false;
  }
  Symbol * symbol = *Stack_symbol_top(rev);
  Stack_symbol_pop(rev);
  (*tree) = (Expression_node *)malloc(sizeof(Expression_node));
  (*tree)->symbol = symbol;

  bool result = true;
  if (symbol->type == SYMBOL_OP) {
    Symbol_OP * symbol_op = (Symbol_OP *)symbol;
    if (symbol_op->op == OP_UNARY_MINUS) {
      (*tree)->l = NULL;
      result = result && build_tree(&((*tree)->r), rev);
    }
    else {
      result = result && build_tree(&((*tree)->r), rev);
      // ???? result ??? false, ?? build_tree ??? ?? ?????????
      result = result && build_tree(&((*tree)->l), rev);
    }
  }
  return result;
}

void print_tree(Expression_node * tree, size_t level) {
  if (tree == NULL)
    return;

  if (tree->symbol->type == SYMBOL_OP) {
    print_tree(tree->r, level + 1);
  }
  for (int i = 0; i < level; i++) {
    printf("\t");
  }
  switch (tree->symbol->type) {
    Symbol_OP * symbol_op;
  case SYMBOL_NUMBER:
    printf("%.2lf\n", ((Symbol_number *)tree->symbol)->number);
    break;
  case SYMBOL_VAR:
    printf("%s\n", ((Symbol_variable *)tree->symbol)->variable);
    break;
  case SYMBOL_OP:
    symbol_op = (Symbol_OP *)tree->symbol;
    if (symbol_op->op == OP_UNARY_MINUS) {
      printf("-\n");
    }
    else {
      printf("%c\n", op_to_char(symbol_op->op));
    }
    break;
  default:
    fprintf(stderr, "This symlbol must not be in the tree already");
    return;
  }
  if (tree->symbol->type == SYMBOL_OP) {
    print_tree(tree->l, level + 1);
  }
}

void print_op(Expression_node * node);
void print_expr(Expression_node * node) {
  if (node == NULL) return;
  switch (node->symbol->type) {
    Symbol_OP * symbol_op;
  case SYMBOL_NUMBER:
    printf("%.2lf ", ((Symbol_number *)node->symbol)->number);
    break;
  case SYMBOL_VAR:
    printf("%s ", ((Symbol_variable *)node->symbol)->variable);
    break;
  case SYMBOL_OP:
    print_op(node);
    break;
  default:
    fprintf(stderr, "Error: undefined symbol type in print_expr function");
    return;
  }
}

void print_op(Expression_node * node) {
  Operator currentOp = ((Symbol_OP *)node->symbol)->op;
  if (node->r->symbol->type == SYMBOL_OP) {
    Operator rightOp = ((Symbol_OP *)node->r->symbol)->op;
    if (op_priority(currentOp) > op_priority(rightOp)) {
      printf("( ");
      print_expr(node->r);
      printf(") ");
    }
    else
      print_expr(node->r);
  }

  printf("%c ", op_to_char(currentOp));

  if (node->l->symbol->type == SYMBOL_OP) {
    Operator leftOp = ((Symbol_OP *)node->l->symbol)->op;
    if (op_priority(currentOp) > op_priority(leftOp)) {
      printf("( ");
      print_expr(node->l);
      printf(") ");
    }
    else
      print_expr(node->l);
  }
}

Stack_symbol * Deikstra() {
  Stack_symbol * temp, * prefix_form;
  Symbol * symbol;

  temp = Stack_symbol_create();
  prefix_form = Stack_symbol_create();

  while ((symbol = next_symbol())->type != SYMBOL_NONE) {
    switch (symbol->type) {
      Symbol_OP * symbol_op;
      Symbol_OP ** top;
    case SYMBOL_NONE:
      fprintf(stderr, "Error: symbol not recognized\n");
      return NULL;

    case SYMBOL_OP:
      symbol_op = (Symbol_OP *)symbol;
      top = (Symbol_OP **)Stack_symbol_top(temp);
      while (!Stack_symbol_empty(temp) && (*top)->type == SYMBOL_OP &&
             ((op_assoc(symbol_op->op) == ASSOC_LEFT &&
               op_priority(symbol_op->op) <= op_priority((*top)->op)) ||
               (op_assoc(symbol_op->op) == ASSOC_RIGHT &&
                 op_priority(symbol_op->op) < op_priority((*top)->op)))) {
        // ?????????????
        Stack_symbol_push(prefix_form, (Symbol *)*top);
        Stack_symbol_pop(temp);
        top = (Symbol_OP **)Stack_symbol_top(temp);
      }

      // ????? ????? ???????? ?? ???????? ?????
      Stack_symbol_push(temp, symbol);
      break;

    case SYMBOL_NUMBER:
    case SYMBOL_VAR:
      // ??? ???? ????? ?????? ? ???????? ????
      Stack_symbol_push(prefix_form, symbol);
      break;
    case SYMBOL_LEFT_BR:
      Stack_symbol_push(temp, symbol);
      break;

    case SYMBOL_RIGHT_BR:
      top = (Symbol_OP **)Stack_symbol_top(temp);
      while (top != NULL && (*top)->type != SYMBOL_LEFT_BR) {
        if (Stack_symbol_empty(temp)) {
          fprintf(stderr, "Error: closing bracket hasn't pair");
          return NULL;
        }

        // ?????????????
        Stack_symbol_push(prefix_form, (Symbol *)*top);
        Stack_symbol_pop(temp);
        top = (Symbol_OP **)Stack_symbol_top(temp);
      }
      Stack_symbol_pop(temp); // ??????? ???????????? (
      break;
    }
  }

  while (!Stack_symbol_empty(temp)) {
    symbol = *Stack_symbol_top(temp);
    Stack_symbol_pop(temp);
    if (symbol->type == SYMBOL_LEFT_BR) {
      fprintf(stderr, "Error: opening bracket hasn't pair");
      return NULL;
    }
    Stack_symbol_push(prefix_form, symbol);
  }

  return prefix_form;
}

void print_stack(Stack_symbol * stack) {
  if (Stack_symbol_empty(stack))
    return;

  Symbol * top = *Stack_symbol_top(stack);
  if (top->type == SYMBOL_NUMBER) {
    printf("%lf\n", ((Symbol_number *)top)->number);
  }
  else if (top->type == SYMBOL_OP) {
    printf("%c\n", ((Symbol_OP *)top)->op);
  }
  else if (top->type == SYMBOL_VAR) {
    printf("%s\n", ((Symbol_variable *)top)->variable);
  }
  Stack_symbol_pop(stack);
  print_stack(stack);
  Stack_symbol_push(stack, top);
}
int main() {
  Stack_symbol * prefix_form = Deikstra();
  print_stack(prefix_form);

  Expression_node * tree_expr;
  build_tree(&tree_expr, prefix_form);

  print_tree(tree_expr, 0);
  return 0;
}
