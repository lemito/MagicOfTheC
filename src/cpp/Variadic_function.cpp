/**
 * Функции с переменным числом аргументов
 * Доступно на C и на C++
 */
#include <cstdarg>
#include <iostream>

/**
 * Сумма некоторых чиселок
 * @param cnt их количество
 * @param ... сами числа (через запятую)
 * @return сумма чисел
 */
long long sum(int cnt, ...) {
  va_list arg_list;
  long long res = 0;
  va_start(arg_list, cnt);
  for (int i = 0; i < cnt; ++i) {
    res += va_arg(arg_list, long long);
  }
  va_end(arg_list);
  return res;
}

/**
 * Еще один printf
 * @param fmt формат-строка
 * @param ... параметры
 */
void yet_another_format(const char* fmt, ...) {
  va_list arg_list;
  va_start(arg_list, fmt);

  // для каждого символа в формат-строке
  for (const char* c = fmt; *c != '\0'; ++c) {
    // символ начинается с '%'? возможно символ форматирования...
    if (*c == '%') {
      // следующий символ
      ++c;
      switch (*c) {
        case 'm':
          std::cout << "This is " << va_arg(arg_list, const char*) << " m";
          continue;
        case 'p':
          std::cout << "This is " << va_arg(arg_list, int) << " p";
          continue;
        case 'q':
          std::cout << "This is " << va_arg(arg_list, double) << " q";
          continue;
        // ...ну или просто символ %
        case '%':
          std::cout << '%';
          continue;
        default:
          std::cout << '%' << *c;
          continue;
      }
    } else {
      std::cout << *c;
    }
  }
  va_end(arg_list);
}

int main() {
  std::cout << sum(6, 2, 125, 5, 7, 5, 10) << '\n';
  yet_another_format("%m % %p%q \tTab %j", "Meow", 52, 3.14);
  return 0;
}